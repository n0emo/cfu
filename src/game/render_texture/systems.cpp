#include "./systems.hpp"

#include "../dev/components.hpp"
#include "../constants.hpp"
#include "./components.hpp"

namespace cfu::systems {

auto setup_main_render_texture(entt::registry& registry) -> void {
    auto texture = comp::MainRenderTexture {
        .texture = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT),
        .section = WINDOW_DEV_VIEWPORT_SECTION,
    };
    registry.ctx().insert_or_assign(texture);
}

auto destroy_main_render_texture(entt::registry& registry) -> void {
    auto texture = registry.ctx().get<comp::MainRenderTexture>();
    UnloadRenderTexture(texture.texture);
}

auto begin_main_render_texture(entt::registry& registry) -> void {
    auto texture = registry.ctx().get<comp::MainRenderTexture>();
    BeginTextureMode(texture.texture);
}

auto end_main_render_texture(entt::registry& registry) -> void {
    EndTextureMode();

    const auto settings = registry.ctx().get<comp::DevSettings>();
    const auto texture = registry.ctx().get<comp::MainRenderTexture>();
    auto source = Rectangle(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
    const auto dest = settings.show_dev_panel ? WINDOW_DEV_VIEWPORT_SECTION : source;
    source.height *= -1;
    DrawTexturePro(texture.texture.texture, source, dest, Vector2 {}, 0.0f, WHITE);
}

} // namespace cfu::systems
