#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include "ObjModel.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Camera.h"
#include "WhiteBall.h"
#include "YellowBall.h"
#include "RedBall.h"
#include "Ball.h"
#include "Ceu.h"

/* TODO:
*	Bal toevoegen (ball.cpp, white-, red-, yellowball.cpp)						DONE
*	Bal logica (locatie, richting, snelheid (afnemend), botsing, etc)
*	Camera laten bewegen om juiste bal											DONE
*	Afmetigen tafel
*	Collision met tafel
*	Stok toevoegen (ceu.cpp) (aanmaken in blender)
*	Stok logica (afschieten, richting laten bepalen door gebruiker, etc)
*	Belichting
*	mist/fog																	DONE
*	Automatisch bewegend object (Keu)
*	Speler object laten bedienen (zie `Stok logica`)
*/

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

ObjModel* biljartTable[3];
Camera* camera;
Ceu* ceu;
float rotation = 0;
WhiteBall* whiteBall;
RedBall* redBall;
YellowBall* yellowBall;
bool activePlayer = true;	//false on whiteball, true on yellowball
double lastFrameTime = 0;

void init();
void update();
void draw();
void enableFog(bool flag);

int main(void)
{
	if (!glfwInit())
		throw "Could not initialize glwf";
	window = glfwCreateWindow(1400, 800, "Three cushion billiard", NULL, NULL);
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
	int value[10];
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, value);
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window, true);
		});
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
		{
			if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !activePlayer)
			{
				std::cout << "whiteball pressed" << std::endl;
				if (whiteBall->getSpeed() < 0.05f)
				{
					std::cout << "whiteball adding movement" << std::endl;
					whiteBall->move(glm::vec2(0, 1.f), 3.f);
				}
			}
			if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && activePlayer)
			{
				std::cout << "yellowball pressed" << std::endl;
				if (yellowBall->getSpeed() < 0.05f)
				{
					std::cout << "yellowball adding movement" << std::endl;
					yellowBall->move(glm::vec2(0, 1.f), 3.f);
				}
			}
		});
	// Load all moddels
	biljartTable[0] = new ObjModel("models/biljard/Biljart_table.obj");
	biljartTable[1] = new ObjModel("models/biljard/Biljart_edge.obj");
	biljartTable[2] = new ObjModel("models/biljard/Biljart_cloth.obj");
	whiteBall = new WhiteBall("models/ball/WhiteBall.obj");
	redBall = new RedBall("models/ball/RedBall.obj");
	yellowBall = new YellowBall("models/ball/YellowBall.obj");
	camera = new Camera(window, whiteBall, yellowBall);
	ceu = new Ceu(*camera, "models/ceu/Ceu.obj");
}

void update()
{
	double frameTime = glfwGetTime();
	float deltaTime = lastFrameTime - frameTime;
	lastFrameTime = frameTime;

	if (!activePlayer && (whiteBall->getSpeed() <= 0.05f && whiteBall->getSpeed() > 0)) {
		activePlayer = !activePlayer;
		std::cout<< "going to yellow" << std::endl;
	}
	if (activePlayer && (yellowBall->getSpeed() <= 0.05f && yellowBall->getSpeed() > 0)) {
		activePlayer = !activePlayer;
		std::cout << "going to white" << std::endl;
	}

	camera->update(window, activePlayer);
	whiteBall->update(deltaTime);
	yellowBall->update(deltaTime);
	redBall->update(deltaTime);
	ceu->update(deltaTime);
}

void draw()
{
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 100.0f);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(camera->getMatrix());
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(true);

	glEnable(GL_DEPTH_TEST);
	enableFog(true);


	for (auto& model : biljartTable)
		model->draw();
	whiteBall->draw();
	yellowBall->draw();
	redBall->draw();
	//ceu->draw();
}

void enableFog(bool flag) {
	if (flag) {
		tigl::shader->enableFog(true);
		tigl::shader->setFogLinear(1, 4);
		tigl::shader->setFogExp(.15f);
	}
	else {
		tigl::shader->enableFog(false);
	}
}