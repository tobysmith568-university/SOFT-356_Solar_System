#include "TimeUtil.h"

TimeUtil::TimeUtil()
{
	deltaTime = 0.0f;
	lastFrame = 0.0f;
}

// Recreates the current deltaTime - needs to be called at the begining of every frame
void TimeUtil::Update()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

// Returns the deltaTime of the current frame
GLfloat TimeUtil::GetDeltaTime()
{
	return deltaTime;
}
