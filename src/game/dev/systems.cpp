#include "./systems.hpp"

#include <entt_editor.hpp>
#include <ranges>
#include <imgui.h>
#include <raylib.h>

#include "../background/components.hpp"
#include "../combat/components.hpp"
#include "../physics/components.hpp"
#include "../player/components.hpp"
#include "../shapes/components.hpp"
#include "../solids/components.hpp"
#include "../states.hpp"
#include "./components.hpp"

namespace cfu::systems {

auto setup_dev(entt::registry& registry) -> void {
    registry.ctx().insert_or_assign(comp::DevSettings {});
    setup_entt_editor(registry);
}

auto draw_dev(entt::registry& registry) -> void {
    auto& settings = registry.ctx().get<comp::DevSettings>();
    if (!settings.show_dev_panel) return;
    draw_dev_panel(registry);
    draw_entt_editor(registry);
}

auto update_dev(entt::registry& registry) -> void {
    auto& settings = registry.ctx().get<comp::DevSettings>();
    if (IsKeyPressed(KEY_F3)) settings.show_dev_panel = !settings.show_dev_panel;
}

struct StateMenuResult {
    bool main_menu = false;
    bool in_game = false;
};

static auto state_menu() -> StateMenuResult {
    auto result = StateMenuResult {};

    if (ImGui::MenuItem("Main menu")) result.main_menu = true;
    if (ImGui::MenuItem("In game")) result.in_game = true;

    return result;
}

auto draw_dev_panel(entt::registry& registry) -> void {
    // auto& settings = registry.ctx().get<comp::DevSettings>();
    auto& editor = registry.ctx().get<comp::Editor>();
    auto& stack = StateStack::get(registry);

    auto io = ImGui::GetIO();
    auto flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoResize;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::Begin("Dev panel", nullptr, flags);
    if (ImGui::BeginMenuBar()) {
        ImGui::PushItemFlag(ImGuiItemFlags_AutoClosePopups, false);

        if (ImGui::BeginMenu("state")) {
            if (ImGui::BeginMenu("Push")) {
                auto result = state_menu();
                if (result.main_menu) stack.push(MainMenuState {});
                if (result.in_game) stack.push(InGameState {});
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Replace")) {
                auto result = state_menu();
                if (result.main_menu) stack.replace(MainMenuState {});
                if (result.in_game) stack.replace(InGameState {});
                ImGui::EndMenu();
            }

            if (ImGui::MenuItem("Pop")) stack.pop();

            ImGui::Separator();

            ImGui::Text("State Stack");
            auto list = StateStack::get(registry).list();
            for (auto state : std::views::reverse(list)) {
                if (std::holds_alternative<MainMenuState>(state)) ImGui::Text("- Main Menu");
                else if (std::holds_alternative<InGameState>(state)) ImGui::Text("- In Game");
                else ImGui::Text("- Unknown");
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("view")) {
            ImGui::MenuItem("Entity editor", nullptr, &editor.show_window);
            ImGui::EndMenu();
        }

        ImGui::PopItemFlag();
        ImGui::EndMenuBar();
    }
    ImGui::End();
}

auto setup_entt_editor(entt::registry& registry) -> void {
    auto editor = comp::Editor {};
    editor.show_window = false;
    editor.registerComponent<comp::BackgroundColor>("background::Color");
    editor.registerComponent<comp::Ball>("shapes::Ball");
    editor.registerComponent<comp::Cube>("solids::Cube");
    editor.registerComponent<comp::Player>("player::Player");
    editor.registerComponent<comp::Transform>("physics::Transform");
    editor.registerComponent<comp::ShapeColor>("shapes::Color");
    editor.registerComponent<comp::SolidMaterial>("solids::Material");
    editor.registerComponent<comp::Hp>("combat::Hp");
    editor.registerComponent<comp::MoveSpeed>("combat::MoveSpeed");
    editor.registerComponent<comp::MeleeAttack>("combat::MeleeAttack");
    registry.ctx().insert_or_assign(editor);

    auto entity = comp::CurrentEntity {.entity = entt::null};
    registry.ctx().insert_or_assign(entity);
}

auto draw_entt_editor(entt::registry& registry) -> void {
    auto& entity = registry.ctx().get<comp::CurrentEntity&>().entity;
    auto& editor = registry.ctx().get<comp::Editor>();
    editor.renderSimpleCombo(registry, entity);
}

} // namespace cfu::systems
