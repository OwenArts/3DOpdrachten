#pragma once
#include "Ball.h"
#include <glm/glm.hpp>

struct GLFWwindow;

class Camera
{
public:
	Camera(GLFWwindow*, Ball& ball1, Ball& ball2);
	~Camera();

	glm::mat4 getMatrix();
	void update(GLFWwindow*, bool activePlayer);
	glm::vec3 getPosition();
	glm::vec2 getRotation();


private:
	glm::vec3 position = glm::vec3(0, -2.5f, 0);	// -3 to be above the table and ball
	glm::vec2 rotation = glm::vec2(0.5, 0);		// 0.5 to look down a bit
	float distanceToObject = 1.f;
	bool activePlayer = false;
	void move(float angle, float fac);
	Ball* playerOne,* playerTwo;
};


