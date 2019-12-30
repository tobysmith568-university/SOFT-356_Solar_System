#include "CameraUtil.h"
#include <glm\ext\matrix_transform.hpp>

using namespace glm;

CameraUtil::CameraUtil(InputManager& _inputManager)
	: inputManager(_inputManager)
{
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	cameraSpeed = 0.02f;

	SetUpKeyPresses();
}

glm::mat4 CameraUtil::GetView()
{
	return lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void CameraUtil::SetUpKeyPresses()
{
	inputManager.RegisterKeyRepeat(KeyBinding::MoveForward, [&]()
		{
			cameraPos += cameraSpeed * cameraFront;
		});

	inputManager.RegisterKeyRepeat(KeyBinding::MoveBackward, [&]()
		{
			cameraPos -= cameraSpeed * cameraFront;
		});

	inputManager.RegisterKeyRepeat(KeyBinding::MoveLeft, [&]()
		{
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		});

	inputManager.RegisterKeyRepeat(KeyBinding::MoveRight, [&]()
		{
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		});
}
