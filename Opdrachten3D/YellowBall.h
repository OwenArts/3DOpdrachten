#pragma once
#include <string>
#include "ball.h"

class YellowBall : public Ball
{
private:
	int cushions_touched;
public:

	YellowBall(std::string filePath, std::string tag);
};
