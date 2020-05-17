//
// Created by Mao on 5/7/18.
//

#ifndef GL3BOOK_SHADER_H
#define GL3BOOK_SHADER_H

#include <string>
#include <GLES3/gl3.h>
#include <iostream>


class Shader {
public:
    unsigned int program;

    Shader(const char *vertexShader, const char *fragShader) {
        GLuint vertex, fragment;
        int success;
        char infoLog[512];

        vertex = buildShader(vertexShader, GL_VERTEX_SHADER);
        fragment = buildShader(fragShader, GL_FRAGMENT_SHADER);

        this->program = glCreateProgram();
        glAttachShader(this->program, vertex);
        glAttachShader(this->program, fragment);
        glLinkProgram(this->program);
        glGetProgramiv(this->program, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(this->program, 512, NULL, infoLog);
            std::cout << "mao... program compilation failed. \n" << infoLog << std::endl;
        }

        //delete
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Use() {
        glUseProgram(this->program);
    }

    void setInt(std::string &name, int val) {
        glUniform1i(glGetUniformLocation(this->program, name.c_str()), val);
    }

    void setFloat(std::string &name, float val) {
        glUniform1f(glGetUniformLocation(this->program, name.c_str()), val);
    }

private:

    GLuint buildShader(const char *shaderSource, GLenum type) {
        int suceess;
        char infoLog[512];
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &suceess);
        if (!suceess) {
            glDeleteShader(shader);
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "mao...  shader compilation failed. \n" << infoLog << std::endl;
        }
        return shader;
    }

    void checkCompileError(unsigned int shader, std::string type) {

    }
};

#endif //GL3BOOK_SHADER_H
