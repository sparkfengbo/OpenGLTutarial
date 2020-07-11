cmake_minimum_required(VERSION 3.16)
project(OpenGLTutarial)

set(CMAKE_CXX_STANDARD 14)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        glfw
        glad
        glm
        )

set(SRC
        src/stb_image.cpp
        src/Shader.cpp
        src/main.cpp
        )

include_directories(
        src/
        external/glfw/include/
        external/glad/include/
#        external/glm/include/


)

find_package(OpenGL REQUIRED)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/glm)

add_executable(OpenGLTutarial ${SRC})

target_link_libraries(OpenGLTutarial ${ALL_LIBS})

