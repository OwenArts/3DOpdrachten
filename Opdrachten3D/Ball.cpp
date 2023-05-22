#include "ball.h"

Ball::Ball(std::string filePath)
{
	path = filePath;
	model = new ObjModel(path);
}

void Ball::move(glm::vec2 direction, float speed)
{
	this->direction = direction;
	this->speed = speed;
}

void Ball::draw()
{
	glm::mat4 modelMatrix(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, direction.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, direction.y, glm::vec3(0, 1, 0));

	tigl::shader->setModelMatrix(modelMatrix);
	model->draw();
}

glm::vec3 Ball::getPosition()
{
	return position;
}


void Ball::update(float deltaTime)
	{
		if (speed > 0.05f)
		{
			//direction.x -= 0.4f;									//Too buggy
			// 0f (0) <= y <= 6.3f (360)
			position.x += (-sin(direction.y) * speed * deltaTime);
			position.z += (cos(direction.y) * speed * deltaTime);
			speed -= 0.007f;
			//position.y += -sin(direction.x)/80.f;
			//std::cout << "Speed: " << speed << ", Direction: [" << direction.x << "(not important), " << direction.y << "], deltatime: " << deltaTime << std::endl;
		}
		else
		{
			speed = 0;
		}
}

float Ball::getSpeed()
{
	return speed;
}