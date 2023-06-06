#pragma once
#include <string>
#include "ball.h"

class RedBall : public Ball
{
public:
	RedBall(std::string filePath, std::string tag);
	void update(float deltaTime);
};