#include "Ceu.h"
#include "Camera.h"
#include <iostream>

Ceu::Ceu(Camera& camera)
{
	this->camera = &camera;
	//TODO load object, move to camera pos (0,-.25,0), automatic movement using sin()
}