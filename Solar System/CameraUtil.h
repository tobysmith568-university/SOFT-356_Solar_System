#pragma once

#include "InputManager.h"

#include <glm/glm.hpp>
#include <glm/fwd.hpp>

class CameraUtil
{
public:
	CameraUtil(InputManager& _inputManager);

	glm::mat4 GetView();

private:
	InputManager& inputManager;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	GLfloat cameraSpeed;

	void SetUpKeyPresses();
};