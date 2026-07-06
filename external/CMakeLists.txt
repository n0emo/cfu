include(FetchContent)

set(CR_VERSION 1c3f8302320dee8206cf85d6aeb9e9a9cd78b527)
set(RAYLIB_VERSION 6.0)
set(IMGUI_VERSION 1.92.8)
set(RLIMGUI_VERSION Raylib_6_0)
set(ENTT_VERSION 3.16.0)
set(GSL_VERSION 4.2.2)
set(ENTT_EDITOR_VERSION entt_v3.12.2)
set(EDYN_VERSION 1.3.1)

set(FETCHCONTENT_QUIET ON)

macro(fetch name)
  FetchContent_GetProperties(${name})
  if(NOT ${name}_POPULATED)
    message(STATUS "Downloading ${name}")
    FetchContent_MakeAvailable(${name})
  endif()
endmacro()

# cr.h
FetchContent_Declare(
    cr
    GIT_REPOSITORY https://github.com/fungos/cr
    GIT_TAG ${CR_VERSION}
)

# Raylib
set(CUSTOMIZE_BUILD ON CACHE INTERNAL "")
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_Declare(
    raylib
    URL "https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.zip"
)

# Dear ImGui
FetchContent_Declare(
    imgui
    URL "https://github.com/ocornut/imgui/archive/refs/tags/v${IMGUI_VERSION}.zip"
)

# RlImGui
FetchContent_Declare(
    rlimgui
    URL "https://github.com/raylib-extras/rlImGui/archive/refs/tags/${RLIMGUI_VERSION}.zip"
)

# EnTT
FetchContent_Declare(
    entt
    URL "https://github.com/skypjack/entt/archive/refs/tags/v${ENTT_VERSION}.zip"
)

# Microsoft GSL
FetchContent_Declare(
    gsl
    URL "https://github.com/microsoft/GSL/archive/refs/tags/v${GSL_VERSION}.zip"
)

# ImGui EnTT Editor
FetchContent_Declare(
    entt-editor
    URL "https://github.com/Green-Sky/imgui_entt_entity_editor/archive/refs/tags/${ENTT_EDITOR_VERSION}.zip"
)

fetch(cr)
fetch(raylib)
fetch(imgui)
fetch(rlimgui)
fetch(entt)
fetch(gsl)
fetch(entt-editor)

include(./imgui.cmake)
include(./rlimgui.cmake)
