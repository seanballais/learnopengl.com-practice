#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char *vertexShaderSrc = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n";

const char *fragShaderSrc =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Make them cool window.
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window. :-(" << std::endl;
        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD before calling any OpenGL functions.
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD. :-(" << std::endl;

        return -1;
    }

    // Prepping OpenGL.
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set up the vertex data.
    float triangleVertices[][9] = {
        {
            -0.5f, -0.25f, 0.0f,
            -0.25f, 0.25f, 0.0f,
            0.0f, -0.25f, 0.0f
        },
        {
            0.0f, -0.25f, 0.0f,
            0.25f, 0.25f, 0.0f,
            0.5f, -0.25f, 0.0f
        }
    };

    // Set up the shaders modern OpenGL requires us to define.
    char infoLog[512];

    // Set up the vertex shader.
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    int vertexShaderCompileSuccess;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompileSuccess);
    if (!vertexShaderCompileSuccess) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::VERTEX_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
    }

    // Set up the fragment shader.
    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    int fragShaderCompileSuccess;
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fragShaderCompileSuccess);
    if (!fragShaderCompileSuccess) {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR::FRAGMENT_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
    }

    // Let's create the shader program that the shaders will be linked into.
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    int shaderProgLinkSuccess;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderProgLinkSuccess);
    if (!shaderProgLinkSuccess) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM_LINKING_FAILED: " << infoLog << std::endl;
    }

    // Configure the objects for rendering.
    unsigned int triangleVaos[] = { 0, 0 };
    unsigned int triangleVbos[] = { 0, 0 };
    unsigned int numTriangleVaos = sizeof(triangleVaos) / sizeof(*triangleVaos);
    unsigned int numTriangleVbos = sizeof(triangleVbos) / sizeof(*triangleVbos);
    for (int index = 0; index < numTriangleVaos; index++) {
        unsigned int* triangleVao = &triangleVaos[index];
        glGenVertexArrays(1, triangleVao);

        glBindVertexArray(*triangleVao);

        unsigned int* triangleVbo = &triangleVbos[index];
        glGenBuffers(1, triangleVbo);
        glBindBuffer(GL_ARRAY_BUFFER, *triangleVbo);
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(triangleVertices[index]),
            triangleVertices[index],
            GL_STATIC_DRAW
        );

        glVertexAttribPointer(
            0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0
        );
        glEnableVertexAttribArray(0);

        // Unbind everything to prepare for the next triangle.
        glBindVertexArray(0);
    }

    // Let's get OpenGL displaying!
    // This is called the render loop.
    while (!glfwWindowShouldClose(window)) {
        // We must always call glClear(). Otherwise, we'd be displaying
        // whatever data was in the frame buffer our OpenGL context is using.
        // For funsies, let's clear the frame buffer and paint a pink
        // background.
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        // Rendering methods here!
        glUseProgram(shaderProgram);
        for (int vao : triangleVaos) {
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        // We should try removing this buffer swapping sometime to see what happens during single buffer drawing.
        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
