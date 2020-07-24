cmake_minimum_required(VERSION 3.16)
project(OpenGLTutarial)

set(CMAKE_CXX_STANDARD 14)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        glfw
        glad
        glm
        assimp
        )

set(BOX_SRC
        src/stb_image.cpp
        src/Shader.cpp
        src/box_main.cpp
        src/Mesh.cpp
        src/Model.cpp
        )


set(ASSIMP_SRC
        src/stb_image.cpp
        src/Shader.cpp
        src/assimp_main.cpp
        src/Mesh.cpp
        src/Model.cpp
        )

include_directories(
        src/
        external/glfw/include/
        external/glad/include/
        external/assimp/include/
#        external/glm/include/
)

find_package(OpenGL REQUIRED)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/glm)
add_subdirectory(external/assimp)

add_executable(Box ${BOX_SRC})
add_executable(ASSIMP ${ASSIMP_SRC})

target_link_libraries(Box ${ALL_LIBS})
target_link_libraries(ASSIMP ${ALL_LIBS})

