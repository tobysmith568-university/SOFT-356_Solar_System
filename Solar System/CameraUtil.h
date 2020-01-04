#pragma once

#include "InputManager.h"
#include "TimeUtil.h"

#include <glm/glm.hpp>
#include <glm/fwd.hpp>

class CameraUtil
{
public:
	CameraUtil(InputManager& _inputManager, TimeUtil& _timeUtil, ConfigUtil& _configUtil);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	void SetAspectRatio(GLfloat _aspectRatio);

private:
	InputManager& inputManager;
	TimeUtil& timeUtil;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	GLfloat cameraSpeed;
	GLfloat mouseSpeed;
	GLfloat scrollSpeed;

	bool firstRun = true;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat yaw;
	GLfloat pitch;

	bool isFPSStyle = false;

	GLfloat aspectRatio;
	GLfloat fov = 45.0f;

	void SetUpKeyPresses();
	void SetUpMouseMovement();
	void SetUpMouseScroll();

	void UpdatePositions(GLfloat xpos, GLfloat ypos);
};