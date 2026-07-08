#include "./systems.hpp"

#include <entt_editor.hpp>
#include <ranges>
#include <imgui.h>
#include <raylib.h>

#include "../background/components.hpp"
#include "../combat/components.hpp"
#include "../constants.hpp"
#include "../data/components.hpp"
#include "../data/systems.hpp"
#include "../in_game/components.hpp"
#include "../physics/components.hpp"
#include "../player/components.hpp"
#include "../raymath.hpp"
#include "../shapes/components.hpp"
#include "../solids/components.hpp"
#include "../states.hpp"
#include "../tilemap/components.hpp"
#include "./components.hpp"
#include "./utils.hpp"

namespace cfu::systems {

auto setup_dev(entt::registry& registry) -> void {
    registry.ctx().insert_or_assign(comp::DevSettings {});
    setup_entt_editor(registry);
    setup_tilemap_editor(registry);
    setup_data_editor(registry);
}

auto draw_dev(entt::registry& registry) -> void {
    auto& settings = registry.ctx().get<comp::DevSettings>();
    if (settings.show_dev_panel) {
        SetWindowSize(WINDOW_DEV_WIDTH, WINDOW_DEV_HEIGHT);
    } else {
        SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        return;
    }

    draw_dev_panel(registry);
    draw_entt_editor(registry);
    draw_tilemap_editor(registry);
    draw_data_editor(registry);
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
    auto& entt_editor = registry.ctx().get<comp::Editor>();
    auto& tilemap_editor = registry.ctx().get<comp::TileMapEditor>();
    auto& data_editor = registry.ctx().get<comp::DataEditor>();
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
            ImGui::MenuItem("Entity editor", nullptr, &entt_editor.show_window);
            ImGui::MenuItem("Tilamap editor", nullptr, &tilemap_editor.show_window);
            ImGui::MenuItem("Data editor", nullptr, &data_editor.show_window);
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

static auto get_cube_under_mouse(entt::registry& registry) -> std::tuple<entt::entity, Vector3> {
    auto view = registry.view<const comp::Tile, const comp::Transform, const comp::Cube>();
    for (auto [entity, tile, transform, cube] : view.each()) {
        const auto ray = dev::mouse_ray(registry);
        const auto size = cube.size * transform.scale;
        const auto min = transform.translation - size * 0.5f;
        auto max = min + size;
        auto box = BoundingBox {.min = min, .max = max};
        auto collision = GetRayCollisionBox(ray, box);
        if (collision.hit) {
            return {entity, collision.point};
            // current_entity.entity = entity;
            // editor.mode = comp::TileMapEditorMode::Free;
            break;
        }
    }
    return {entt::null, Vector3()};
}

auto setup_tilemap_editor(entt::registry& registry) -> void {
    auto editor = comp::TileMapEditor {};
    registry.ctx().insert_or_assign(editor);
}

auto draw_tilemap_editor(entt::registry& registry) -> void {
    auto& editor = registry.ctx().get<comp::TileMapEditor>();
    if (!editor.show_window) return;

    auto tilemap_entity = registry.view<comp::TileMap>().back();
    if (tilemap_entity == entt::null) {
        editor.enabled = false;
        return;
    } else {
        editor.enabled = true;
    }

    auto& current_entity = registry.ctx().get<comp::CurrentEntity>();

    ImGui::Begin("Tilemap Editor");

    ImGui::SeparatorText("Mode");
    auto selected_mode = int(editor.mode);
    ImGui::RadioButton("Free", &selected_mode, int(comp::TileMapEditorMode::Free));
    ImGui::RadioButton("Selecting", &selected_mode, int(comp::TileMapEditorMode::Selecting));
    ImGui::RadioButton("Placing", &selected_mode, int(comp::TileMapEditorMode::Placing));
    ImGui::RadioButton("Erasing", &selected_mode, int(comp::TileMapEditorMode::Erasing));
    editor.mode = comp::TileMapEditorMode(selected_mode);

    auto selected_tile = int(editor.current_tile);
    ImGui::SeparatorText("Tile");
    ImGui::RadioButton("Floor", &selected_tile, int(comp::TileKind::Floor));
    ImGui::RadioButton("Wall", &selected_tile, int(comp::TileKind::Wall));
    editor.current_tile = comp::TileKind(selected_tile);

    ImGui::End();

    switch (editor.mode) {
        case comp::TileMapEditorMode::Free: {
            break;
        }
        case comp::TileMapEditorMode::Selecting: {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (auto [entity, position] = get_cube_under_mouse(registry); entity != entt::null) {
                    current_entity.entity = entity;
                    editor.mode = comp::TileMapEditorMode::Free;
                }
            }
            break;
        }
        case comp::TileMapEditorMode::Placing: {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (auto [entity, position] = get_cube_under_mouse(registry); entity != entt::null) {
                    const auto x = gsl::index(position.x / TILE_SIZE);
                    const auto y = gsl::index(position.y / TILE_SIZE);
                    const auto z = gsl::index(position.z / TILE_SIZE);
                    auto new_entity = registry.create();
                    comp::create_tile(registry, new_entity, editor.current_tile, x, y, z);
                    registry.emplace<comp::InGameTag>(new_entity);
                } else {
                    const auto ray = dev::mouse_ray(registry);
                    const auto size = float(TILE_SIZE);

                    auto collision = GetRayCollisionBox(
                        ray,
                        BoundingBox {
                            .min = Vector3(0.0f, 0.0f, 0.0f),
                            // TODO: get tilemap size
                            .max = Vector3(128.0f * size, size, 128.0f * size),
                        }
                    );

                    if (collision.hit) {
                        const auto x = gsl::index(collision.point.x / TILE_SIZE);
                        const auto y = 0;
                        const auto z = gsl::index(collision.point.z / TILE_SIZE);
                        auto new_entity = registry.create();
                        comp::create_tile(registry, new_entity, editor.current_tile, x, y, z);
                        registry.emplace<comp::InGameTag>(new_entity);
                    }
                }
            }
            break;
        }
        case comp::TileMapEditorMode::Erasing: {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (auto [entity, position] = get_cube_under_mouse(registry); entity != entt::null) {
                    // TODO: Update height map
                    registry.destroy(entity);
                }
            }
            break;
            break;
        }
    }
}

