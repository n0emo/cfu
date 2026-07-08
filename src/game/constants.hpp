#pragma once

#include <raylib.h>

namespace cfu {

constexpr auto WINDOW_WIDTH = 720;
constexpr auto WINDOW_HEIGHT = 720;
constexpr auto WINDOW_DEV_WIDTH = 1600;
constexpr auto WINDOW_DEV_HEIGHT = 900;

constexpr auto WINDOW_DEV_VIEWPORT_SECTION = Rectangle {
    .x = (WINDOW_DEV_WIDTH - WINDOW_WIDTH) * 0.5f,
    .y = (WINDOW_DEV_HEIGHT - WINDOW_HEIGHT) * 0.5f,
    .width = WINDOW_WIDTH,
    .height = WINDOW_HEIGHT,
};

constexpr auto B2_STEPS = 4;

constexpr auto TILE_SIZE = 32;

constexpr auto BALANCE_DATA_PATH = "assets/data/balance.json";
constexpr auto LEVEL_DATA_PATH_FMT = "assets/data/level-{}.json";

} // namespace cfu
