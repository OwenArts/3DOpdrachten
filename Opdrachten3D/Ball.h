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


public:
	ObjModel* model;
	std::string tag;
	glm::vec2 getMoveDirection();
	float getSpeed();

	Ball(std::string filePath, std::string tag);
	virtual void update(float deltaTime);
	void draw();
	void move(float direction, float speed);
	void move(glm::vec2 direction, float speed);
	void setSpeed(float speed);
	void setMoveDirection(float direction);
	void setMoveDirection(glm::vec2 direction);
	void setPosition(glm::vec3 position);
	void changeDirection(bool vertical, bool horizontal);
	glm::vec3 position = glm::vec3(0, 2.f, 0);
	
protected:
	float speed;
	std::string path;
	glm::vec2 moveDirection = glm::vec2(0, 0);
	glm::vec2 lookDirection = glm::vec2(0, 0);
	glm::vec3 prevPosition;
	void checkOutsidePlayField();
};