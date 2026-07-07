#include "./components.hpp"

namespace cfu::comp {

template<>
void ComponentEditorWidget<SolidMaterial>(entt::registry& reg, entt::registry::entity_type e) {
    auto& c = reg.get<SolidMaterial>(e);
    auto color = ColorNormalize(c.color);
    ImGui::ColorPicker4("Color", reinterpret_cast<float *>(&color)); // NOLINT
    c.color = ColorFromNormalized(color);
}

template<>
void ComponentEditorWidget<Cube>(entt::registry& reg, entt::registry::entity_type e) {
    auto& c = reg.get<Cube>(e);
    ImGui::DragFloat("Width", &c.size.x);
    ImGui::DragFloat("Height", &c.size.y);
    ImGui::DragFloat("Length", &c.size.z);
}

} // namespace cfu::comp
