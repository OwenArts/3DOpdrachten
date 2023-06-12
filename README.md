# Three-Cushion Billiards OpenGL

This is a C++ project that simulates the game of three-cushion billiards, where players aim to hit a ball against three cushions before it comes to a stop. The project utilizes OpenGL for 3D rendering and implements camera control using keyboard and mouse input.

![Game Screenshot](/images/screenshot.png)

## Installation

Follow these steps to install and run the project locally:

1. Clone the repository to your local machine:
   ```
   git clone https://github.com/OwenArts/Three_Cushion_Billiard_OpenGL.git
   ```

2. Navigate to the project directory:
   ```
   cd three-cushion-billiards
   ```

3. Install the necessary libraries and dependencies. *(Specify the required libraries, such as OpenGL, GLFW, GLM, and any other dependencies. Provide instructions for installing these libraries, such as using package managers like apt, brew, or manual installation.)*

4. Compile the project:
   ```
   g++ main.cpp -o three-cushion-billiards -lOpenGL -lGLFW -lGLM
   ```

5. Run the game:
   ```
   ./three-cushion-billiards
   ```

## Usage

* How to play the game and which controls are used:
  - Use the "a" and "d" keys or the left and right arrow keys to move the camera and aim the active player's ball.
  - Move the mouse to change the camera direction.
  - Click the mouse to fire the ball in the direction you are looking with the camera.
  - After each turn, the camera will move to the other ball, and it will be the other player's turn.

* This is only the start and basic of a Three-Cushion Billiards game. Therefor it may still contain some bugs and not all Three-Cushion Billiards rules are implemented. There is no point system and the system doesn't check if the player has touched three cushions before touching the second ball.
   - The particle system seems to be fixed to the red ball's position, this is a known bug. 

## Examples

The camera rotates around the ball using an offset, this is a glm::vec3 called distanceToObject. The camera class has a boolean to know what player to follow. It's usage can be seen underneath.
```cpp
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
```

A ball moves in the direction the camera is looking, this is done using sinus and cosinus because the camera's direction is a floating value. 
```cpp
void Ball::move(float direction, float speed)
{
	move(glm::vec2(-sin(direction), cos(direction)), speed);
	lookDirection.y = direction;
}

void Ball::move(glm::vec2 direction, float speed)
{
	this->moveDirection = direction;
	this->speed = speed;
}
```
