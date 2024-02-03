#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertextArrayLayout.h"

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
        100.0f, 100.0f, 0.f, 0.f, // Bottom Left
        200.0f, 100.0f, 1.f, 0.f, // Bottom Right
        200.0f, 200.0f, 1.0f, 1.f, // Top Right
        100.0f, 200.0f, 0.0f, 1.0f, // Top Left
    };
    constexpr unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    glCall(glEnable(GL_BLEND));

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    VertextArrayLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddLayout(vb, layout);

    IndexBuffer ib(indices, 6);

    Shader shader("../res/shaders/basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.8f, 0.0f, 0.8f, 1.f);

    glm::mat4 proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.f, 0.f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 200.f, 0.f));

    shader.SetUniformMat4f("u_MVP", proj * view * model);

    Texture texture("../res/texture/ChernoLogo.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    va.UnBind();
    vb.UnBind();
    ib.UnBind();
    shader.UnBind();

    Renderer renderer;

    float r = 0.0f;
    float increment = 0.01f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();

        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.0f, 0.8f, 1.f);
        renderer.Draw(va, ib, shader);

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

    glfwTerminate();
    return 0;
}
