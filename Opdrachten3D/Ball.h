#pragma once
#include <glm/glm.hpp>
#include "iostream"
#include <glm/gtc/matrix_transform.hpp>
#include "ObjModel.h"
#include "tigl.h"
#include <string>

class Ball
{
private:
	const float leftWall = 1.85f;
	const float rightWall = -1.85f;
	const float upperWall = 2.85f;
	const float lowerWall = -2.85f;
	void checkOutsidePlayField();
	glm::vec3 prevPosition;


public:
	ObjModel* model;
	std::string tag;
	glm::vec3 getPosition();
	glm::vec2 getDirection();
	float getSpeed();

	Ball(std::string filePath, std::string tag);
	void update(float deltaTime);
	void draw();
	void move(float direction, float speed);
	void move(glm::vec2 direction, float speed);
	void setSpeed(float speed);
	void setDirection(glm::vec2 direction);
	void setPosition(glm::vec3 position);
	void setDirection(float direction);
	void changeDirection(bool vertical, bool horizontal);
	
protected:
	std::string path;
	float speed;
	glm::vec3 position = glm::vec3(0, 2.f, 0);
	glm::vec2 moveDirection = glm::vec2(0, 0);
	glm::vec2 lookDirection = glm::vec2(0, 0);
};