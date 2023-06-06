#include "RedBall.h"

RedBall::RedBall(std::string filePath, std::string tag) : Ball(filePath, tag) {
}

void RedBall::update(float deltaTime) {
	prevPosition = position;
	if (speed > 0.05f)
	{
		// 0f (0°) <= y <= 6.3f (360°)
		position.x += (moveDirection.x * speed * deltaTime);
		position.z += (moveDirection.y * speed * deltaTime);
		speed -= 0.025f;
	}
	else
	{
		speed = 0;
	}
	checkOutsidePlayField();
}
