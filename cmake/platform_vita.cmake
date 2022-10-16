
set(VITA_APP_NAME "Theta2")
set(VITA_TITLEID  "PIWO00002")
set(VITA_VERSION  "01.00")


if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
    set(VITA)
else()
    set(VITA OFF)
endif()


include_directories("deps/fmod/vita")
include_directories("$ENV{VITASDK}/arm-vita-eabi/include/SDL2")

list(APPEND game_libs
    c
    "SDL2"
    "z"
    "pthread"
    "jpeg"
    SceGxm_stub
    SceDisplay_stub
    SceCtrl_stub
    SceAppMgr_stub
    SceAudio_stub
    SceAudioIn_stub
    SceSysmodule_stub
    SceDisplay_stub
    SceCtrl_stub
    SceIofilemgr_stub
    SceCommonDialog_stub
    SceTouch_stub
    SceHid_stub
    SceMotion_stub
    ScePower_stub
    SceProcessmgr_stub
    m
)   # don't link SDL2main on xbox since it uses a c++ entrypoint

target_compile_definitions(theta2 PRIVATE VITA=1)


include("${VITASDK}/share/vita.cmake" REQUIRED)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
    VERSION ${VITA_VERSION}
    NAME ${VITA_APP_NAME}
    FILE data data
    FILE src/platform/vita/sce_sys sce_sys
)