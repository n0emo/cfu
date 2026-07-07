#include "./utils.hpp"

#include "../constants.hpp"
#include "../raymath.hpp"
#include "../dev/components.hpp"

namespace cfu::dev {

auto mouse_ray(entt::registry& registry) -> Ray {
    const auto camera_entity = registry.view<Camera3D>().back();
    if (camera_entity == entt::null) return Ray {};
    const auto camera = registry.get<Camera3D>(camera_entity);
    const auto settings = registry.ctx().get<comp::DevSettings>();
    const auto position = GetMousePosition();

    if (settings.show_dev_panel) {
        const auto offset = Vector2(WINDOW_DEV_VIEWPORT_SECTION.x, WINDOW_DEV_VIEWPORT_SECTION.y);
        const auto offseted = position - offset;
        const auto width = int(WINDOW_DEV_VIEWPORT_SECTION.width);
        const auto height = int(WINDOW_DEV_VIEWPORT_SECTION.height);
        return GetScreenToWorldRayEx(offseted, camera, width, height);
    } else {
        return GetScreenToWorldRay(position, camera);
    }
}

} // namespace cfu::dev
