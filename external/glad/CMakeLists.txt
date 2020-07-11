cmake_minimum_required(VERSION 3.16)

project(GLAD)

set(SRC
        src/glad.c)

set(INCLUDE
        include/glad/glad.h
        include/KHR/khrplatform.h)
#set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_library(glad
        ${SRC}
        ${INCLUDE}
        )

#add_definitions(-DENABLE_OPENGL)
