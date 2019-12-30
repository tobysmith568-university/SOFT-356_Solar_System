#include "TimeUtil.h"

TimeUtil::TimeUtil()
{
	deltaTime = 0.0f;
	lastFrame = 0.0f;
}

void TimeUtil::Update()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

GLfloat TimeUtil::GetDeltaTime()
{
	return deltaTime;
}
