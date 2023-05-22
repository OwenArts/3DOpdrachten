#include "ball.h"

Ball::Ball(std::string filePath)
{
	path = filePath;
}

int Ball::init_ball()
{
	try
	{
		std::cout << "Path: " << path << std::endl;
		model = new ObjModel(path);
		return 0;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
		return -1;
	}
}

void Ball::move(glm::vec2 direction, float speed)
{
	position.x += (direction.x * speed);
	position.z += (direction.y * speed);
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


void Ball::update()
{

}