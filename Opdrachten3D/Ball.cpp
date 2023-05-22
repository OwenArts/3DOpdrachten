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
			position.x += (direction.x * speed * deltaTime);
			position.z += (direction.y * speed * deltaTime);
			speed -= 0.01f;
			std::cout << speed << std::endl;
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