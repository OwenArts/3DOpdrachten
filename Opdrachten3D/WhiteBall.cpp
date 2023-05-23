#include "WhiteBall.h"

WhiteBall::WhiteBall(std::string filePath, std::string tag) : Ball(filePath, tag) {
	cushions_touched = 0;
	position += glm::vec3(1, 0, 2);
}
