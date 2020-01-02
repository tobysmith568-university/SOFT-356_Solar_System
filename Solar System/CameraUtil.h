#pragma once

#include "InputManager.h"
#include "TimeUtil.h"

#include <glm/glm.hpp>
#include <glm/fwd.hpp>

class CameraUtil
{
public:
	CameraUtil(InputManager& _inputManager, TimeUtil& _timeUtil, ConfigUtil& _configUtil);

	glm::mat4 GetView();

private:
	InputManager& inputManager;
	TimeUtil& timeUtil;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	GLfloat cameraSpeed;

	bool firstRun = true;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat yaw;
	GLfloat pitch;

	bool isFPSStyle = false;

	void SetUpKeyPresses();
	void SetUpMouseMovement();

	void UpdatePositions(GLfloat xpos, GLfloat ypos);
};