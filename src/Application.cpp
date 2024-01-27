#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexBuffer.h"

struct ShaderSource {
    std::string vertexShader;
    std::string fragmentShader;
};

static ShaderSource parseShader(const std::string &filepath) {
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

static unsigned int compileShader(const unsigned int type, const std::string &source) {
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

static unsigned int createShader(const std::string &vertexShader, const std::string &fragmetShader) {
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

int main() {
    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    std::cout << "I'm apple machine" << std::endl;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) {
        std::cout << "window NOT created" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    const GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "glew NOT init:" << err << std::endl;
        return -1;
    }
    const unsigned int major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    const unsigned int minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    std::cout << "oepngl version: " << major << "." << minor << std::endl;

    constexpr float positions[] = {
        -0.5f, -0.5f, // Bottom Left
        0.5f, -0.5f, // Bottom Right
        0.5f, 0.5f, // Top Right
        -0.5f, 0.5f, // Top Left
    };
    constexpr unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    unsigned int vao;
    glCall(glGenVertexArrays(1, &vao));
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glCall(glBindVertexArray(vao));

    VertexBuffer vb(positions, 4 * 2 * sizeof(float));

    glCall(glEnableVertexAttribArray(0));
    glCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr));

    IndexBuffer ib(indices, 6);

    const ShaderSource source = parseShader("../res/shaders/basic.shader");
    std::cout << "vertex shader:" << std::endl;
    std::cout << source.vertexShader << std::endl;
    std::cout << "fragment shader:" << std::endl;
    std::cout << source.fragmentShader << std::endl;
    const unsigned int shader = createShader(source.vertexShader, source.fragmentShader);
    glCall(glUseProgram(shader));

    int location;
    glCall(location = glGetUniformLocation(shader, "u_Color"));
    glAsset(location != -1);
    glCall(glUniform4f(location, 0.8f, 0.0f, 0.8f, 1.f));

    glCall(glBindVertexArray(0));
    glCall(glUseProgram(0));
    glCall(glBindBuffer(GL_ARRAY_BUFFER , 0));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0));

    float r = 0.0f;
    float increment = 0.01f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glCall(glClear(GL_COLOR_BUFFER_BIT));

        glCall(glUseProgram(shader));
        glCall(glUniform4f(location, r, 0.0f, 0.8f, 1.f));

        glCall(glBindVertexArray(vao));
        ib.Bind();
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f) {
            increment = -0.01f;
        } else if (r < 0.0f) {
            increment = 0.01f;
        }
        r += increment;

        /* Swap front and back buffers */
        glCall(glfwSwapBuffers(window));

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
