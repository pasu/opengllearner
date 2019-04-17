#include <GLFW/glfw3.h>
extern GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

glm::mat4 projectMatrix;
glm::mat4 viewMatrix;

// Initial position : on +Z
glm::vec3 position = glm::vec3(0, 0, 5);
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

void computeMatricesFromInputs()
{
    static double lastTime = glfwGetTime();

    double currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;

    double mouse_pos_x, mouse_pos_y;
    glfwGetCursorPos(window, &mouse_pos_x, &mouse_pos_y);

    glfwSetCursorPos(window, 1024 / 2, 768 / 2);
    horizontalAngle += mouseSpeed * float(1024 / 2 - mouse_pos_x);
    verticalAngle += mouseSpeed * float(768 / 2 - mouse_pos_y);

    glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle)*cos(horizontalAngle));

    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f)
    );

    glm::vec3 up = glm::cross(right, direction);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        position += direction * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        position -= direction * deltaTime * speed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }

    float FoV = initialFoV;

    projectMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
    viewMatrix = glm::lookAt(position, position + direction, up);

    lastTime = currentTime;
}

glm::mat4 getViewMatrix()
{
    return viewMatrix;
}

glm::mat4 getProjectionMatrix()
{
    return projectMatrix;
}