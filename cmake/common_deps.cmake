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

