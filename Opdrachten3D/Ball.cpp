#include "ball.h"

Ball::Ball(std::string filePath, std::string tag)
{
	path = filePath;
	model = new ObjModel(path);
	this->tag = tag;
}

void Ball::move(float direction, float speed)
{
	move(glm::vec2(-sin(direction), cos(direction)), speed);
}

void Ball::move(glm::vec2 direction, float speed)
{
	std::cout << tag << " got moved in the following direction [" << direction.x << "," << direction.y << "] with a speed of " << speed << std::endl;
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
	prevPosition = position;
	if (speed > 0.05f)
	{
		//direction.x -= 0.4f;									//Too buggy, rotates in front of the obj model instead of own center.
		// 0f (0°) <= y <= 6.3f (360°)
		position.x += (direction.x * speed * deltaTime);
		position.z += (direction.y * speed * deltaTime);
		speed -= 0.005f;
	}
	else
	{
		speed = 0;
	}
	checkOutsidePlayField();
}

float Ball::getSpeed()
{
	return speed;
}

glm::vec2 Ball::getDirection()
{
	return direction;
}

void Ball::setSpeed(float speed)
{
	this->speed = speed;
}

void Ball::setDirection(float direction)
{
	this->direction.x = -sin(direction);
	this->direction.y = cos(direction);
}

void Ball::setDirection(glm::vec2 direction)
{
	this->direction = direction;
}

void Ball::changeDirection(bool vertical, bool horizontal)
{
	if (vertical)
		direction.y = -direction.y;
	if (horizontal)
		direction.x = -direction.x;
	//setPosition(prevPosition);
}

void Ball::setPosition(glm::vec3 position) {
	this->position = position;
}

void Ball::checkOutsidePlayField() {
	if (position.x > leftWall)
		position.x = 1.79f;
	if (position.x < rightWall)
		position.x = -1.79f;
	if (position.z > upperWall)
		position.z = 2.78f;
	if (position.z < lowerWall)
		position.z = -2.78f;
}