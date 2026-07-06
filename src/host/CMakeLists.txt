include(../cmake/deps.cmake)

add_executable(${PROJECT_NAME}-host)

target_sources(${PROJECT_NAME}-host PRIVATE
    main.cpp
)

set_target_properties(${PROJECT_NAME}-host PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    OUTPUT_NAME game
)

target_compile_definitions(${PROJECT_NAME}-host PRIVATE
    -DGAME_HOT_RELOAD=$<BOOL:${GAME_HOT_RELOAD}>
)

set_dependencies(${PROJECT_NAME}-host)

if(NOT GAME_HOT_RELOAD)
    target_link_libraries(${PROJECT_NAME}-host PRIVATE ${PROJECT_NAME}-game)
endif()

if(EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME}-host PROPERTIES
        OUTPUT_NAME index
        SUFFIX ".html"
    )

    target_link_options(${PROJECT_NAME}-host PRIVATE
        "-sALLOW_MEMORY_GROWTH=1"
        "-sASYNCIFY"
        "-sUSE_GLFW=3"
        "-sINITIAL_MEMORY=1024MB"
        "-sALLOW_MEMORY_GROWTH=0"
        "--shell-file=${CMAKE_CURRENT_SOURCE_DIR}/minshell.html"
    )
endif()

if(MINGW)
    target_link_options(${PROJECT_NAME}-host PRIVATE
        -static -static-libgcc -static-libstdc++
    )
endif()

if(GAME_HOT_RELOAD)
    if (WIN32)
	add_custom_command(TARGET ${PROJECT_NAME}-host POST_BUILD
	    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}-host> $<TARGET_FILE_DIR:${PROJECT_NAME}-host>
	    COMMAND_EXPAND_LISTS
	)
    endif()
endif()
