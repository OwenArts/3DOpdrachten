#pragma once
#include <string>
#include "ball.h"

class RedBall : public Ball
{
public:
	ObjModel* model;
	std::string path;
	RedBall(std::string filePath)
	{
		path = filePath;
	}

	int init_ball()
	{
		std::cout << "Path: " << path << std::endl;
		model = new ObjModel(path);
		return 1;
	}
};