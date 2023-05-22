#pragma once
#include <glm/glm.hpp>
#include "iostream"
#include <glm/gtc/matrix_transform.hpp>
#include "ObjModel.h"
#include "tigl.h"
#include <string>
#include "Camera.h"

class Ceu
{
private:
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec2 rotation = glm::vec2(-0.15f, 0);
	Camera* camera;
	ObjModel* model;
	std::string path;

public:
	Ceu(Camera& camera, std::string path);
	void update(float deltaTime);
	void draw();
	void move();
};