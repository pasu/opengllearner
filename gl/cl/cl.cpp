//

#include "pch.h"
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
GLFWwindow* window;

#include "shader.h"
#include "texture.h"

#include "opencl.h"
#include "shared.h"

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCRWIDTH, SCRHEIGHT, "cl", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Create Window Fail";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Load glad Fail";
        return -1;
    }

    double lastTime = glfwGetTime();

    GLuint _Texture = loadDDS("./data/uvtemplate.DDS");

    GLuint quad_ID = loadshaders("./shader/quad.vertexshader", "./shader/quad.fragmentshader");
    GLuint _qtextureID = glGetUniformLocation(quad_ID, "texture_dds");
    // The fullscreen quad's FBO
    static const GLfloat g_quad_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint quad_vertexbuffer;
    glGenBuffers(1, &quad_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

    /////////////////////////////////////////////////////////////////////
    CL_Texture* clOutput = new CL_Texture(SCRWIDTH, SCRHEIGHT, CL_Texture::FLOAT);
    Kernel* testFunction = new Kernel("programs/program.cl", "TestFunction");
    Kernel* boundsCheck = new Kernel("programs/program.cl", "BoundsTest");
    // link cl output texture as an OpenCL buffer
    Buffer* outputBuffer = new Buffer(clOutput->GetID(), Buffer::TARGET);
    testFunction->SetArgument(0, outputBuffer);
    Buffer* testData = new Buffer(10000);
    testData->CopyToDevice();
    boundsCheck->SetArgument(0, testData);
    ///////////////////////////////////////////////////////////////////////
       
    while (!glfwWindowShouldClose(window))
    {
        testFunction->Run(outputBuffer);
        boundsCheck->Run(9999);
        testData->CopyFromDevice();
        if (testData->GetHostPtr()[9999] == 99999)
        {
            int w = 0;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(quad_ID);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, clOutput->GetID());
        glUniform1i(_qtextureID, 0);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(0);

        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteTextures(1, &_Texture);

    glDeleteBuffers(1, &quad_vertexbuffer);
    glDeleteProgram(quad_ID);

    glfwTerminate();

    return 0;
}
