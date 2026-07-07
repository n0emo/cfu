#include "./systems.hpp"

#include "./components.hpp"
#include "../physics/components.hpp"

namespace cfu::systems {

auto update_tilemap(entt::registry& registry) -> void {
    auto map_entity = registry.view<const comp::HeightMap>().back();
    if (map_entity == entt::null) return;
    const auto& map = registry.get<const comp::HeightMap>(map_entity);

    auto view = registry.view<const comp::Grounded, comp::Transform>();
    for (auto [entity, grounded, transform] : view.each()) {
        const auto height = map.get_height(transform.translation.x, transform.translation.z);
        transform.translation.y = grounded.y + height;
    }
}

} // namespace cfu::systems
