#include "./state.hpp"

#include <raylib.h>

#include "components.hpp"
#include "../background/components.hpp"
#include "../background/systems.hpp"
#include "../states.hpp"

namespace cfu {

auto MainMenuState::on_enter(entt::registry& registry) -> void {
    TraceLog(LOG_INFO, "MainMenuState::on_enter");
    auto bg = registry.create();
    registry.emplace<comp::BackgroundColor>(bg, GetColor(0xA4A4DAFF));
    registry.emplace<comp::MainMenuTag>(bg);
}

auto MainMenuState::on_exit(entt::registry& registry) -> void {
    TraceLog(LOG_INFO, "MainMenuState::on_exit");
    auto view = registry.view<comp::MainMenuTag>();
    registry.destroy(view.begin(), view.end());
}

auto MainMenuState::update(entt::registry& registry) -> void {
    if (IsKeyPressed(KEY_SPACE)) {
        StateStack::get(registry).replace(InGameState {});
    }
}

auto MainMenuState::draw(entt::registry& registry) -> void {
    systems::draw_background_color(registry);
};

} // namespace cfu
