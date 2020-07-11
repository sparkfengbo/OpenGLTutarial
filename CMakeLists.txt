cmake_minimum_required(VERSION 3.16)
project(OpenGLTutarial)

set(CMAKE_CXX_STANDARD 14)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        glfw
        glad
        )

include_directories(
        src/
        external/glfw/include/
        external/glad/include/
)

find_package(OpenGL REQUIRED)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)

add_executable(OpenGLTutarial src/main.cpp)

target_link_libraries(OpenGLTutarial ${ALL_LIBS})

