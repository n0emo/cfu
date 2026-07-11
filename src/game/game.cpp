#include "game.hpp"

#include <imgui.h>
#include <raylib.h>
#include <rlgl.h>

#include <rlImGui.h>

#include "./level/systems.hpp"
#include "./constants.hpp"
#include "./data/systems.hpp"
#include "./dev/systems.hpp"
#include "./physics/systems.hpp"
#include "./render_texture/systems.hpp"
#include "./shaders/systems.hpp"
#include "./states.hpp"
#include "./vox/systems.hpp"
#include "audio/systems.hpp"
#include "fonts/systems.hpp"
#include "textures/systems.hpp"

namespace cfu {

auto Game::init(Game& self) -> void {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Chimera Factory Unleash");
    SetTargetFPS(60);
    rlSetClipPlanes(20.0f, 5000.0f);
    rlImGuiSetup(true);

    systems::load_game_data_from_disk(self.registry);
    systems::reload_shaders(self.registry);
    systems::setup_level_cache(self.registry);

    systems::setup_vox_model_cache(self.registry);

    systems::setup_font_cache(self.registry);

    systems::setup_texture_cache(self.registry);

    systems::setup_audio(self.registry);

    systems::setup_main_render_texture(self.registry);

    StateStack::setup(self.registry);
    StateStack::get(self.registry).push(MainMenuState());

    systems::setup_physics(self.registry);
    systems::setup_dev(self.registry);
}

auto Game::deinit(Game& self) -> void {
    StateStack::get(self.registry).clear(self.registry);
    self.registry.clear();

    systems::destroy_main_render_texture(self.registry);
    rlImGuiEnd();
    systems::destroy_audio();
    CloseWindow();
}

auto Game::frame(this Game& self) -> void {
    StateStack::get(self.registry).update(self.registry);

    systems::update_audio(self.registry);
    systems::update_physics(self.registry);
    systems::update_dev(self.registry);

    BeginDrawing();
    ClearBackground(GetColor(0x181818ff));

    systems::begin_main_render_texture(self.registry);
    StateStack::get(self.registry).draw(self.registry);
    systems::end_main_render_texture(self.registry);

    rlImGuiBegin();
    systems::draw_dev(self.registry);
    rlImGuiEnd();

    EndDrawing();
}

auto Game::running(this const Game&) -> bool {
    return !WindowShouldClose();
}

} // namespace cfu
