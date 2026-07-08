#include "game.hpp"

#include <imgui.h>
#include <raylib.h>

#include <rlImGui.h>

#include "./constants.hpp"
#include "./dev/systems.hpp"
#include "./physics/systems.hpp"
#include "./data/systems.hpp"
#include "./render_texture/systems.hpp"
#include "./states.hpp"

namespace cfu {

auto Game::init(Game& self) -> void {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cmake");
    SetTargetFPS(60);
    InitAudioDevice();
    rlImGuiSetup(true);

    systems::load_game_data_from_disk(self.registry);

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
    CloseAudioDevice();
    CloseWindow();
}

auto Game::frame(this Game& self) -> void {
    StateStack::get(self.registry).update(self.registry);

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
