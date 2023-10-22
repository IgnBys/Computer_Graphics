#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include "ext.hpp"
#include <vector>

#include "Shader_Loader.h"
#include "Render_Utils.h"

GLuint program; // Shader ID

GLuint quadVAO;

Core::Shader_Loader shaderLoader;
glm::vec3 quadRotation(0.0f, 0.0f, 0.0f);
glm::vec3 quadPos(0.0f, 0.0f, 0.0f);
std::vector<glm::vec3> quadsPositions;

void renderScene(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	float time = glfwGetTime();

    glUseProgram(program);
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), quadPos);
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(quadRotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); 

    //glm::mat4 translation = glm::translate(glm::mat4(1.0f), quadPos);
    //glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(quadRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 transformation = translation * rotation;




    glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&transformation);
    Core::drawVAOIndexed(quadVAO, 6);

    glUseProgram(0);

    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    /*int width, height;
    glfwGetWindowSize(window, &width, &height);

    float x_normalized = (2.0f * xpos / width) - 1.0f;
    float y_normalized = -((2.0f * ypos / height) - 1.0f);

    quadPos.x = x_normalized;
    quadPos.y = y_normalized;*/
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    printf("%f,%f\n", xpos, ypos);
}


void init(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    program = shaderLoader.CreateProgram("shaders/shader_1_2.vert", "shaders/shader_1_2.frag");

    float points[] = {
        -0.1,-0.1,0.0,1.0,
         0.1,-0.1,0.0,1.0,
         0.1, 0.1,0.0,1.0,
        -0.1, 0.1,0.0,1.0,
    };
    unsigned int indices[] = {
        0,1,3,
        1,2,3,
    };
    quadVAO = Core::initVAOIndexed(points, indices, 4, 4, 6);

    //Przekopiuj kod do ladowania z poprzedniego zadania
}

void shutdown(GLFWwindow* window)
{
    shaderLoader.DeleteProgram(program);
}

//obsluga wejscia
void processInput(GLFWwindow* window)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
     if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
         quadPos += glm::vec3(0.0,0.001,0.0);
    }
     if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
         quadPos += glm::vec3(0.0, -0.001, 0.0);
    }                        
     if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
         quadPos += glm::vec3(0.001, 0.0, 0.0);
    }
     if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
         quadPos += glm::vec3(-0.001, 0.0, 0.0);
    }
     if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
         quadRotation.z += 0.07f;
     }
     if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
         quadRotation.z -= 0.07f;
     }
}

// funkcja jest glowna petla
void renderLoop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        renderScene(window);
        glfwPollEvents();
    }
}
//}