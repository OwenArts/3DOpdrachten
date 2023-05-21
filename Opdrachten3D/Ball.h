#pragma once
#include <glm/glm.hpp>
#include "iostream"
#include "ObjModel.h"


class Ball
{
private:
	float speed;
	glm::vec3 location;

public:
	virtual int init_ball() {
		try
		{
			std::cout << "Loading..." << std::endl;
			return 0;
		}
		catch (const std::exception& ex) {
			std::cout << ex.what();
			return -1;
		}
	}

	void move(glm::vec2 direction, float speed)
	{

		// TODO: test
		location.x = location.x * direction.x * speed;
		location.y = location.y * direction.y * speed;
	}
};