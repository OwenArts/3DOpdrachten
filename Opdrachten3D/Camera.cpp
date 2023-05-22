#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(GLFWwindow* window, Ball* ball1, Ball* ball2)
{
	playerOne = ball1;
	playerTwo = ball2;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}


glm::mat4 Camera::getMatrix()
{
	glm::mat4 ret(1.0f);
	ret = glm::rotate(ret, rotation.x, glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, rotation.y, glm::vec3(0, 1, 0));
	//ret = glm::translate(ret, position + glm::vec3(0,0,-distanceToObject));
	//return ret;

	// Calculate the camera position based on the rotation, distance, and the player's position
	glm::vec3 cameraPosition;

	if (activePlayer)
	{
		glm::vec3 playerTwoPosition = playerTwo->getPosition() + glm::vec3(0, 1.f, 0);
		glm::vec3 offset(0, 0, distanceToObject);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -rotation.y, glm::vec3(0, 1, 0));
		glm::vec4 rotatedOffset = rotationMatrix * glm::vec4(offset, 1.0f);
		cameraPosition = playerTwoPosition + glm::vec3(rotatedOffset);
	}
	else
	{
		glm::vec3 playerOnePosition = playerOne->getPosition() + glm::vec3(0, 1.f, 0);
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

	//std::cout << rotation.y << std::endl;

	lastX = x;/*
	if (activePlayer)
	{
		position.x = -playerTwo->getPosition().x;
		position.z = -playerTwo->getPosition().z;
	}
	else
	{
		position.x = -playerOne->getPosition().x;
		position.z = -playerOne->getPosition().z;
	}*/


	// Adds the movement via awsd - REMOVED
	/*
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move(0, 0.05f);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move(180, 0.05f);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		move(90, 0.05f);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		move(-90, 0.05f);
	*/

}