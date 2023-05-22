#pragma once
#include "Camera.h"
class Ceu
{
private:
	glm::vec3 position = glm::vec3(0, 0, 0);
	Camera* camera;

public:
	Ceu(Camera& camera);
};