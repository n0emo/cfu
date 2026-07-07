#include "./components.hpp"

namespace cfu::comp {

template<>
void ComponentEditorWidget<Hp>(entt::registry& reg, entt::registry::entity_type e) {
    auto& hp = reg.get<Hp>(e);
    ImGui::SeparatorText("HP");
    ImGui::DragFloat("Max##HP", &hp.max, 1.0f, 0.0f, 9999.0f, "%.0f");
    ImGui::DragFloat("Current##HP", &hp.current, 1.0f, 0.0f, hp.max, "%.0f");
}

template<>
void ComponentEditorWidget<MoveSpeed>(entt::registry& reg, entt::registry::entity_type e) {
    auto& move_speed = reg.get<MoveSpeed>(e);
    ImGui::SeparatorText("Move Speed");
    ImGui::DragFloat("Value##MoveSpeed", &move_speed.value, 1.0f, 0.0f, 999.0f, "%.0f");
}

template<>
void ComponentEditorWidget<MeleeAttack>(entt::registry& reg, entt::registry::entity_type e) {
    auto& attack = reg.get<MeleeAttack>(e);
    ImGui::SeparatorText("Melee Attack");
    ImGui::DragFloat("Damage##MeleeAttack", &attack.damage, 1.0f, 1.0f, 999.0f, "%.0f");
    ImGui::DragFloat("Radius##MeleeAttack", &attack.attack_radius, 1.0f, 0.0f, 999.0f, "%.0f");
    ImGui::DragFloat("Speed##MeleeAttack", &attack.attack_speed, 0.1f, 0.1f, 99.0f, "%.1f");
}

} // namespace cfu::comp
