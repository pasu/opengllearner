#include "pch.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "shader.h"
#include "texture.h"
#include "control.h"
#include "mesh.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "gl", NULL, NULL);

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

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);

    GLuint prg_ID = loadshaders("./shader/SimpleVertexShader.vertexshader", "./shader/SimpleFragmentShader.fragmentshader");

    GLuint matrixID = glGetUniformLocation(prg_ID, "MVP");

    GLuint _texture = loadDDS("./data/uvmap.DDS");
    GLuint textureID = glGetUniformLocation(prg_ID, "texture_dds");

    /*
    glm::mat4 projectMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 viewMatrix = glm::lookAt(
        glm::vec3(4.0f,3.0f,3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f,1.0f, 0.0f));
    */
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    vector<unsigned short> indeices;
    vector<glm::vec3> vertices;
    vector<glm::vec2> uv;
    vector<glm::vec3> normals;

    loadObj("./data/suzanne.obj", indeices, vertices, uv, normals);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_data_buffer), g_vertex_data_buffer, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_data_buffer), g_color_data_buffer, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*normals.size(), &normals[0], GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*uv.size(), &uv[0], GL_STATIC_DRAW);

    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*indeices.size(), &indeices[0], GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(prg_ID);

        computeMatricesFromInputs();
        glm::mat4 mvp = projectMatrix * viewMatrix * modelMatrix;
        glUniformMatrix4fv(matrixID,1,GL_FALSE,&mvp[0][0]);
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

        //glDrawArrays(GL_TRIANGLES, 0, 12*3);
        glDrawElements(GL_TRIANGLES,indeices.size(),GL_UNSIGNED_SHORT,0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteBuffers(1, &uvbuffer);

    glDeleteBuffers(1, &elementbuffer);

    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(prg_ID);

    glfwTerminate();

    return 0;
}