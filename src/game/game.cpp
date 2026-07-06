#include "game.hpp"

#include <imgui.h>
#include <raylib.h>

#include <rlImGui.h>

#include "./constants.hpp"
#include "./dev/systems.hpp"
#include "./physics/systems.hpp"
#include "./states.hpp"

namespace game {

auto Game::init(Game& self) -> void {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cmake");
    SetTargetFPS(60);
    InitAudioDevice();
    rlImGuiSetup(true);

    StateStack::setup(self.registry);
    StateStack::get(self.registry).push(MainMenuState());

    systems::setup_physics(self.registry);
    systems::setup_dev(self.registry);
}

auto Game::deinit(Game& self) -> void {
    StateStack::get(self.registry).clear(self.registry);
    self.registry.clear();

    rlImGuiEnd();
    CloseAudioDevice();
    CloseWindow();
}

auto Game::frame(this Game& self) -> void {
    StateStack::get(self.registry).update(self.registry);

    systems::update_physics(self.registry);
    systems::update_dev(self.registry);

    BeginDrawing();
    ClearBackground(RED);

    rlImGuiBegin();
    StateStack::get(self.registry).draw(self.registry);
    systems::draw_dev(self.registry);
    rlImGuiEnd();

    EndDrawing();
}

auto Game::running(this const Game&) -> bool {
    return !WindowShouldClose();
}

} // namespace game
