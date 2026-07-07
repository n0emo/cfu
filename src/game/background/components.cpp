#include "./components.hpp"

#include <array>

namespace cfu::comp {

template<>
void ComponentEditorWidget<BackgroundColor>(entt::registry& reg, entt::registry::entity_type e) {
    auto& c = reg.get<BackgroundColor>(e);
    auto colors = std::array<float, 4> {
        float(c.color.r) / 255.0f,
        float(c.color.g) / 255.0f,
        float(c.color.b) / 255.0f,
        float(c.color.a) / 255.0f,
    };
    ImGui::ColorPicker4("Color", colors.data());
    c.color.r = static_cast<unsigned char>(colors[0] * 255.0f);
    c.color.g = static_cast<unsigned char>(colors[1] * 255.0f);
    c.color.b = static_cast<unsigned char>(colors[2] * 255.0f);
    c.color.a = static_cast<unsigned char>(colors[3] * 255.0f);
}

} // namespace cfu::comp