auto setup_data_editor(entt::registry& registry) -> void {
    registry.ctx().insert_or_assign(comp::DataEditor {});
}

auto draw_data_editor(entt::registry& registry) -> void {
    auto& d = registry.ctx().get<comp::GameData>();
    auto& editor = registry.ctx().get<comp::DataEditor>();
    if (!editor.show_window) return;

    ImGui::Begin("Data Editor");

    if (ImGui::Button("Apply") || editor.update_realtime) systems::apply_game_data_to_game(registry);
    ImGui::SameLine();
    if (ImGui::Button("Save")) systems::save_game_data_to_disk(registry);
    ImGui::SameLine();
    if (ImGui::Button("Reset")) ImGui::OpenPopup("Confirm Reset?");
    ImGui::SameLine();
    ImGui::Checkbox("Realtime", &editor.update_realtime);

    ImGui::Separator();

    if (ImGui::CollapsingHeader("Camera settings")) {
        ImGui::PushID("Camera settings");
        ImGui::Indent(10.f);

        auto& c = d.balance.camera;
        ImGui::DragFloat("Box culling", &c.box_culling, 100.0f);
        ImGui::DragFloat("Lerp factor", &c.lerp, 0.002f);
        ImGui::DragFloat("fovy", &c.fovy, 1.0f);

        ImGui::SeparatorText("Offset");
        ImGui::DragFloat("X##offset", &c.offset.x, 1.0f);
        ImGui::DragFloat("Y##offset", &c.offset.y, 1.0f);
        ImGui::DragFloat("Z##offset", &c.offset.z, 1.0f);

        ImGui::SeparatorText("Up");
        ImGui::DragFloat("X##up", &c.up.x, 1.0f);
        ImGui::DragFloat("Y##up", &c.up.y, 1.0f);
        ImGui::DragFloat("Z##up", &c.up.z, 1.0f);

        ImGui::Unindent();
        ImGui::PopID();
    }

    if (ImGui::CollapsingHeader("Player stats")) {
        ImGui::PushID("Player stats");
        ImGui::Indent(10.0f);

        auto& p = d.balance.player;

        if (ImGui::CollapsingHeader("Evo 1")) {
            ImGui::PushID("Evo 1");
            ImGui::Indent(10.0f);

            auto& e = p.evo_1;
            ImGui::DragInt("Max HP", &e.max_hp);
            ImGui::DragInt("Move Speed", &e.move_speed);
            ImGui::DragInt("Damage", &e.damage);
            ImGui::DragInt("Attack Speed", &e.attack_speed);
            ImGui::DragInt("Attack Radius", &e.attack_radius);

            ImGui::Unindent(10.0f);
            ImGui::PopID();
        }

        if (ImGui::CollapsingHeader("Evo 2")) {
            ImGui::PushID("Evo 2");
            ImGui::Indent(10.0f);

            auto& e = p.evo_2;
            ImGui::DragInt("Max HP", &e.max_hp);
            ImGui::DragInt("Move Speed", &e.move_speed);
            ImGui::DragInt("Damage", &e.damage);
            ImGui::DragInt("Attack Speed", &e.attack_speed);
            ImGui::DragInt("Attack Radius", &e.attack_radius);

            ImGui::Unindent(10.0f);
            ImGui::PopID();
        }

        if (ImGui::CollapsingHeader("Evo 3")) {
            ImGui::PushID("Evo 3");
            ImGui::Indent(10.0f);

            auto& e = p.evo_3;
            ImGui::DragInt("Max HP", &e.max_hp);
            ImGui::DragInt("Move Speed", &e.move_speed);
            ImGui::DragInt("Damage", &e.damage);
            ImGui::DragInt("Attack Speed", &e.attack_speed);
            ImGui::DragInt("Attack Radius", &e.attack_radius);

            ImGui::Unindent(10.0f);
            ImGui::PopID();
        }

        ImGui::Unindent(10.0f);
        ImGui::PopID();
    }

    if (ImGui::BeginPopupModal("Confirm Reset?", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Are you sure you want to reset game data?");
        ImGui::Separator();

        if (ImGui::Button("OK", ImVec2(120, 0))) {
            systems::load_game_data_from_disk(registry);
            ImGui::CloseCurrentPopup();
        }

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    ImGui::End();
}

} // namespace cfu::systems
