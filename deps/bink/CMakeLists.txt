project(bink C CXX)

set(game_src_paths "${PROJECT_SOURCE_DIR}/win/*.c" "${PROJECT_SOURCE_DIR}/win/*.cpp" "${PROJECT_SOURCE_DIR}/win/*.h")

file(GLOB_RECURSE game_SRC ${game_src_paths})


add_library(bink SHARED ${game_SRC})
set(bink_flags "-D_REENTRANT  -D_GLIBCXX_USE_CXX11_ABI=0 -m64 --target=x86_64-unknown-linux-gnu -mbranches-within-32B-boundaries -O3 -DNDEBUG -D__RADFINAL__ -D USING_EGT -DWRAP_PUBLICS=Bink  -DBINKTEXTURESINDIRECTBINKCALLS -DBINKTEXTURESGPUAPITYPE -DINC_BINK2 -DSUPPORT_BINKGPU -DNO_BINK20 -DNO_BINK10_SUPPORT -DNO_BINK_BLITTERS -D__ggp__  -D__RADINSTATICLIB__ " )
set(CMAKE_CXX_FLAGS ${bink_flags})
set(CMAKE_C_FLAGS ${bink_flags})