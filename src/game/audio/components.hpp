#pragma once

#include "audio/resource.hpp"
#include "entt/resource/resource.hpp"
namespace cfu::comp {

// TODO: CfuMusic component
// TODO: CfuSound component

struct CfuMusic{
    entt::resource<res::CfuMusic> handle;
};

struct CfuSound{
    entt::resource<res::CfuSound> handle;
};

} // namespace cfu::comp
