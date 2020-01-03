#pragma once

#include "ConfigUtil.h"
#include "CameraUtil.h"

#include "GLFW/glfw3.h"
#include "InputManager.h"

class GLFWUtil
{
public:
	GLFWUtil(ConfigUtil& _configUtil, InputManager& _inputManager, CameraUtil& _cameraUtil);
	void Init();
	void Update();
	void WireFrameOnly();
	bool GetShouldClose();
	void SetShouldClose(bool shouldClose);
	void Exit();
private:
	ConfigUtil& configUtil;
	InputManager& inputManager;
	CameraUtil& cameraUtil;

	GLFWwindow* window;
};