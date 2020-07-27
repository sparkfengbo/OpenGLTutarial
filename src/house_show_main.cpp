#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Shader.h"
#include "stb_image.h"
#include "Camera.h"
#include "utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "vector"
#include "string"

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

const unsigned int WINDOW_WIDTH = 600;
const unsigned int WINDOW_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;
bool mouseLeftPressed = false;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float skyboxVertices[] = {
        // 上左下顶点
        -1.0f, 1.0f, 1.0f,
        // 上右下顶点
        1.0f, 1.0f, 1.0f,
        // 上左上顶点
        -1.0f, 1.0f, -1.0f,
        // 上右上顶点
        1.0f, 1.0f, -1.0f,

        // 下左下顶点
        -1.0f, -1.0f, 1.0f,
        // 下右下顶点
        1.0f, -1.0f, 1.0f,
        // 下左上顶点
        -1.0f, -1.0f, -1.0f,
        // 下右上顶点
        1.0f, -1.0f, -1.0f,
};


unsigned int indices[] = {
        // Top
        1, 3, 0,
        0, 3, 2,

        // Bottom
        4, 6, 5,
        5, 6, 7,

        // Left
        0, 2, 4,
        4, 2, 6,

        // Right
        5, 7, 1,
        1, 7, 3,

        // Back
        5, 1, 4,
        4, 1, 0,

        // Front
        6, 2, 7,
        7, 2, 3
};

//float skyboxVertices[] = {
//        // positions
//        -1.0f,  1.0f, -1.0f,
//        -1.0f, -1.0f, -1.0f,
//        1.0f, -1.0f, -1.0f,
//        1.0f, -1.0f, -1.0f,
//        1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//
//        -1.0f, -1.0f,  1.0f,
//        -1.0f, -1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f,  1.0f,
//        -1.0f, -1.0f,  1.0f,
//
//        1.0f, -1.0f, -1.0f,
//        1.0f, -1.0f,  1.0f,
//        1.0f,  1.0f,  1.0f,
//        1.0f,  1.0f,  1.0f,
//        1.0f,  1.0f, -1.0f,
//        1.0f, -1.0f, -1.0f,
//
//        -1.0f, -1.0f,  1.0f,
//        -1.0f,  1.0f,  1.0f,
//        1.0f,  1.0f,  1.0f,
//        1.0f,  1.0f,  1.0f,
//        1.0f, -1.0f,  1.0f,
//        -1.0f, -1.0f,  1.0f,
//
//        -1.0f,  1.0f, -1.0f,
//        1.0f,  1.0f, -1.0f,
//        1.0f,  1.0f,  1.0f,
//        1.0f,  1.0f,  1.0f,
//        -1.0f,  1.0f,  1.0f,
//        -1.0f,  1.0f, -1.0f,
//
//        -1.0f, -1.0f, -1.0f,
//        -1.0f, -1.0f,  1.0f,
//        1.0f, -1.0f, -1.0f,
//        1.0f, -1.0f, -1.0f,
//        -1.0f, -1.0f,  1.0f,
//        1.0f, -1.0f,  1.0f
//};

unsigned int loadSkyBoxTexture(std::vector<std::string> faces) {
    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    int width, height, nChanles;
    for (unsigned int i =0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nChanles, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }
    return textureId;
}

int main() {
    glfwInit();
    //OpenGL 版本3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLTutarial", NULL, NULL);
    //一定在gladLoadGLLoader之前调用
    glfwMakeContextCurrent(window);

    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glEnable(GL_DEPTH_TEST);

    Shader skyBoxShader("../shaders/house_show_cube_map.vs", "../shaders/house_show_cube_map.fs");

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    unsigned int skyBoxVAO;
    unsigned int EBO;
    glGenVertexArrays(1, &skyBoxVAO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(skyBoxVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vector<string> faces{
        "../assets/room_show/virtual_room_1/4_r.jpg",
        "../assets/room_show/virtual_room_1/4_l.jpg",
        "../assets/room_show/virtual_room_1/4_u.jpg",
        "../assets/room_show/virtual_room_1/4_d.jpg",
        "../assets/room_show/virtual_room_1/4_f.jpg",
        "../assets/room_show/virtual_room_1/4_b.jpg"
    };

    unsigned int sykboxTextureId = loadSkyBoxTexture(faces);
    skyBoxShader.use();
    skyBoxShader.setUniformInt("skybox", 0);

    while(!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glDepthMask(GL_FALSE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        skyBoxShader.setUniformMat4("projection", projection);
//        skyBoxShader.setUniformMat4("view", glm::mat4(glm::mat3(camera.GetViewMatrix())));
        skyBoxShader.setUniformMat4("view", view);

        glBindVertexArray(skyBoxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, sykboxTextureId);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &skyBoxVAO);
    glDeleteBuffers(1, &VBO);
    skyBoxShader.del();
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            mouseLeftPressed = true;
        } else if (action == GLFW_RELEASE) {
            mouseLeftPressed = false;
        }
    }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (mouseLeftPressed) {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    } else {
        lastX = xpos;
        lastY = ypos;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}
