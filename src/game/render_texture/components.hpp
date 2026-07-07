#pragma once

#include <raylib.h>

namespace cfu::comp {

struct MainRenderTexture {
    RenderTexture2D texture;
    Rectangle section;
};

} // namespace cfu::comp
