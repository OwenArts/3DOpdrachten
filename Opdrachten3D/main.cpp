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
#include "ParticleSystem.h"
#include "FileManager.h"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
std::vector<ObjModel*> biljardTable;
Camera* camera;
float rotation = 0;
WhiteBall* whiteBall;
RedBall* redBall;
YellowBall* yellowBall;
ParticleSystem* particleSystemWhiteBall, * particleSystemYellowBall, * particleSystemRedBall;
bool activePlayer = false;	//false on whiteball, true on yellowball
double lastFrameTime = 0;
glm::vec3 worldColor = glm::vec3(0.3f, 0.4f, 0.6f);
std::string savePath = "GameData";
FileManager* fileManager;


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
	window = glfwCreateWindow(1680, 960, "Three cushion billiard", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);

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
	tigl::init();
	fileManager = new FileManager("config.txt");
	activePlayer = fileManager->readActivePlayer();
	
	enableFog(true);
	enableLight(true);

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
	biljardTable.push_back(new ObjModel("models/biljard/Biljart_table.obj"));
	biljardTable.push_back(new ObjModel("models/biljard/Biljart_edge.obj"));
	biljardTable.push_back(new ObjModel("models/biljard/Biljart_cloth.obj"));
	/*biljartTable[0] = new ObjModel("models/biljard/Biljart_table.obj");
	biljartTable[1] = new ObjModel("models/biljard/Biljart_edge.obj");
	biljartTable[2] = new ObjModel("models/biljard/Biljart_cloth.obj");*/
	redBall = new RedBall("models/ball/RedBall.obj", "RedBall");
	whiteBall = new WhiteBall("models/ball/WhiteBall.obj", "WhiteBall");
	yellowBall = new YellowBall("models/ball/YellowBall.obj", "YellowBall");
	camera = new Camera(window, *whiteBall, *yellowBall);

	// Initiate particle systems
	particleSystemWhiteBall = new ParticleSystem(50, *whiteBall);
	particleSystemYellowBall = new ParticleSystem(100, *yellowBall);
	particleSystemRedBall = new ParticleSystem(100, *redBall);
}

void update()
{
	double frameTime = glfwGetTime();
	float deltaTime = lastFrameTime - frameTime;
	lastFrameTime = frameTime;

	// Handles the active player, writes the active player to a file on change.
	if (!activePlayer && (whiteBall->getSpeed() <= 0.05f && whiteBall->getSpeed() > 0))
	{
		activePlayer = !activePlayer;
		fileManager->writeActivePlayer(activePlayer);
	}
	if (activePlayer && (yellowBall->getSpeed() <= 0.05f && yellowBall->getSpeed() > 0))
	{
		activePlayer = !activePlayer;
		fileManager->writeActivePlayer(activePlayer);
	}

	// Update the camera, balls and particles
	camera->update(window, activePlayer);
	whiteBall->update(deltaTime);
	particleSystemWhiteBall->updateParticles(deltaTime);
	yellowBall->update(deltaTime);
	particleSystemYellowBall->updateParticles(deltaTime);
	redBall->update(deltaTime);
	particleSystemRedBall->updateParticles(deltaTime);

	// Check for all collision types
	CheckForCollisionTable(*whiteBall);
	CheckForCollisionTable(*yellowBall);
	CheckForCollisionTable(*redBall);
	CheckForCollisionBall(*whiteBall, *yellowBall);
	CheckForCollisionBall(*yellowBall, *redBall);
	CheckForCollisionBall(*redBall, *whiteBall);
}

void draw()
{
	glClearColor(worldColor.x, worldColor.y, worldColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 100.0f);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(camera->getMatrix());
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(true);

	glEnable(GL_DEPTH_TEST);

	// Draw the table and balls
	for (const auto& model : biljardTable)
		model->draw();

	whiteBall->draw();
	yellowBall->draw();
	redBall->draw();

	// Render particles
	particleSystemWhiteBall->renderParticles();
	particleSystemYellowBall->renderParticles();
	particleSystemRedBall->renderParticles();
}

// Enables/disables the fog. Sets the color to the same color as the background of the world.
void enableFog(bool state)
{
	if (state) {
		tigl::shader->enableFog(true);
		tigl::shader->setFogLinear(1, 4);
		tigl::shader->setFogColor(worldColor);
		tigl::shader->setFogExp(.15f);
	}
	else {
		tigl::shader->enableFog(false);
	}
}

// Enables/disables the lighting. 
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

// Checks if ball 1 and ball 2 have collision based on their position and radius. if there is a collision on both the z- and x-axis, the ball with the lowest speed wil get the speed of the other ball -0,5f.
void CheckForCollisionBall(Ball& one, Ball& two)
{
	bool collisionX = false;
	bool collisionZ = false;
	float radius = 0.25f;


	if ((round(one.position.x * 10.f) / 10.f < round(two.position.x * 10.f) / 10.f + radius &&
		round(one.position.x * 10.f) / 10.f > round(two.position.x * 10.f) / 10.f - radius) ||
		round(one.position.x * 10.f) / 10.f == round(two.position.x * 10.f) / 10.f)
	{
		collisionX = true;
	}

	if ((round(one.position.z * 10.f) / 10.f < round(two.position.z * 10.f) / 10.f + radius &&
		round(one.position.z * 10.f) / 10.f > round(two.position.z * 10.f) / 10.f - radius) ||
		round(one.position.z * 10.f) / 10.f == round(two.position.z * 10.f) / 10.f)
	{
		collisionZ = true;
	}
	if (collisionX && collisionZ)
	{
		if (one.getSpeed() > two.getSpeed())
		{
			glm::vec2 direction = one.getMoveDirection();
			if (one.getSpeed() > 1.f)
				two.move(direction, one.getSpeed() - 0.5f);
			if (direction.x > direction.y)
				one.changeDirection(false, true);
			if (direction.x < direction.y)
				one.changeDirection(true, false);
		}
		else if (one.getSpeed() < two.getSpeed())
		{
			glm::vec2 direction = two.getMoveDirection();
			if (two.getSpeed() > 1.f)
				one.move(direction, two.getSpeed() - 0.5f);
			if (direction.x > direction.y)
				one.changeDirection(false, true);
			if (direction.x < direction.y)
				one.changeDirection(true, false);
		}
	}
}

// Checks if a ball has collision with the edges of the table.
void CheckForCollisionTable(Ball& ball)
{
	/*
	*   Table corners
	*	X = -1.81,	Z = -2.80 	-	Lower right
	*	X = -1.81,	Z =  2.80	-	Upper right
	*	X =  1.81,	Z =  2.80	-	Upper left
	*	X =  1.81,	Z = -2.80	-	Lower left
	*/
	float leftWall = 1.81f;
	float rightWall = -1.81f;
	float upperWall = 2.80f;
	float lowerWall = -2.80f;
	glm::vec3 coords = ball.position;

	if (coords.x >= leftWall || coords.x <= rightWall) ball.changeDirection(false, true);
	if (coords.z >= upperWall || coords.z <= lowerWall) ball.changeDirection(true, false);
}