#include "ball.h"

int init_ball()
{
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