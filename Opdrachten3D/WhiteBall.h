#pragma once
#include <string>
#include "ball.h"

class WhiteBall : public Ball
{
private:
	int cushions_touched;
public:
	ObjModel* model;
	std::string path;
	WhiteBall(std::string filePath)
	{
		cushions_touched = 0;
		path = filePath;
	}

	int init_ball()
	{
		std::cout << "Path: " << path << std::endl;
		model = new ObjModel(path);
		return 1;
	}
};