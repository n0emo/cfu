#include "./components.hpp"

#include <entt/entt.hpp>

#include "../physics/components.hpp"
#include "../solids/components.hpp"
#include "../combat/components.hpp"
#include "../tilemap/components.hpp"
#include "../vox/resource.hpp"
#include "../vox/components.hpp"
#include "../data/components.hpp"

namespace cfu::comp {

using entt::operator""_hs;

auto create_player(entt::registry& registry, entt::entity entity) -> void {
    const auto& data = registry.ctx().get<comp::GameData>();
    const auto& desc = data.balance.player.evo_1;
    auto model = registry.ctx().get<res::VoxelModelCache>()[res::vox::Player];

    registry.emplace<Player>(entity);
    registry.emplace<cfu::comp::Transform>(
        entity,
        cfu::comp::Transform {
            .translation = Vector3(0.0f, 10.0f, 0.0f),
            .rotation = Vector3(0.0f, 1.0f, 0.0f),
            .scale = Vector3(4.0f, 4.0f, 4.0f),
        }
    );

    registry.emplace<Grounded>(entity, 0.0f);

    registry.emplace<Hp>(entity, float(desc.max_hp), float(desc.max_hp));
    registry.emplace<MoveSpeed>(entity, float(desc.move_speed));
    registry.emplace<MeleeAttack>(
        entity,
        MeleeAttack {
            .damage = float(desc.damage),
            .attack_speed = float(desc.attack_speed),
            .attack_radius = float(desc.attack_radius),
        }
    );

    registry.emplace<VoxelModel>(entity, model);
}

} // namespace cfu::comp
