#pragma once

#include <entt/entity/registry.hpp>
#include <entt_editor.hpp>

#include "../tilemap/components.hpp"

namespace cfu::comp {

struct DevSettings {
    bool show_dev_panel = true;
};

using Editor = EntityEditor<entt::entity>;

struct CurrentEntity {
    entt::entity entity;
};

enum class TileMapEditorMode {
    Free,
    Selecting,
    Placing,
    Erasing,
};

struct TileMapEditor {
    bool show = false;
    bool enabled = false;
    TileMapEditorMode mode = TileMapEditorMode::Free;
    TileKind current_tile = TileKind::Wall;
};

} // namespace cfu::comp
