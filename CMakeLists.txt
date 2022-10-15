project(theta2)
cmake_minimum_required(VERSION 3.16)

set(VITA_APP_NAME "Theta2")
set(VITA_TITLEID  "PIWO00002")
set(VITA_VERSION  "01.00")


if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
    set(VITA)
else()
    set(VITA OFF)
endif()

project(theta)
include(FetchContent)

set(BUILD_SHARED_LIBS FALSE)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE STRING "don't update every time")

option(BUILD_DOCS "Build doxygen documentation" OFF)



#set(CMAKE_CXX_FLAGS "-Wall")
#set(CMAKE_CXX_FLAGS_DEBUG "-g -Wl -q")
#set(CMAKE_CXX_FLAGS_RELEASE "-Wl -q")
set(CPPWINRT_REQUIRED_COMPILER_FLAGS "/std:c++latest /await")

if (VITA)
    #add_subdirectory(deps/fakemod)

else()
    #SDL
    FetchContent_Declare(
        SDL
        GIT_REPOSITORY https://github.com/libsdl-org/SDL
        GIT_TAG release-2.24.1
    )

    FetchContent_MakeAvailable(SDL)

endif()
#glm


FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG master
)

FetchContent_MakeAvailable(glm)

add_subdirectory(deps/fmod)
add_subdirectory(deps/eos)
# imgui

set(BUILD_SHARED_LIBS FALSE)
set(IMGUI_STATIC "yes")

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/Pesc0/imgui-cmake
    GIT_TAG master
)

#FetchContent_MakeAvailable(imgui)




if (BUILD_DOCS)

    if (WIN32)
    set(DOXYGEN_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/tools/doxygen.exe)
    endif()

    find_package(Doxygen)

    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")

        # note the option ALL which allows to build the docs together with the application
        add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
    else (DOXYGEN_FOUND)
      message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif()


# set game sources according to platform

set(game_src_paths "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.h")

if(WINDOWS_STORE)
    list(APPEND game_src_paths "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.rc" "${PROJECT_SOURCE_DIR}/src/*.cur")
endif()

file(GLOB_RECURSE game_SRC ${game_src_paths})

set_source_files_properties(game_SRC PROPERTIES LANGUAGE CXX)


set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/src/platform/windows/theta.rc")

# don't show console in release build

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(theta2 
        ${game_SRC}
    )
else()
    add_executable(theta2 WIN32
        ${game_SRC}
        ${APP_ICON_RESOURCE_WINDOWS}
    )
endif()

target_include_directories(theta2 PUBLIC "${PROJECT_SOURCE_DIR}/src")

# link libraries

set(game_libs "glm" "fmod")

if(NOT WINDOWS_STORE)
    list(APPEND game_libs "SDL2main") # don't link SDL2main on xbox since it uses a c++ entrypoint
endif()


if(VITA)

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
else()
    list(APPEND game_libs SDL2-static eos)
    add_custom_command(TARGET theta2 POST_BUILD COMMAND ${CMAKE_COMMAND} -DDIR=${PROJECT_SOURCE_DIR} -DFILE=$<TARGET_FILE:theta2> -P ${PROJECT_SOURCE_DIR}/cmake/copy_dlls.cmake)
endif()


target_link_libraries(theta2 PRIVATE ${game_libs})
target_compile_definitions(theta2 PRIVATE _CRT_SECURE_NO_WARNINGS=1)
get_target_property(FMOD_BINARY_PATH fmod IMPORTED_LOCATION)

if (NOT VITA)
    # copy fmod dll
    add_custom_command(TARGET theta2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FMOD_BINARY_PATH} $<TARGET_FILE_DIR:theta2>
        COMMENT "Copying fmod")
endif()

# platform defines

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_compile_definitions(theta2 PRIVATE APPLE=1)
elseif (WINDOWS_STORE)
    target_compile_definitions(theta2 PRIVATE XBOX=1)
elseif (VITA)
    target_compile_definitions(theta2 PRIVATE VITA=1)
else()
    target_compile_definitions(theta2 PRIVATE WIN=1)
endif()

#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/PROFILE")

# copy game data only in release

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  # In non-win32 debug build, debug_malloc is on by default
  target_compile_definitions(theta2 PRIVATE DEBUG=1)
else()
    add_custom_command(TARGET theta2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:theta2>/data
    COMMENT "Copying assets")
endif()

if (VITA)

    include("${VITASDK}/share/vita.cmake" REQUIRED)

    vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
    vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
      VERSION ${VITA_VERSION}
      NAME ${VITA_APP_NAME}
      FILE data data
      FILE src/platform/vita/sce_sys sce_sys
    )
endif()
