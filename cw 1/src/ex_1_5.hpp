#pragma once
#include "glew.h"
#include <GLFW/glfw3.h>
#include "glm.hpp"

#include "Shader_Loader.h"
#include "Render_Utils.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

GLuint program; // Shader ID

GLuint quadVAO1, quadVAO2;

Core::Shader_Loader shaderLoader;


void renderScene(GLFWwindow* window)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Zmienna "time" przechowuje czas ktory uplynal od uruchomienia aplikacji
	float time = glfwGetTime();

	glUseProgram(program);

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// ! Macierz translation jest definiowana wierszowo dla poprawy czytelnosci. OpenGL i GLM domyslnie stosuje macierze kolumnowe, dlatego musimy ja transponowac !
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	glm::mat4 translation =
	{ 1,0,0,0,
	  0,1,0, sin(time) * 0.5f,
	  0,0,1,0,
	  0,0,0,1 };
	glm::mat4 translater = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.5f, 0.0f));
	glm::mat4 rotation =
	{
		cos(time), -sin(time), 0, 0,
		sin(time), cos(time), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	glm::mat4 reverseTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, -0.5f, 0.0f));

	// Итоговая матрица преобразования
	glm::mat4 transformation = reverseTranslation * rotation * translater;



	// ZADANIE: Narysuj dwa czworokaty, jeden ruszajacy sie, drugi obracajacy sie 
	// Do rysowania ruszajacego sie czworokatu mozesz uzyc kodu z poprzedniego zadania, zmodyfikuj tylko macierz translacji, zeby byly obok siebie, nie jeden na drugim
	// Uzyj zmiennej "time" do zdefiniowania takiej macierzy rotacji, aby czworokat obracal sie wokol srodka (znajdz odpowiednia macierz 4x4 w internecie)
	// Kat obrotu podajemy w radianach

    rotation = glm::transpose(rotation);
	glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&transformation);

	// Uzyj kodu z poprzednich cwiczen do narysowania czworokata
	Core::drawVAOIndexed(quadVAO1, 16);	
	translation = glm::transpose(translation);
	glUniformMatrix4fv(glGetUniformLocation(program, "transformation"), 1, GL_FALSE, (float*)&translation);
	Core::drawVAOIndexed(quadVAO2, 16);

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
0.9f, -0.9f, 0, 1,
0.1f, -0.9f, 0, 1,
0.1f, -0.1f, 0, 1,
0.9f, -0.1f, 0, 1
	};
	unsigned int unsignedArray1[6] = {
	   0,1,2,2,3,0
	};
	quadVAO1 = Core::initVAOIndexed(array1, unsignedArray1, 4, 4, 6);
	float array2[16] = {
-0.9f, 0.9f, 0, 1,
-0.1f, 0.9f, 0, 1,
-0.1f, 0.1f, 0, 1,
-0.9f, 0.1f, 0, 1
	};
	unsigned int unsignedArray2[6] = {
	   0,1,2,2,3,0
	};
	quadVAO2 = Core::initVAOIndexed(array2, unsignedArray2, 4, 4, 6);
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