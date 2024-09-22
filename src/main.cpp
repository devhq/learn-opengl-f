#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "config.h"
#include "shader.hpp"
#include "version.h"

const unsigned int WINDOW_WIDTH  = CONFIG_WINDOW_WIDTH;
const unsigned int WINDOW_HEIGHT = CONFIG_WINDOW_HEIGHT;
const std::string ROOT_PATH_SHADER_FILES_DIRECTORY(CONFIG_ROOT_PATH_SHADER_FILES_DIRECTORY);
const std::string FILE_NAME_VERT_SHADER(CONFIG_FILE_NAME_VERT_SHADER);
const std::string FILE_NAME_FRAG_SHADER(CONFIG_FILE_NAME_FRAG_SHADER);

void callbackFramebufferSize(GLFWwindow* window, int width, int height);
void callbackKeyboardInput(GLFWwindow* window, int key, int scan_code, int action, int mods);

int main()
{
	std::cout << PROJECT_NAME << " Version " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, PROJECT_NAME, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Error: GLFW window creation failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, callbackFramebufferSize);
	glfwSetKeyCallback(window, callbackKeyboardInput);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error: Glad initilization failed" << std::endl;
		return -1;
	}

	Shader shader((ROOT_PATH_SHADER_FILES_DIRECTORY + FILE_NAME_VERT_SHADER).c_str(), (ROOT_PATH_SHADER_FILES_DIRECTORY + FILE_NAME_FRAG_SHADER).c_str());

	float vertices_f[] = {
		//positions				//colors
		-0.25f,  0.75f, 0.0f,	1.0f, 0.0f, 0.0f,
		 0.35f,  0.75f, 0.0f,	1.0f, 0.0f, 0.0f,
		 0.35f,  0.50f, 0.0f,	1.0f, 0.0f, 0.0f,
		 0.00f,  0.50f, 0.0f,	0.0f, 1.0f, 0.0f, 
		-0.25f,  0.50f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.25f,  0.25f, 0.0f,	0.0f, 1.0f, 0.0f,
		 0.00f,  0.25f, 0.0f,	0.0f, 0.0f, 1.0f,
		 0.25f,  0.25f, 0.0f,	0.0f, 1.0f, 0.0f,
		 0.25f,  0.00f, 0.0f,	0.0f, 1.0f, 0.0f,
		 0.00f,  0.00f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.25f,  0.00f, 0.0f,	0.0f, 1.0f, 0.0f,
		-0.25f, -0.75f, 0.0f,	0.0f, 0.0f, 1.0f,
		 0.00f, -0.75f, 0.0f,	0.0f, 0.0f, 1.0f
	};
	unsigned int indices_f[] = {
		0 , 1 , 2 ,
		0 , 2 , 4 ,
		4 , 3 , 6 ,
		4 , 6 , 5 ,
		5 , 7 , 8 ,
		5 , 8 , 10,
		10, 9 , 12,
		10, 12, 11
	};

	unsigned int vao_f;
	glGenVertexArrays(1, &vao_f);
	glBindVertexArray(vao_f);

	unsigned int vbo_f;
	glGenBuffers(1, &vbo_f);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_f);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_f), vertices_f, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int ebo_f;
	glGenBuffers(1, &ebo_f);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_f);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_f), indices_f, GL_STATIC_DRAW);

	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClearColor(0.8f, 1.0f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.useProgram();
		glBindVertexArray(vao_f);
		glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao_f);
	glDeleteBuffers(1, &vao_f);
	glDeleteBuffers(1, &vao_f);

	glfwTerminate();
	return 0;
}

void callbackFramebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void callbackKeyboardInput(GLFWwindow* window, int key, int scan_code, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
		
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		int polygon_mode[2];
		glGetIntegerv(GL_POLYGON_MODE, polygon_mode);
		glPolygonMode(GL_FRONT_AND_BACK, polygon_mode[0] == GL_FILL ? GL_LINE : GL_FILL);
	}
}