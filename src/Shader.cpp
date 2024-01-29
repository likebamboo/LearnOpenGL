//
// Created by 李文涛 on 2024/1/27.
//

#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Renderer.h"

Shader::Shader(const std::string &filePath): m_RendererId(0), filePath(filePath) {
    const ShaderSource source = parseShader("../res/shaders/basic.shader");
    std::cout << "vertex shader:" << std::endl;
    std::cout << source.vertexShader << std::endl;
    std::cout << "fragment shader:" << std::endl;
    std::cout << source.fragmentShader << std::endl;
    m_RendererId = createShader(source.vertexShader, source.fragmentShader);
}

Shader::~Shader() {
    glCall(glDeleteProgram(m_RendererId));
}

void Shader::Bind() const {
    glCall(glUseProgram(m_RendererId));
}

void Shader::UnBind() const {
    glCall(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string &name) {
    int location;
    if (uniformLocationMap.find(name) != uniformLocationMap.end()) {
        return uniformLocationMap[name];
    }
    glCall(location = glGetUniformLocation(m_RendererId, name.c_str()));
    uniformLocationMap[name] = location;
    return location;
}

void Shader::SetUniform1i(const std::string &name, int value) {
    glCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string &name, float value) {
    glCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    glCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

ShaderSource Shader::parseShader(const std::string &filepath) {
    std::ifstream stream(filepath);

    enum ShaderType {
        None = -1,
        Vertex = 0,
        Fragment = 1
    };

    ShaderType type = None;
    std::string line;
    std::stringstream ss[2];
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = Vertex;
            } else if (line.find("fragment") != std::string::npos) {
                type = Fragment;
            }
        } else {
            if (type != None) {
                ss[type] << line << "\n";
            }
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::compileShader(const unsigned int type, const std::string &source) {
    const unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        const auto message = static_cast<char *>((alloca(length * sizeof(char))));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" <<
                std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmetShader) {
    unsigned int program;
    glCall(program = glCreateProgram());
    const unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    const unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmetShader);

    glCall(glAttachShader(program, vs));
    glCall(glAttachShader(program, fs));

    glCall(glLinkProgram(program));
    glCall(glValidateProgram(program));

    glCall(glDeleteShader(vs));
    glCall(glDeleteShader(fs));
    return program;
}
