#include "CameraUtil.h"
#include <glm\ext\matrix_transform.hpp>

using namespace glm;

CameraUtil::CameraUtil(InputManager& _inputManager, TimeUtil& _timeUtil, ConfigUtil& _configUtil)
	: inputManager(_inputManager), timeUtil(_timeUtil)
{
	//Start beside looking forward
	/*cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);*/

	//Start above looking down
	/*cameraPos = vec3(0.0f, 3.0f, 0.0f);
	cameraFront = vec3(0.0f, -90.0f, -1.0f);
	cameraUp = vec3(0.0f, 1.0f, 0.0f);*/

	//Start beside and above looking diagonally down
	cameraPos = vec3(3.0f, 3.0f, 0.0f);
	cameraFront = vec3(0.0f, -45.0f, -1.0f);
	cameraUp = vec3(0.0f, 1.0f, 0.0f);

	isFPSStyle = _configUtil.GetBool(BoolSetting::StartOnFPSStyle);
	cameraSpeed = _configUtil.GetFloat(FloatSetting::MovementSpeed);

	SetUpKeyPresses();
	SetUpMouseMovement();
}

glm::mat4 CameraUtil::GetView()
{
	return lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void CameraUtil::SetUpKeyPresses()
{
	inputManager.RegisterKeyRepeat(KeyBinding::MoveForward, [&]()
		{
			cameraPos += cameraSpeed * cameraFront * timeUtil.GetDeltaTime();
		});

	inputManager.RegisterKeyRepeat(KeyBinding::MoveBackward, [&]()
		{
			cameraPos -= cameraSpeed * cameraFront * timeUtil.GetDeltaTime();
		});

	inputManager.RegisterKeyRepeat(KeyBinding::MoveLeft, [&]()
		{
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * timeUtil.GetDeltaTime();
		});

	inputManager.RegisterKeyRepeat(KeyBinding::MoveRight, [&]()
		{
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * timeUtil.GetDeltaTime();
		});

	inputManager.RegisterKeyPress(KeyBinding::ToggleFPSStyle, [&]()
		{
			isFPSStyle = !isFPSStyle;
		});
}

void CameraUtil::SetUpMouseMovement()
{
	inputManager.RegisterMouseMovement([&](GLfloat xpos, GLfloat ypos)
		{
			if (isFPSStyle)
			{
				FPSStyleCameraUpdate(xpos, ypos);
			}
			else
			{

			}
		});
}

void CameraUtil::FPSStyleCameraUpdate(GLfloat xpos, GLfloat ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		pitch = 0;
		yaw = 0;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = -7;
	xoffset *= sensitivity * timeUtil.GetDeltaTime();
	yoffset *= sensitivity * timeUtil.GetDeltaTime();

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	vec3 front;
	front.x = cos(radians(yaw)) * cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw)) * cos(radians(pitch));
	cameraFront = normalize(front);

	std::cout << "Pitch = " << pitch << " Yaw = " << yaw << std::endl;
}

void CameraUtil::ArcballStyleCameraUpdate(GLfloat xpos, GLfloat ypos)
{
}
