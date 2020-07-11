//
// Created by fengbo on 2020/7/11.
//

#ifndef OPENGLTUTARIAL_SHADER_H
#define OPENGLTUTARIAL_SHADER_H

#include <glad/glad.h>;

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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
};


#endif //OPENGLTUTARIAL_SHADER_H
