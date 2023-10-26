cmake_minimum_required(VERSION 3.22)
project(theta3 C CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS FALSE)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE STRING "don't update every time")

option(BUILD_DOCS "Build doxygen documentation" OFF)
option(ONLINE "Enable online features" OFF)

add_subdirectory(deps/fmod)
if (ONLINE)
add_compile_definitions(ONLINE)
add_subdirectory(deps/eos)
endif()

include("cmake/common_deps.cmake")


if (BUILD_DOCS)
    include("cmake/build_docs.cmake")
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include("cmake/platform_macos.cmake")
elseif (DEFINED ENV{VITASDK})
    include("cmake/platform_vita.cmake")
else()
    include("cmake/platform_windows.cmake")
endif()

include_directories(deps/cereal)

if (ONLINE)
list(APPEND game_libs "eos")
endif()

target_link_libraries(theta3 PRIVATE ${game_libs})
target_compile_definitions(theta3 PRIVATE _CRT_SECURE_NO_WARNINGS=1)

# copy game data only in release
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(theta3 PRIVATE DEBUG=1)
else()
endif()
    add_custom_command(TARGET theta3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:theta3>/data
    COMMENT "Copying assets")