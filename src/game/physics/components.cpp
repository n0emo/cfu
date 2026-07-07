#include "./components.hpp"

#include "../raymath.hpp"

namespace cfu::comp {

template<>
void ComponentEditorWidget<Transform>(entt::registry& reg, entt::registry::entity_type e) {
    auto& transform = reg.get<Transform>(e);
    ImGui::SeparatorText("Translation");
    ImGui::DragFloat("X##Translation", &transform.translation.x, 0.1f);
    ImGui::DragFloat("Y##Translation", &transform.translation.y, 0.1f);
    ImGui::DragFloat("Z##Translation", &transform.translation.z, 0.1f);

    ImGui::SeparatorText("Rotation");
    Vector3 rotation = transform.rotation * 180.0f / M_PI;
    constexpr auto min = -180.0f;
    constexpr auto max = 180.0f;
    constexpr auto speed = 1.0f;
    constexpr auto flags = ImGuiSliderFlags_WrapAround;
    constexpr auto fmt = "%.0f";
    ImGui::DragFloat("X##Rotation", &rotation.x, speed, min, max, fmt, flags);
    ImGui::DragFloat("Y##Rotation", &rotation.y, speed, min, max, fmt, flags);
    ImGui::DragFloat("Z##Rotation", &rotation.z, speed, min, max, fmt, flags);
    transform.rotation = rotation / 180.0f * M_PI;

    ImGui::SeparatorText("Scale");
    ImGui::DragFloat("X##Scale", &transform.scale.x, 0.01f);
    ImGui::DragFloat("Y##Scale", &transform.scale.y, 0.01f);
    ImGui::DragFloat("Z##Scale", &transform.scale.z, 0.01f);
}

} // namespace cfu::comp
