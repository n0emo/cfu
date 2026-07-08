#pragma once

#include <raylib.h>

namespace cfu::comp {

struct CameraLerp {
    float amount {};
};

struct CameraOffset {
    Vector3 offset {};
};

} // namespace cfu::comp
