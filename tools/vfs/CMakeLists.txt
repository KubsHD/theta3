project(vfs)

set(vfs_src_paths "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.c" "${PROJECT_SOURCE_DIR}/src/*.h" "${PROJECT_SOURCE_DIR}/src/*.rc" "${PROJECT_SOURCE_DIR}/src/*.cur")
file(GLOB_RECURSE vfs_SRC ${vfs_src_paths})

add_library(vfs STATIC ${vfs_SRC})

target_include_directories(
  vfs PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src"
)