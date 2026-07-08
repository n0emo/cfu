#pragma once

#include <memory>

#include <entt/resource/resource.hpp>
#include <entt/entity/registry.hpp>
#include <entt/resource/cache.hpp>
#include <gsl/gsl>
#include <raylib.h>

namespace cfu::res {

namespace vox {

#define RES_VOX_ID_LIST                                                                                                \
    CFU_X(Door, "door.vox")                                                                                            \
    CFU_X(Door2, "door2.vox")                                                                                          \
    CFU_X(Floor, "floor.vox")                                                                                          \
    CFU_X(Player, "player.vox")                                                                                        \
    CFU_X(Stair, "stair.vox")                                                                                          \
    CFU_X(Wall, "wall.vox")

    enum VoxelModelId {

    #define CFU_X(name, ...) name,
        RES_VOX_ID_LIST
    #undef CFU_X

    };

} // namespace vox

struct VoxelModel {
    Model model {};
    BoundingBox bounding_box {};
    std::string path {};

    VoxelModel(std::string_view path);
    VoxelModel(VoxelModel&& other) noexcept;
    auto operator=(VoxelModel&& other) noexcept -> VoxelModel&;
    ~VoxelModel();

    VoxelModel(const VoxelModel&) = delete;
    auto operator=(const VoxelModel&) -> VoxelModel& = delete;

    operator Model();
};

using VoxelModelCache = entt::resource_cache<VoxelModel>;

} // namespace cfu::res
