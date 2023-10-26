FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.24.1
)



FetchContent_MakeAvailable(SDL)

set(game_src_paths "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.c" "${PROJECT_SOURCE_DIR}/src/*.h" "${PROJECT_SOURCE_DIR}/src/*.rc" "${PROJECT_SOURCE_DIR}/src/*.cur")
file(GLOB_RECURSE game_SRC ${game_src_paths})

#set_source_files_properties(game_SRC PROPERTIES LANGUAGE CXX)

#set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/src/platform/windows/theta.rc")

# don't show console in release build
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(theta3 
        ${game_SRC}
        ${APP_ICON_RESOURCE_WINDOWS}
    )
else()
    add_executable(theta3 WIN32
        ${game_SRC}
        ${APP_ICON_RESOURCE_WINDOWS}
    )
endif()

target_compile_definitions(theta3 PRIVATE APPLE=1)
target_include_directories(theta3 PUBLIC "${PROJECT_SOURCE_DIR}/src")

# copy dlls
# add_custom_command(
#     TARGET theta3 POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:theta3> $<TARGET_FILE_DIR:theta3>
#     COMMAND_EXPAND_LISTS
# )

set(game_libs "glm" "fmod" "SDL2main" "SDL2-static")
