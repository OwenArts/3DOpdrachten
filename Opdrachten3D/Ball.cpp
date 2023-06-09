#include "ball.h"

Ball::Ball(std::string filePath, std::string tag) : path(filePath), model(new ObjModel(filePath)), tag(tag)
{
}

Ball::~Ball() {
	delete model;
}

void Ball::move(float direction, float speed)
{
	move(glm::vec2(-sin(direction), cos(direction)), speed);
	lookDirection.y = direction;
	std::cout << "recieved direction: " << direction << ", calculated y moveDirection: " << moveDirection.y << ", calculated back: " << std::acosf (moveDirection.y) << std::endl;
}

void Ball::move(glm::vec2 direction, float speed)
{
	std::cout << tag << " got moved in the following direction [" << direction.x << "," << direction.y << "] with a speed of " << speed << std::endl;
	this->moveDirection = direction;
	this->speed = speed;
}

void Ball::draw()
{
	glm::mat4 modelMatrix(1.0f);
	glTranslatef(0.0f, 0.25f, -0.25f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, lookDirection.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, lookDirection.y, glm::vec3(0, 1, 0));

	tigl::shader->setModelMatrix(modelMatrix);
	model->draw();
}

void Ball::update(float deltaTime)
{
	prevPosition = position;
	if (speed > 0.05f)
	{
		// 0f (0°) <= y <= 6.3f (360°)
		position.x += (moveDirection.x * speed * deltaTime);
		position.z += (moveDirection.y * speed * deltaTime);
		lookDirection.y -= 0.025f * speed;

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

glm::vec2 Ball::getMoveDirection()
{
	return moveDirection;
}

void Ball::setSpeed(float speed)
{
	this->speed = speed;
}

void Ball::setMoveDirection(float direction)
{
	this->moveDirection.x = -sin(direction);
	this->moveDirection.y = cos(direction);
}

void Ball::setMoveDirection(glm::vec2 direction)
{
	this->moveDirection = direction;
}

void Ball::changeDirection(bool vertical, bool horizontal)
{
	if (vertical)
		moveDirection.y = -moveDirection.y;
	if (horizontal)
		moveDirection.x = -moveDirection.x;
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