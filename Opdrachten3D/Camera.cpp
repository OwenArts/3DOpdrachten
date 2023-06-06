#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(GLFWwindow* window, Ball& ball1, Ball& ball2)
{
	playerOne = &ball1;
	playerTwo = &ball2;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

glm::mat4 Camera::getMatrix()
{
	glm::mat4 ret(1.0f);
	ret = glm::rotate(ret, rotation.x, glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, rotation.y, glm::vec3(0, 1, 0));
	
	glm::vec3 cameraPosition;
	if (activePlayer)
	{
		glm::vec3 playerTwoPosition = playerTwo->position + glm::vec3(0, 1.f, 0);
		glm::vec3 offset(0, 0, distanceToObject);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -rotation.y, glm::vec3(0, 1, 0));
		glm::vec4 rotatedOffset = rotationMatrix * glm::vec4(offset, 1.0f);
		cameraPosition = playerTwoPosition + glm::vec3(rotatedOffset);
	}
	else
	{
		glm::vec3 playerOnePosition = playerOne->position + glm::vec3(0, 1.f, 0);
		glm::vec3 offset(0, 0, distanceToObject);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -rotation.y, glm::vec3(0, 1, 0));
		glm::vec4 rotatedOffset = rotationMatrix * glm::vec4(offset, 1.0f);
		cameraPosition = playerOnePosition + glm::vec3(rotatedOffset);
	}
	ret = glm::translate(ret, -cameraPosition);

	return ret;
}

void Camera::move(float angle, float fac)
{
	position.x += (float)cos(rotation.y + glm::radians(angle)) * fac;
	position.z += (float)sin(rotation.y + glm::radians(angle)) * fac;
}


void Camera::update(GLFWwindow* window, bool activePlayer)
{
	this->activePlayer = activePlayer;
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	static double lastX = x;
	
	if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)) // Rotate to the right on pressing Left arrow or A
		lastX = x + 5;
	if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)) // Rotate to the right on pressing right arrow or D
		lastX = x - 5;

	rotation.y -= (float)(lastX - x) / 100.0f;
	if (rotation.y < 0)
		rotation.y = 6.3f - fmod(rotation.y, 6.3f);
	else
		rotation.y = fmod(rotation.y, 6.3f);


	lastX = x;
}


glm::vec3 Camera::getPosition() 
{
	return position;
}

glm::vec2 Camera::getRotation()
{
	return rotation;
}