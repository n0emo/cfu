#include "./components.hpp"

#include "../physics/components.hpp"
#include "../solids/components.hpp"
#include "../combat/components.hpp"
#include "../tilemap/components.hpp"
#include "../constants.hpp"

namespace cfu::comp {

auto create_player(entt::registry& registry, entt::entity entity) -> void {
    const auto desc = PLAYER_STATS_DESCS[0];

    registry.emplace<Player>(entity);
    registry.emplace<cfu::comp::Transform>(
        entity,
        cfu::comp::Transform {
            .translation = Vector3(0.0f, 10.0f, 0.0f),
            .rotation = Vector3(),
            .scale = Vector3(1.0f, 1.0f, 1.0f),
        }
    );

    registry.emplace<Grounded>(entity, 0.0f);

    registry.emplace<Hp>(entity, desc.max_hp, desc.max_hp);
    registry.emplace<MoveSpeed>(entity, desc.move_speed);
    registry.emplace<MeleeAttack>(
        entity,
        MeleeAttack {
            .damage = desc.damage,
            .attack_speed = desc.attack_speed,
            .attack_radius = desc.attack_radius,
        }
    );

    registry.emplace<Cube>(entity, 32.0f, 64.0f, 32.0f);
    registry.emplace<SolidMaterial>(entity, RED);
}

} // namespace cfu::comp
