#pragma once
#include <glm/glm.hpp>

class BilliardTable
{
private:
	glm::vec3 position = glm::vec3(0, 0, 0);

public:
	BilliardTable();
	glm::mat4 getMatrix();
};