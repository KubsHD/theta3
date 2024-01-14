#imgui


#FetchContent_MakeAvailable(imgui)

#add_subdirectory(deps/imgui)

#glm
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG master
)

FetchContent_MakeAvailable(glm)


#ldtk parser
FetchContent_Declare(
    LDtk
    GIT_REPOSITORY https://github.com/Madour/LDtkLoader
    GIT_TAG master
)

FetchContent_MakeAvailable(LDtk)

#luau
FetchContent_Declare(
    luau
    GIT_REPOSITORY https://github.com/luau-lang/luau
    GIT_TAG master
)

FetchContent_MakeAvailable(luau)


include_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/_deps/ldtk-src/include)