#pragma once

#include "GLFW/glfw3.h"

class TimeUtil
{
public:
	TimeUtil();

	void Update();
	GLfloat GetDeltaTime();

private:
	GLfloat deltaTime;
	GLfloat lastFrame;
};

