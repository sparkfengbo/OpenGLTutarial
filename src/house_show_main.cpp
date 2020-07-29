#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Shader.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include "Camera.h"

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
const unsigned int WINDOW_HEIGHT = 1000;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;
bool mouseLeftPressed = false;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int window_width = WINDOW_WIDTH;
int window_height = WINDOW_HEIGHT;
bool vertical = true;

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


int loadSignalTexture(char const *filename) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
//    stbi_set_flip_vertically_on_load( true);
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
//        stbi_write_png(string(filename).append("test.png").c_str(), width, height, nrChannels, data, width * nrChannels);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return texture;
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
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);

    glClearColor(1.f, 0.1f, 0.1f, 0.0f);

    Shader virtualRoomShader("../shaders/house_show_cube_map.vs", "../shaders/house_show_cube_map.fs");
    Shader realRoomShader("../shaders/house_show_cube_map.vs", "../shaders/house_show_cube_map.fs");

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

    vector<string> virtualRoom1{
        "../assets/room_show/virtual_room_1/4_r.jpg",
        "../assets/room_show/virtual_room_1/4_l.jpg",
        "../assets/room_show/virtual_room_1/4_u.jpg",
        "../assets/room_show/virtual_room_1/4_d.jpg",
        "../assets/room_show/virtual_room_1/4_f.jpg",
        "../assets/room_show/virtual_room_1/4_b.jpg"
    };

    vector<string> realRoom1{
            "../assets/room_show/real_room_1/4_r.jpg",
            "../assets/room_show/real_room_1/4_l.jpg",
            "../assets/room_show/real_room_1/4_u.jpg",
            "../assets/room_show/real_room_1/4_d.jpg",
            "../assets/room_show/real_room_1/4_f.jpg",
            "../assets/room_show/real_room_1/4_b.jpg"
    };

//    vector<string> faces{
//            "../assets/skybox/right.jpg",
//            "../assets/skybox/left.jpg",
//            "../assets/skybox/top.jpg",
//            "../assets/skybox/bottom.jpg",
//            "../assets/skybox/front.jpg",
//            "../assets/skybox/back.jpg",
//    };

    unsigned int virtualRoomTextureId = loadSkyBoxTexture(virtualRoom1);
    unsigned int realRoomTextureId = loadSkyBoxTexture(realRoom1);
    unsigned int topTexture = loadSignalTexture("../assets/room_show/common/north-point-circle.png");
    unsigned int bottomTexture = loadSignalTexture("../assets/room_show/common/platfond.png");

    virtualRoomShader.use();
    virtualRoomShader.setUniformInt("skybox", 0);
    virtualRoomShader.setUniformInt("topBrand", 2);
    virtualRoomShader.setUniformInt("bottomDirection", 3);

    realRoomShader.use();
    realRoomShader.setUniformInt("skybox", 1);
    realRoomShader.setUniformInt("topBrand", 2);
    realRoomShader.setUniformInt("bottomDirection", 3);


//    camera.Front = glm::vec3(0.0f, 0.0f, 1.0f);
//    camera.Yaw = 90;
    while(!glfwWindowShouldClose(window)) {
        std::cout<<"draw"<<endl;

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glDepthMask(GL_FALSE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // view/projection transformations
        glm::mat4 projection ;

        if (vertical) {
            projection = glm::perspective(glm::radians(90.0f), ((float)window_width * 0.5f)/ (float)window_height, 0.1f, 100.0f);
        } else {
            projection = glm::perspective(glm::radians(90.0f), (float)window_width / ((float)window_height * 0.5f), 0.1f, 100.0f);
        }
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1);
        virtualRoomShader.use();
        virtualRoomShader.setUniformMat4("model", model);
        virtualRoomShader.setUniformMat4("projection", projection);
        virtualRoomShader.setUniformMat4("view", view);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, bottomTexture);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, topTexture);

        glBindVertexArray(skyBoxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, virtualRoomTextureId);
        if (vertical) {
            glViewport(window_width/2, 0, window_width/2, window_height);
        } else {
            glViewport(0, 0, window_width, window_height/2);
        }
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        realRoomShader.use();

        model = glm::rotate(model, glm::radians(129.f), glm::vec3(0.f, 1.f, 0.f));
        realRoomShader.setUniformMat4("projection", projection);
        realRoomShader.setUniformMat4("view", view);
        realRoomShader.setUniformMat4("model", model);


        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, realRoomTextureId);
        if (vertical) {
            glViewport(0, 0, window_width/2, window_height);
        } else {
            glViewport(0, window_height/2, window_width, window_height/2);
        }
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        std::cout<<"draw end"<<endl;

    }

    glDeleteVertexArrays(1, &skyBoxVAO);
    glDeleteBuffers(1, &VBO);
    realRoomShader.del();
    virtualRoomShader.del();
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
    //在绘制时动态修改视口
    std::cout<<"framebuffer_size_callback"<<endl;
    window_width = width;
    window_height = height;
    vertical = window_width * 1.5 > window_height;
//    glViewport(0, 0, width, height);
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
