#include "./systems.hpp"
#include "./components.hpp"

namespace cfu::systems {

auto draw_background_color(entt::registry& registry) -> void {
    auto view = registry.view<const comp::BackgroundColor>();
    for (auto [entity, color] : view.each()) {
        ClearBackground(color.color);
    }
}

} // namespace cfu::systems
