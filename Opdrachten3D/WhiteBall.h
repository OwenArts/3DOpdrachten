#pragma once
#include <string>
#include "ball.h"

class WhiteBall : public Ball
{
private:
	int cushions_touched;
public:
	WhiteBall(std::string filePath, ObjModel* tableEdge);
};