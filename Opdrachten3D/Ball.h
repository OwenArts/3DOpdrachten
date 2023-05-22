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
	int init_ball();
	void update();
	void draw();
	void move(glm::vec2 direction, float speed);
	glm::vec3 getPosition();

protected:
	std::string path;
	float speed;
	glm::vec3 position = glm::vec3(0, 2, 0);
	glm::vec2 direction = glm::vec2(0, 0);
};