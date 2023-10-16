#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "Shader_Loader.h"
#include "Render_Utils.h"

#include <gtc/matrix_transform.hpp>
GLuint program; // Shader ID

GLuint quadVAO1;

Core::Shader_Loader shaderLoader;


void renderScene(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Zmienna "time" przechowuje czas ktory uplynal od uruchomienia aplikacji
	float time = glfwGetTime();

    glUseProgram(program);
    

    glm::mat4 translater = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
    glm::mat4 rotation =
    {
        cos(time), -sin(time), 0, 0,
        sin(time), cos(time), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    glm::mat4 reverseTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f));
    glm::mat4 translationY = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, sin(time) * 0.5f, 0.0f));

    // Итоговая матрица преобразования
    glm::mat4 transformation = reverseTranslation*translationY * rotation * translater;


    // ZADANIE: Wyswietl czworokat, ktory jednoczesnie przesuwa sie i obraca.
    // 
    // Uzyj kodu do translacji i rotacji czworokatu z poprzednich zadan
    // 
    // Stworz taka macierz transformacji, ktora powoduje ze czworokat przesuwa sie w gore i w dol ekranu, jednoczesnie obracajac sie.
    // Wyslij stworzona macierz do GPU za pomoca funkcji glUniformMatrix4fv zamiast macierzy "translation" i "rotation" z poprzednich zadan
    
    

    glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&transformation);
    Core::drawVAOIndexed(quadVAO1, 16);


    // Uzyj kodu z poprzednich cwiczen do narysowania czworokata

    glUseProgram(0);
 
    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void init(GLFWwindow* window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    program = shaderLoader.CreateProgram("shaders/shader_1_2.vert", "shaders/shader_1_2.frag");

    //Przekopiuj kod do ladowania z poprzedniego zadania
    float array1[16] = {
-0.7f, 0.2f, 0, 1,
-0.3f, 0.2f, 0, 1,
-0.3f, -0.2f, 0, 1,
-0.7f, -0.2f, 0, 1
    };
    unsigned int unsignedArray1[6] = {
       0,1,2,2,3,0
    };
    quadVAO1 = Core::initVAOIndexed(array1, unsignedArray1, 4, 4, 6);
}

void shutdown(GLFWwindow* window)
{
    shaderLoader.DeleteProgram(program);
}


//obsluga wejscia
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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