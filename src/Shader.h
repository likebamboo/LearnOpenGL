//
// Created by 李文涛 on 2024/1/27.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>

struct ShaderSource {
    std::string vertexShader;
    std::string fragmentShader;
};

class Shader {
private:
    unsigned int m_RendererId;
    std::string filePath;
    std::unordered_map<std::string, int> uniformLocationMap;

    ShaderSource parseShader(const std::string &filepath);

    unsigned int compileShader(unsigned type, const std::string &source);

    unsigned int createShader(const std::string &vertexShader, const std::string &fragmetShader);

    int GetUniformLocation(const std::string &name);

public:
    Shader(const std::string &filePath);

    ~Shader();

    void Bind();

    void UnBind();

    void SetUniform1f(const std::string& name, float value);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
};


#endif //SHADER_H
