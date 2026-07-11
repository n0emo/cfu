#pragma once

#include <string_view>
#include "entt/resource/cache.hpp"
#include "raylib.h"

namespace cfu::res {

namespace texture {
    #define RES_TEXTURE_ID_LIST\
        CFU_X(placeholder, "png.png")                                                                                            \

        enum TextureId {

        #define CFU_X(name, ...) name,
            RES_TEXTURE_ID_LIST
        #undef CFU_X

        };

}

struct CfuTexture{
    Texture2D texture {};

    CfuTexture(std::string_view path);
    CfuTexture(CfuTexture&& other) noexcept;
    auto operator=(CfuTexture&& other) noexcept -> CfuTexture&;
    ~CfuTexture();

    CfuTexture(const CfuTexture&) = delete;
    auto operator=(const CfuTexture&) -> CfuTexture& = delete;

    operator Texture2D();
};

using TextureCache = entt::resource_cache<CfuTexture>;

} // namespace cfu::res
