#include "Ceu.h"
#include "Camera.h"
#include <iostream>

Ceu::Ceu(Camera& camera, std::string path)
{
	model = new ObjModel(path);
	this->path = path;
	this->camera = &camera;
	//TODO load object, move to camera pos (0,-.25,0), automatic movement using sin()
}

void Ceu::update(float deltaTime)
{
	position = -camera->getPosition();
	rotation.y = -camera->getRotation().y;
	//std::cout << "-------" << std::endl;
	//std::cout << "Ceu: [" << rotation.x << ", " << rotation.y << "]" << std::endl;
	//std::cout << "Ceu: [" << position.x << ", " << position.y <<", " << position.z << "]" << std::endl;

	//std::cout << "Camera: [" << camera->getRotation().x << ", " << camera->getRotation().y << "]" << std::endl;
	//std::cout << "Camera: [" << camera->getPosition().x << ", " << camera->getPosition().y <<", " << camera->getPosition().z << "]" << std::endl;
}

void Ceu::draw()
{
	glm::mat4 modelMatrix(1.0f);
	modelMatrix = glm::translate(modelMatrix, -camera->getPosition() - glm::vec3(-1.f, .9f, -.5f));
	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, -camera->getRotation().y, glm::vec3(0, 1, 0));

	tigl::shader->setModelMatrix(modelMatrix);
	model->draw();
}

void Ceu::move()
{

}