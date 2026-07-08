#include "./components.hpp"

#include <nlohmann/json.hpp>

namespace cfu::comp {

void to_json(json& j, const PlayerEvo1Data& d) {
    j = json {
        {"max_hp", d.max_hp},
        {"move_speed", d.move_speed},
        {"damage", d.damage},
        {"attack_speed", d.attack_speed},
        {"attack_radius", d.attack_radius},
    };
}

void from_json(const json& j, PlayerEvo1Data& d) {
    d.max_hp = j.value("max_hp", 0);
    d.move_speed = j.value("move_speed", 0);
    d.damage = j.value("damage", 0);
    d.attack_speed = j.value("attack_speed", 0);
    d.attack_radius = j.value("attack_radius", 0);
}

void to_json(json& j, const PlayerEvo2Data& d) {
    j = json {
        {"max_hp", d.max_hp},
        {"move_speed", d.move_speed},
        {"damage", d.damage},
        {"attack_speed", d.attack_speed},
        {"attack_radius", d.attack_radius},
    };
}

void from_json(const json& j, PlayerEvo2Data& d) {
    d.max_hp = j.value("max_hp", 0);
    d.move_speed = j.value("move_speed", 0);
    d.damage = j.value("damage", 0);
    d.attack_speed = j.value("attack_speed", 0);
    d.attack_radius = j.value("attack_radius", 0);
}

void to_json(json& j, const PlayerEvo3Data& d) {
    j = json {
        {"max_hp", d.max_hp},
        {"move_speed", d.move_speed},
        {"damage", d.damage},
        {"attack_speed", d.attack_speed},
        {"attack_radius", d.attack_radius},
    };
}

void from_json(const json& j, PlayerEvo3Data& d) {
    d.max_hp = j.value("max_hp", 0);
    d.move_speed = j.value("move_speed", 0);
    d.damage = j.value("damage", 0);
    d.attack_speed = j.value("attack_speed", 0);
    d.attack_radius = j.value("attack_radius", 0);
}

void to_json(json& j, const PlayerData& d) {
    j = json {
        {"evo_1", d.evo_1},
        {"evo_2", d.evo_2},
        {"evo_3", d.evo_3},
    };
}

void from_json(const json& j, PlayerData& d) {
    d.evo_1 = j.value("evo_1", PlayerEvo1Data {});
    d.evo_2 = j.value("evo_2", PlayerEvo2Data {});
    d.evo_3 = j.value("evo_3", PlayerEvo3Data {});
}

void to_json(json& j, const CameraData& d) {
    j = json {
        {"box_culling", d.box_culling},
        {"lerp", d.lerp},
        {"offset_x", d.offset.x},
        {"offset_y", d.offset.y},
        {"offset_z", d.offset.z},
        {"up_x", d.up.x},
        {"up_y", d.up.y},
        {"up_z", d.up.z},
        {"fovy", d.fovy},
    };
}

void from_json(const json& j, CameraData& d) {
    d.box_culling = j.value("box_culling", 0.0f);
    d.lerp = j.value("lerp", 0.0f);
    d.offset.x = j.value("offset_x", 0.0f);
    d.offset.y = j.value("offset_y", 0.0f);
    d.offset.z = j.value("offset_z", 0.0f);
    d.up.x = j.value("up_x", 0.0f);
    d.up.y = j.value("up_y", 0.0f);
    d.up.z = j.value("up_z", 0.0f);
    d.fovy = j.value("fovy", 0.0f);
}

void to_json(json& j, const BalanceData& d) {
    j = json {
        {"player", d.player},
        {"camera", d.camera},
    };
}

void from_json(const json& j, BalanceData& d) {
    d.player = j.value("player", PlayerData {});
    d.camera = j.value("camera", CameraData {});
}

void to_json(json& j, const TileData& d) {
    j = json {
        {"x", d.x},
        {"y", d.y},
        {"z", d.z},
        {"kind", tile_kind_to_string(d.kind)},
        {"rotation", tile_rotation_to_string(d.rotation)},
    };
}

void from_json(const json& j, TileData& d) {
    d.x = j.value("x", 0);
    d.y = j.value("y", 0);
    d.z = j.value("z", 0);
    d.kind = tile_kind_from_string(j.value("kind", "wall"));
    d.rotation = tile_rotation_from_string(j.value("rotation", "none"));
}

void to_json(json& j, const LevelData& d) {
    j = json {
        {"map_size_x", d.map_size_x},
        {"map_size_y", d.map_size_y},
        {"map_size_z", d.map_size_z},
        {"map_tiles", d.map_tiles},
    };
}

void from_json(const json& j, LevelData& d) {
    d.map_size_x = j.value("map_size_x", 0);
    d.map_size_y = j.value("map_size_y", 0);
    d.map_size_z = j.value("map_size_z", 0);
    d.map_tiles = j.value("map_tiles", std::vector<TileData> {});
}

} // namespace cfu::comp
