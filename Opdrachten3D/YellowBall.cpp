#include "YellowBall.h"

YellowBall::YellowBall(std::string filePath) : Ball(filePath) {
	cushions_touched = 0;
	position += glm::vec3(-1, 0, 2);
}
