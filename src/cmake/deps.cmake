function(set_dependencies target)
    target_link_libraries(${target} PRIVATE
        Microsoft.GSL::GSL
        glfw
        raylib
        imgui
        rlimgui
        EnTT
        imgui_entt_entity_editor
        box2d
    )

    if(GAME_HOT_RELOAD)
        target_link_libraries(${target} PRIVATE cr box2dd)
    else()
        target_link_libraries(${target} PRIVATE cr box2d)
    endif()

    if(WIN32)
        target_link_libraries(${target} PRIVATE opengl32)
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        target_link_libraries(${target} PRIVATE
            "-framework Cocoa -framework CoreVideo -framework OpenGL"
        )
        target_link_libraries(${target} PRIVATE m)
    else()
        target_link_libraries(${target} PRIVATE m)
    endif()
endfunction()
