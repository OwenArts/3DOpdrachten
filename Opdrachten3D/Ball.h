#pragma once
#include <glm/glm.hpp>
#include "iostream"
#include <glm/gtc/matrix_transform.hpp>
#include "ObjModel.h"
#include "tigl.h"
#include <string>

class Ball
{
public:
	ObjModel* model;

	Ball(std::string filePath);
	void update(float deltaTime);
	void draw();
	void move(glm::vec2 direction, float speed);
	glm::vec3 getPosition();
	float getSpeed();

protected:
	std::string path;
	float speed;
	glm::vec3 position = glm::vec3(0, 2, 0);
	glm::vec2 direction = glm::vec2(0, 0);
};