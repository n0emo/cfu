#pragma once

#include <entt/entt.hpp>
#include <entt_editor.hpp>

namespace cfu::comp {

struct DevSettings {
    bool show_dev_panel = true;
};

using Editor = EntityEditor<entt::entity>;

struct CurrentEntity {
    entt::entity entity;
};

} // namespace cfu::comp
