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

/* TODO (3D):
*	Bal toevoegen (ball.cpp, white-, red-, yellowball.cpp)						DONE
*	Bal logica (locatie, richting, snelheid (afnemend), botsing, etc)			DONE (richting, snelheid)
*	3 Cushion Billiard logica toevoegen
*	Camera laten bewegen om juiste bal											DONE
*	Afmetigen tafel																DONE
*	Collision met randen tafel													DONE
*	Collision met andere ballen													DONE - still buggy
*	Stok logica (afschieten, richting laten bepalen door gebruiker, etc)		DONE (afschieten muisklik, richting dmv a,d, pijlknoppen en muis)
*	Belichting																	DONE
*	mist/fog																	DONE
*	Automatisch bewegend object (Keu of bal laten rollen)
*	Alpha blending (cue transparant maken)
*	Speler object laten bedienen (zie `Stok logica`)							DONE
*	Stok toevoegen (ceu.cpp) (aanmaken in blender)								w.i.p. - REMOVED CAUSE BUGS, SHIFTED TO END OF PROJECT
*	Particle toevoegen onder ballen
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
bool activePlayer = false;	//false on whiteball, true on yellowball
double lastFrameTime = 0;

void init();
void update();
void draw();
void enableFog(bool flag);
void enableLight(bool state);
void CheckForCollisionBall(Ball& one, Ball& two);
void CheckForCollisionTable(Ball& ball);

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
				if (whiteBall->getSpeed() < 0.05f)
					whiteBall->move(camera->getRotation().y, 3.f);
			}
			if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && activePlayer)
			{
				if (yellowBall->getSpeed() < 0.05f)
					yellowBall->move(camera->getRotation().y, 3.f);
			}
		});

	// Load all moddels
	biljartTable[0] = new ObjModel("models/biljard/Biljart_table.obj");
	biljartTable[1] = new ObjModel("models/biljard/Biljart_edge.obj");
	biljartTable[2] = new ObjModel("models/biljard/Biljart_cloth.obj");
	whiteBall = new WhiteBall("models/ball/WhiteBall.obj", "WhiteBall");
	redBall = new RedBall("models/ball/RedBall.obj", "RedBall");
	yellowBall = new YellowBall("models/ball/YellowBall.obj", "YellowBall");
	camera = new Camera(window, *whiteBall, *yellowBall);
	ceu = new Ceu(*camera, "models/ceu/Ceu.obj");
}

void update()
{
	double frameTime = glfwGetTime();
	float deltaTime = lastFrameTime - frameTime;
	lastFrameTime = frameTime;

	if (!activePlayer && (whiteBall->getSpeed() <= 0.05f && whiteBall->getSpeed() > 0))
		activePlayer = !activePlayer;
	if (activePlayer && (yellowBall->getSpeed() <= 0.05f && yellowBall->getSpeed() > 0))
		activePlayer = !activePlayer;

	camera->update(window, activePlayer);
	whiteBall->update(deltaTime);
	yellowBall->update(deltaTime);
	redBall->update(deltaTime);
	ceu->update(deltaTime);

	CheckForCollisionTable(*whiteBall);
	CheckForCollisionTable(*yellowBall);
	CheckForCollisionTable(*redBall);
	CheckForCollisionBall(*whiteBall, *yellowBall);
	CheckForCollisionBall(*whiteBall, *redBall);
	CheckForCollisionBall(*yellowBall, *redBall);
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
	enableLight(true);


	for (auto& model : biljartTable)
		model->draw();
	whiteBall->draw();
	yellowBall->draw();
	redBall->draw();
	//ceu->draw();
}

void enableFog(bool state)
{
	if (state) {
		tigl::shader->enableFog(true);
		tigl::shader->setFogLinear(1, 4);
		tigl::shader->setFogExp(.15f);
	}
	else {
		tigl::shader->enableFog(false);
	}
}

void enableLight(bool state)
{
	if (state) {
		tigl::shader->enableLighting(true);
		tigl::shader->setLightCount(1);
		tigl::shader->setLightDirectional(0, false);
		tigl::shader->setLightPosition(0, glm::vec3(0, 25, 0));
		tigl::shader->setLightAmbient(0, glm::vec3(0.1f, 0.1f, 0.15f));
		tigl::shader->setLightDiffuse(0, glm::vec3(0.8f, 0.8f, 0.8f));
		tigl::shader->setLightSpecular(0, glm::vec3(225.f / 255, 159.f / 255, 0));
		tigl::shader->setShinyness(5.f);
	}
	else {
		tigl::shader->enableLighting(false);
	}
}

void CheckForCollisionBall(Ball& one, Ball& two)
{
	bool collisionX = false;
	bool collisionZ = false;
	float radius = 0.25f;

	//if (one.getSpeed() != 0)
	//{
	//	std::cout << "[ORIGINAL]	ball1 [" << round(one.getPosition().x * 10.0) / 10.0 << "," << round(one.getPosition().z * 10.0) / 10.0 << "], ball2 [" << round(two.getPosition().x * 10.0) / 10.0 << "," << round(two.getPosition().z * 10.0) / 10.0 << "]" << std::endl;
	//	std::cout << "[IF STATEMENT] (x) condition 1 [" << (round(one.getPosition().x * 10.f) / 10.f < (round(two.getPosition().x * 10.f) / 10.f) - 0.1f) << "]" << std::endl;
	//	std::cout << "[IF STATEMENT] (x) condition 2 [" << (round(one.getPosition().x * 10.f) / 10.f > (round(two.getPosition().x * 10.f) / 10.f) + 0.1f) << "]" << std::endl;
	//	std::cout << "[IF STATEMENT] (x) condition 1&2 [" << ((round(one.getPosition().x * 10.f) / 10.f < round(two.getPosition().x * 10.f) / 10.f && round(one.getPosition().x * 10.f) / 10.f > round(two.getPosition().x * 10.f) / 10.f) || round(one.getPosition().x * 10.f) / 10.f == round(two.getPosition().x * 10.f) / 10.f) << "]" << std::endl;
	//	std::cout << "[IF STATEMENT] (y) condition 1 [" << (round(one.getPosition().z * 10.f) / 10.f <= round(two.getPosition().z * 10.f) / 10.f - 0.1f) << "]" << std::endl;
	//	std::cout << "[IF STATEMENT] (y) condition 2 [" << (round(one.getPosition().z * 10.f) / 10.f >= round(two.getPosition().z * 10.f) / 10.f + 0.1f) << "]" << std::endl;
	//	std::cout << "[IF STATEMENT] (y) condition 1&2 [" << (round(one.getPosition().z * 10.f) / 10.f <= round(two.getPosition().z * 10.f) / 10.f && round(one.getPosition().z * 10.f) / 10.f >= round(two.getPosition().z * 10.f) / 10.f) << "]" << std::endl;
	//	std::cout << "--------------------------------------------------------------------------" << std::endl;
	//}

	if ((round(one.getPosition().x * 10.f) / 10.f < round(two.getPosition().x * 10.f) / 10.f + radius &&
		round(one.getPosition().x * 10.f) / 10.f > round(two.getPosition().x * 10.f) / 10.f - radius) ||
		round(one.getPosition().x * 10.f) / 10.f == round(two.getPosition().x * 10.f) / 10.f)
	{
		collisionX = true;
	}

	if ((round(one.getPosition().z * 10.f) / 10.f < round(two.getPosition().z * 10.f) / 10.f + radius &&
		round(one.getPosition().z * 10.f) / 10.f > round(two.getPosition().z * 10.f) / 10.f - radius) ||
		round(one.getPosition().z * 10.f) / 10.f == round(two.getPosition().z * 10.f) / 10.f)
	{
		collisionZ = true;
	}
	if (collisionX && collisionZ)
	{
		if (one.getSpeed() > two.getSpeed())
		{
			glm::vec2 direction = one.getDirection();
			two.move(direction, one.getSpeed() - 0.5f);
			one.setSpeed(one.getSpeed() - 0.5);
			if (direction.x > direction.y)
				one.changeDirection(false, true);
			if (direction.x < direction.y)
				one.changeDirection(true, false);

		}
		else if (one.getSpeed() < two.getSpeed())
		{
			glm::vec2 direction = two.getDirection();
			one.move(direction, two.getSpeed() - 0.5f);
			if (direction.x > direction.y)
				one.changeDirection(false, true);
			if (direction.x < direction.y)
				one.changeDirection(true, false);

		}
	}
}

void CheckForCollisionTable(Ball& ball)
{
	/*
	*  ORGINEEL - COORDS HOEKEN TAFEL
	*	X = -1.8063,	Z = -2.76143 	-	RECHTS ONDER (VANAF STARTPUNT)
	*	X = -1.81101,	Z =  2.78461	-	RECHTS BOVEN (VANAF STARTPUNT)
	*	X = 1.80754,	Z =  2.73023	-	LINKS BOVEN (VANAF STARTPUNT)
	*	X = 1.81428,	Z = -2.81266	-	lINKS ONDER (VANAF STARTPUNT)
	*
	*  AFGEROND - COORDS HOEKEN TAFEL
	*	X = -1.81,	Z = -2.80 	-	RECHTS ONDER (VANAF STARTPUNT)
	*	X = -1.81,	Z =  2.80	-	RECHTS BOVEN (VANAF STARTPUNT)
	*	X =  1.81,	Z =  2.80	-	LINKS BOVEN (VANAF STARTPUNT)
	*	X =  1.81,	Z = -2.80	-	lINKS ONDER (VANAF STARTPUNT)
	*/
	float leftWall = 1.81f;
	float rightWall = -1.81f;
	float upperWall = 2.80f;
	float lowerWall = -2.80f;
	glm::vec3 coords = ball.getPosition();

	if (coords.x >= leftWall || coords.x <= rightWall) ball.changeDirection(false, true);
	if (coords.z >= upperWall || coords.z <= lowerWall) ball.changeDirection(true, false);
}