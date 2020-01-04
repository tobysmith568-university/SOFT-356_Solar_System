#include "CameraUtil.h"
#include <glm\ext\matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

using namespace glm;

CameraUtil::CameraUtil(InputManager& _inputManager, TimeUtil& _timeUtil, ConfigUtil& _configUtil)
	: inputManager(_inputManager), timeUtil(_timeUtil)
{
	cameraPos = vec3(3.0f, 3.0f, 0.0f);
	cameraFront = vec3(0.0f, -45.0f, -1.0f);
	cameraUp = vec3(0.0f, 1.0f, 0.0f);

	pitch = yaw = 0;
	cameraSpeed = _configUtil.GetFloat(FloatSetting::MovementSpeed);
	mouseSpeed = _configUtil.GetFloat(FloatSetting::MouseSpeed);
	scrollSpeed = _configUtil.GetFloat(FloatSetting::ScrollSpeed);

	SetUpKeyPresses();
	SetUpMouseMovement();
	SetUpMouseScroll();
}

glm::mat4 CameraUtil::GetViewMatrix()
{
	if (isFPSStyle)
	{
		return lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}
	else
	{
		mat4 view = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};
		
		view = glm::translate(view, vec3(0.0f, 0.0f, -3.0f));
		view = glm::rotate(view, radians(pitch), vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, radians(yaw), vec3(0.0f, -1.0f, 0.0f));

		return view;
	}
}

// Creating a projection matrix
glm::mat4 CameraUtil::GetProjectionMatrix()
{
	return glm::perspective(fov, aspectRatio, 0.1f, 30.0f);
}

void CameraUtil::SetAspectRatio(GLfloat _aspectRatio)
{
	aspectRatio = _aspectRatio;
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
			UpdatePositions(xpos, ypos);
		});
}

void CameraUtil::SetUpMouseScroll()
{
	inputManager.RegisterScrollMovement([&](GLfloat xoffset, GLfloat yoffset)
		{
			fov += yoffset * scrollSpeed * timeUtil.GetDeltaTime();
		});
}

void CameraUtil::UpdatePositions(GLfloat xpos, GLfloat ypos)
{
	if (firstRun)
	{
		lastX = xpos;
		lastY = ypos;
		firstRun = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xoffset *= mouseSpeed * timeUtil.GetDeltaTime();
	yoffset *= mouseSpeed * timeUtil.GetDeltaTime();

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
}