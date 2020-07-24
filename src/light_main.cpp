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

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;
bool mouseLeftPressed = false;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec4 lightPos(0.0f, 0.0f, 6.0f, 0.0f);

const float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

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

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    Shader lightingShader("../shaders/2_1_cube.vs", "../shaders/2_1_cube.fs");
    Shader lightCubeShader("../shaders/2_1_light.vs", "../shaders/2_1_light.fs");

    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int diffuseMap = loadTexture("../assets/container2.png");
    unsigned int specularMap = loadTexture("../assets/container2_specular.png");

    // shader configuration
    // --------------------
    lightingShader.use();

    lightingShader.use();
    lightingShader.setUniformInt("material.diffuse", 0);
    lightingShader.setUniformInt("material.specular", 1);

    // positions all containers
    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // positions of the point lights
    glm::vec3 pointLightPositions[] = {
            glm::vec3( 0.7f,  0.2f,  2.0f),
            glm::vec3( 2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    while(!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightingShader.use();
//        lightingShader.setUniformVec3("objectColor", 1.0f, 0.5f, 0.31f);
//        lightingShader.setUniformVec3("lightColor",  1.0f, 1.0f, 1.0f);
        lightingShader.setUniformVec3("lightPos", glm::vec3(lightPos));
        lightingShader.setUniformVec3("viewPos", camera.Position);

//        lightingShader.setUniformVec3("material.ambient",  1.0f, 0.5f, 0.31f);
//        lightingShader.setUniformVec3("material.diffuse",  1.0f, 0.5f, 0.31f);
//        lightingShader.setUniformVec3("material.specular", 0.5f, 0.5f, 0.5f);
        lightingShader.setUniformFloat("material.shininess", 64.0f);

        // directional light
        lightingShader.setUniformVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingShader.setUniformVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setUniformVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        lightingShader.setUniformVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        lightingShader.setUniformVec3("pointLights[0].position", pointLightPositions[0]);
        lightingShader.setUniformVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setUniformVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setUniformVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setUniformFloat("pointLights[0].constant", 1.0f);
        lightingShader.setUniformFloat("pointLights[0].linear", 0.09);
        lightingShader.setUniformFloat("pointLights[0].quadratic", 0.032);
        // point light 2
        lightingShader.setUniformVec3("pointLights[1].position", pointLightPositions[1]);
        lightingShader.setUniformVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setUniformVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setUniformVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setUniformFloat("pointLights[1].constant", 1.0f);
        lightingShader.setUniformFloat("pointLights[1].linear", 0.09);
        lightingShader.setUniformFloat("pointLights[1].quadratic", 0.032);
        // point light 3
        lightingShader.setUniformVec3("pointLights[2].position", pointLightPositions[2]);
        lightingShader.setUniformVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setUniformVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setUniformVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setUniformFloat("pointLights[2].constant", 1.0f);
        lightingShader.setUniformFloat("pointLights[2].linear", 0.09);
        lightingShader.setUniformFloat("pointLights[2].quadratic", 0.032);
        // point light 4
        lightingShader.setUniformVec3("pointLights[3].position", pointLightPositions[3]);
        lightingShader.setUniformVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        lightingShader.setUniformVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setUniformVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setUniformFloat("pointLights[3].constant", 1.0f);
        lightingShader.setUniformFloat("pointLights[3].linear", 0.09);
        lightingShader.setUniformFloat("pointLights[3].quadratic", 0.032);
        // spotLight
        lightingShader.setUniformVec3("spotLight.position", camera.Position);
        lightingShader.setUniformVec3("spotLight.direction", camera.Front);
        lightingShader.setUniformVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingShader.setUniformVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        lightingShader.setUniformVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setUniformFloat("spotLight.constant", 1.0f);
        lightingShader.setUniformFloat("spotLight.linear", 0.09);
        lightingShader.setUniformFloat("spotLight.quadratic", 0.032);
        lightingShader.setUniformFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        lightingShader.setUniformFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setUniformMat4("projection", projection);
        lightingShader.setUniformMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setUniformMat4("model", model);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);
        // render the cube
        glBindVertexArray(cubeVAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lightingShader.setUniformMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

//        // also draw the lamp object
        lightCubeShader.use();
        lightCubeShader.setUniformMat4("projection", projection);
        lightCubeShader.setUniformMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(lightPos));
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setUniformMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
    lightCubeShader.del();
    lightingShader.del();
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
