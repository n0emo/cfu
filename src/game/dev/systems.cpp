#include "./systems.hpp"

#include <imgui.h>
#include <raylib.h>

#include "../constants.hpp"
#include "../raymath.hpp"
#include "../shaders/systems.hpp"
#include "../states.hpp"
#include "../vox/systems.hpp"
#include "./components.hpp"
#include "audio/systems.hpp"
#include "fonts/systems.hpp"
#include "textures/systems.hpp"

namespace cfu::systems {

auto setup_dev(entt::registry& registry) -> void {
    registry.ctx().insert_or_assign(comp::DevSettings {});

    auto font = ImGui::GetIO().Fonts->AddFontFromFileTTF("./assets/fonts/RobotoMono-VariableFont.ttf");
    ImGui::GetIO().FontDefault = font;

    setup_entt_editor(registry);
    setup_tilemap_editor(registry);
    setup_data_editor(registry);
    setup_console(registry);
}

auto update_dev(entt::registry& registry) -> void {
    auto& settings = registry.ctx().get<comp::DevSettings>();
    if (IsKeyPressed(KEY_F3)) settings.show_dev_panel = !settings.show_dev_panel;
}

auto draw_dev(entt::registry& registry) -> void {
    auto& settings = registry.ctx().get<comp::DevSettings>();
    if (!GAME_DEV_MODE) settings.show_dev_panel = false;

    if (settings.show_dev_panel) {
        SetWindowSize(WINDOW_DEV_WIDTH, WINDOW_DEV_HEIGHT);
    } else {
        SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        return;
    }
    if (IsKeyPressed(KEY_F1)) {
        systems::reload_shaders(registry);
        systems::reload_voxel_models(registry);
        systems::reload_fonts(registry);
        systems::reload_textures(registry);
        systems::reload_audio(registry);
    }

    draw_dev_panel(registry);
    draw_entt_editor(registry);
    draw_tilemap_editor(registry);
    draw_data_editor(registry);
    draw_console(registry);
}

} // namespace cfu::systems
