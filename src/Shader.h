//
// Created by fengbo on 2020/7/11.
//

#ifndef OPENGLTUTARIAL_SHADER_H
#define OPENGLTUTARIAL_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    unsigned int id;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    void use();
    void del();
    // uniform工具函数
    void setUniformBool(const std::string &name, bool value) const;
    void setUniformInt(const std::string &name, int value) const;
    void setUniformFloat(const std::string &name, float value) const;
    void setUniformMat4(const std::string &name, glm::mat4 value) const;
    void setUniformVec3(const std::string &name, float x, float y, float z) const;
    void setUniformVec3(const std::string &name, glm::vec3 value) const;
    void setUniformVec4(const std::string &name, glm::vec4 value) const;
};


#endif //OPENGLTUTARIAL_SHADER_H
