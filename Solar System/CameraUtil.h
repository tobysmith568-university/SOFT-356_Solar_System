#pragma once

#include "InputManager.h"
#include "TimeUtil.h"

#include <glm/glm.hpp>
#include <glm/fwd.hpp>

class CameraUtil
{
public:
	CameraUtil(InputManager& _inputManager, TimeUtil& _timeUtil);

	glm::mat4 GetView();

private:
	InputManager& inputManager;
	TimeUtil& timeUtil;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	GLfloat cameraSpeed;

	void SetUpKeyPresses();
};