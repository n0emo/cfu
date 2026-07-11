#include "./systems.hpp"

#include <gsl/zstring>
#include "textures/resource.hpp"
#include <entt/entity/registry.hpp>
#include <raylib.h>

namespace cfu::systems {


    auto setup_texture_cache(entt::registry& registry) -> void {
        registry.ctx().insert_or_assign(res::TextureCache {});
        reload_textures(registry);
    }

    static auto reload_single_texture(res::TextureCache& cache, res::texture::TextureId id, gsl::czstring path) {
        auto [it, loaded] = cache.load(id, path);
        if (!loaded) *it->second.handle() = res::CfuTexture(path);
    }

    auto reload_textures(entt::registry& registry) -> void {
        auto& cache = registry.ctx().get<res::TextureCache>();
        #define CFU_X(name, path) reload_single_texture(cache, res::texture::name, path);
        RES_TEXTURE_ID_LIST
        #undef CFU_X
    }

    // auto draw_texrure(entt::registry& registry, Shader shader) -> void {
    //     //TODO
    // }

} // namespace cfu::systems
