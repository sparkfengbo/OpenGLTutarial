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
        src/Camera.h
        )


set(ASSIMP_SRC
        src/stb_image.cpp
        src/Shader.cpp
        src/assimp_main.cpp
        src/Mesh.cpp
        src/Model.cpp
        src/Camera.h
        )

set(LIGHT_SRC
        src/stb_image.cpp
        src/Shader.cpp
        src/light_main.cpp
        src/Mesh.cpp
        src/Model.cpp
        src/Camera.h
        src/utils.h
        )

set(HOUSE_SHOW_SRC
        src/stb_image.cpp
        src/stb_image_write.cpp
        src/Shader.cpp
        src/house_show_main.cpp
        src/Mesh.cpp
        src/Model.cpp
        src/Camera.h
        src/utils.h
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
add_executable(LIGHT ${LIGHT_SRC})
add_executable(HOUSE_SHOW ${HOUSE_SHOW_SRC})

target_link_libraries(Box ${ALL_LIBS})
target_link_libraries(ASSIMP ${ALL_LIBS})
target_link_libraries(LIGHT ${ALL_LIBS})
target_link_libraries(HOUSE_SHOW ${ALL_LIBS})

