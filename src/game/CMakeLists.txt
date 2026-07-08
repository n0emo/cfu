include(../cmake/deps.cmake)

if(GAME_DEV_MODE)
    add_library(${PROJECT_NAME}-game MODULE)
else()
    add_library(${PROJECT_NAME}-game STATIC)
endif()

target_sources(${PROJECT_NAME}-game PRIVATE
    ./background/components.cpp
    ./background/systems.cpp
    ./camera/systems.cpp
    ./combat/components.cpp
    ./data/components.cpp
    ./data/systems.cpp
    ./dev/systems.cpp
    ./dev/utils.cpp
    ./game.cpp
    ./in_game/state.cpp
    ./main_menu/state.cpp
    ./physics/components.cpp
    ./physics/systems.cpp
    ./player/components.cpp
    ./player/systems.cpp
    ./render_texture/systems.cpp
    ./shapes/components.cpp
    ./shapes/systems.cpp
    ./solids/components.cpp
    ./solids/systems.cpp
    ./states.cpp
    ./tilemap/components.cpp
    ./tilemap/systems.cpp
    ./vox/resource.cpp
    ./vox/systems.cpp
)

target_include_directories(${PROJECT_NAME}-game PUBLIC .)

set_target_properties(${PROJECT_NAME}-game PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_compile_definitions(${PROJECT_NAME}-game PRIVATE
    -DGAME_DEV_MODE=$<BOOL:${GAME_DEV_MODE}>
)

if(MSVC)
    target_compile_options(${PROJECT_NAME}-game PRIVATE /W3 /EHsc)
else()
    target_compile_options(${PROJECT_NAME}-game PRIVATE -Wall -Wextra -g)
endif()

set_dependencies(${PROJECT_NAME}-game)

if(GAME_DEV_MODE)
    set_target_properties(${PROJECT_NAME}-game PROPERTIES OUTPUT_NAME plugin)
    target_sources(${PROJECT_NAME}-game PRIVATE plugin.cpp)
endif()
