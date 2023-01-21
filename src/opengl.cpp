#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shader.h"

using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

int main () {


/*

    Initialize GLFW

*/

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

/*

    Create GLFW Window

*/

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

/*

    GLAD: Load all OpenGL Function Pointers

*/
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // Build and compile shaders
    // uses custom include to make creating new shaders easier.
    Shader myShader("../shaders/default.vs", "../shaders/default.fs");

    // Setup vertex data and configure vertex attributes
    float triangleVertices1[] = {
        -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,    // 1st triangle - top left - red
        -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,    // 1st triangle - bottom left - blue
        -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,    // 1st triangle - bottom right - green
        -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,    // 2nd triangle - top left - green
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,     // 2nd triangle - top right - red
        0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f     // 2nd triangle - bottom right - green
    };

    // Initialize the vertex buffer object
    unsigned int VBO, VAO;
    // Generate one vertex array
    glGenVertexArrays(1, &VAO);
    // Generate one buffer
    glGenBuffers(1, &VBO);


    glBindVertexArray(VAO);

    // Bind the VBO buffer to the GL_ARRAY_BUFFER buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Add the triangle vertices to the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices1), triangleVertices1, GL_STATIC_DRAW);

    // Describe where to find the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float))); // color
    glEnableVertexAttribArray(1);


    // glUseProgram(shaderProgram);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 10.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwPollEvents();    
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;

}
