#include "./resource.hpp"

#include <rlgl.h>

#include <numbers>

#include "../camera/components.hpp"
#include "../data/components.hpp"
#include "../physics/components.hpp"
#include "../raymath.hpp"
#include "./components.hpp"

namespace cfu::systems {

auto setup_vox_model_cache(entt::registry& registry) -> void {
    registry.ctx().insert_or_assign(res::VoxelModelCache {});
}

static auto reload_single_model(res::VoxelModelCache& cache, res::vox::VoxelModelId id, gsl::czstring path) {
    auto [it, loaded] = cache.load(id, path);
    if (!loaded) *it->second.handle() = res::VoxelModel(path);
}

auto reload_voxel_models(entt::registry& registry) -> void {
    auto& cache = registry.ctx().get<res::VoxelModelCache>();
    #define CFU_X(name, path) reload_single_model(cache, res::vox::name, path);
    RES_VOX_ID_LIST
    #undef CFU_X
}

auto draw_voxel_models(entt::registry& registry) -> void {
    auto d = registry.ctx().get<comp::GameData>();
    auto camera_entity = registry.view<Camera3D, comp::CameraOffset>().back();
    if (camera_entity == entt::null) return;
    const auto camera_offset = registry.get<comp::CameraOffset>(camera_entity);
    const auto camera_position_3d = registry.get<Camera3D>(camera_entity).position - camera_offset.offset;
    const auto camera_position = Vector2(camera_position_3d.x, camera_position_3d.z);

    auto view = registry.view<comp::VoxelModel, comp::Transform>();
    for (auto [entity, model, transform] : view.each()) {
        const auto position_2d = Vector2(transform.translation.x, transform.translation.z);
        if (Vector2DistanceSqr(camera_position, position_2d) > d.balance.camera.box_culling) continue;

        const auto pitch = transform.rotation.x;
        const auto yaw = transform.rotation.y;
        const auto roll = transform.rotation.z;
        const auto quaternion = QuaternionFromEuler(pitch, yaw, roll);
        auto axis = Vector3 {};
        auto angle = float {};
        QuaternionToAxisAngle(quaternion, &axis, &angle);
        angle *= 180.0f / std::numbers::pi_v<float>;
        DrawModelEx(model.handle->model, transform.translation, axis, angle, transform.scale, WHITE);
    }
}

} // namespace cfu::systems
