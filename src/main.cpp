#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>

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
    const unsigned int program = glCreateProgram();
    const unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    const unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmetShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
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

    const GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "glew NOT init:" << err << std::endl;
        return -1;
    }
    const unsigned int major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    const unsigned int minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    std::cout << "oepngl version: " << major << "." << minor << std::endl;

    constexpr float postions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5,
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), postions, GL_STATIC_DRAW);

    // 这两个必不可少？
    unsigned int vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);

    const ShaderSource source = parseShader("../res/shaders/basic.shader");
    std::cout << "vertex shader:" << std::endl;
    std::cout << source.vertexShader << std::endl;
    std::cout << "fragment shader:" << std::endl;
    std::cout << source.fragmentShader << std::endl;
    const unsigned int shader = createShader(source.vertexShader, source.fragmentShader);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &buffer);
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
