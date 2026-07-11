#pragma once

#include <string_view>
#include "entt/resource/cache.hpp"
#include "raylib.h"

namespace cfu::res {

namespace fonts {
    #define RES_FONT_ID_LIST                                                                                           \
    CFU_X(Roboto, "Roboto-VariableFont.ttf")                                                                           \
    CFU_X(Yuy, "YuyuShort-Regular.ttf")

    enum FontId {
        #define CFU_X(name, ...) name,
        RES_FONT_ID_LIST
        #undef CFU_X
    };

} // namespace fonts

struct CfuFont {
    Font font {};

    CfuFont(std::string_view path);
    CfuFont(CfuFont&& other) noexcept;
    auto operator=(CfuFont&& other) noexcept -> CfuFont&;
    ~CfuFont();

    CfuFont(const CfuFont&) = delete;
    auto operator=(const CfuFont&) -> CfuFont& = delete;

    operator Font();
};

using FontCache = entt::resource_cache<CfuFont>;

} // namespace cfu::res
