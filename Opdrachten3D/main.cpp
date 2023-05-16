#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

void init();
void update();
void draw();

int width = 1400, height = 800;

glm::vec3 ballPosition(0, 0, 0);
glm::vec3 ballDirection(-3, 0, -1.5f);
glm::vec3 player1Position(-7, 0, 0);
glm::vec3 player2Position(7, 0, 0);
float ballSize = 0.5f;

double lastFrameTime = 0;
float playerSpeed = 5.0f;

int main(void)
{
	if (!glfwInit())
		throw "Could not initialize glwf";
	window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);

	tigl::init();

	init();

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


	return 0;
}


void init()
{
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);
	});

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
	{
		::width = width;
		::height = height;
	});

	glEnable(GL_DEPTH_TEST);
}


void update()
{
	double frameTime = glfwGetTime();
	float deltaTime = lastFrameTime - frameTime;
	lastFrameTime = frameTime;

	if (glfwGetKey(window, GLFW_KEY_Q))
		player1Position.z -= playerSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_A))
		player1Position.z += playerSpeed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_O))
		player2Position.z -= playerSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_L))
		player2Position.z += playerSpeed * deltaTime;

	/*
	glm::vec3 oldBallPosition = ballPosition;
	ballPosition += ballDirection * deltaTime;

	if (ballPosition.x < -8 || ballPosition.x > 8)
	{
		ballDirection.x = -ballDirection.x;
		ballPosition.x = oldBallPosition.x;
	}
	if (ballPosition.z < -8 || ballPosition.z > 8)
	{
		ballDirection.z = -ballDirection.z;
		ballPosition.z = oldBallPosition.z;
	}*/
}

void drawCube(const glm::vec3& size)
{
	tigl::begin(GL_QUADS);

	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, -size.y / 2, -size.z / 2), glm::vec4(1.0f, 1.0f, 0.9f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, -size.y / 2, -size.z / 2), glm::vec4(1.0f, 1.0f, 0.9f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, size.y / 2, -size.z / 2), glm::vec4(1.0f, 1.0f, 0.9f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, size.y / 2, -size.z / 2), glm::vec4(1.0f, 1.0f, 0.9f, 1.0f)));

	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, -size.y / 2, size.z / 2), glm::vec4(1.0f, 1.0f, 0.8f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, -size.y / 2, size.z / 2), glm::vec4(1.0f, 1.0f, 0.8f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, size.y / 2, size.z / 2), glm::vec4(1.0f, 1.0f, 0.8f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, size.y / 2, size.z / 2), glm::vec4(1.0f, 1.0f, 0.8f, 1.0f)));

	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, -size.y / 2, -size.z / 2), glm::vec4(1.0f, 0.5f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, -size.y / 2, -size.z / 2), glm::vec4(1.0f, 0.5f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, -size.y / 2, size.z / 2), glm::vec4(1.0f, 0.5f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, -size.y / 2, size.z / 2), glm::vec4(1.0f, 0.5f, 1.0f, 1.0f)));

	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, size.y / 2, -size.z / 2), glm::vec4(1.0f, 0.8f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, size.y / 2, -size.z / 2), glm::vec4(1.0f, 0.8f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, size.y / 2, size.z / 2), glm::vec4(1.0f, 0.8f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, size.y / 2, size.z / 2), glm::vec4(1.0f, 0.8f, 1.0f, 1.0f)));

	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, -size.y / 2, -size.z / 2), glm::vec4(0.5f, 1.0f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, size.y / 2, -size.z / 2), glm::vec4(0.5f, 1.0f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, size.y / 2, size.z / 2), glm::vec4(0.5f, 1.0f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(-size.x / 2, -size.y / 2, size.z / 2), glm::vec4(0.5f, 1.0f, 1.0f, 1.0f)));

	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, -size.y / 2, -size.z / 2), glm::vec4(0.8f, 1.0f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, size.y / 2, -size.z / 2), glm::vec4(0.8f, 1.0f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, size.y / 2, size.z / 2), glm::vec4(0.8f, 1.0f, 1.0f, 1.0f)));
	tigl::addVertex(Vertex::PC(glm::vec3(size.x / 2, -size.y / 2, size.z / 2), glm::vec4(0.8f, 1.0f, 1.0f, 1.0f)));

	tigl::end();
}

void draw()
{
	glViewport(0, 0, width, height);
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	tigl::shader->setProjectionMatrix(glm::perspective(glm::radians(80.0f), (float)width / height, 0.1f, 100.0f));
	tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(ballPosition.x, 7, -12), ballPosition, glm::vec3(0, 1, 0)));
	tigl::shader->enableColor(true);


	//zijkanten
	tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(8.5f, 0, 0)));
	drawCube(glm::vec3(1, 1, 16));

	tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-8.5, 0, 0)));
	drawCube(glm::vec3(1, 1, 16));

	//voor/achter
	tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 8.5f)));
	drawCube(glm::vec3(16, 1, 1));

	tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -8.5)));
	drawCube(glm::vec3(16, 1, 1));

	
	tigl::shader->enableColorMult(true);
	tigl::shader->setColorMult(glm::vec4(0, 1, 0, 1));
	tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.5f, 0)));
	drawCube(glm::vec3(16, 1, 16));
	/*
	tigl::shader->setColorMult(glm::vec4(1, 0, 0, 1));
	tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), ballPosition));
	drawCube(glm::vec3(ballSize));

	tigl::shader->setColorMult(glm::vec4(1, 0, 1, 1));
	tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), player1Position));
	drawCube(glm::vec3(1, 1, 3));

	tigl::shader->setColorMult(glm::vec4(0, 1, 1, 1));
	tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), player2Position));
	drawCube(glm::vec3(1, 1, 3));

	srand(0);

	for (int i = 0; i < 10; i++)
	{
		tigl::shader->enableColorMult(false);
		tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 9 + i)));
		drawCube(glm::vec3(16, i + 1, 1));

		tigl::shader->enableColorMult(true);
		for (float f = -8; f < 8; f += 0.75f)
		{
			float offset = (1 + sin(f / 8 + lastFrameTime * 10)) * 0.25;
			offset += 0.1f * (rand() / (float)RAND_MAX);
			tigl::shader->setColorMult(glm::vec4(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1));
			tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(f, i / 2.0f + 1 + offset, 9 + i)));
			drawCube(glm::vec3(0.25f, 1, 0.25f));

			tigl::shader->setColorMult(glm::vec4(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1));

			tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(f - 0.15f, i / 2.0f + 1 + offset + 0.5f, 9 + i)));
			drawCube(glm::vec3(0.1f, 0.5f, 0.1f));
			tigl::shader->setModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(f + 0.15f, i / 2.0f + 1 + offset + 0.5f, 9 + i)));
			drawCube(glm::vec3(0.1f, 0.5f, 0.1f));
		}

	}
	*/
	tigl::shader->enableColorMult(false);
}