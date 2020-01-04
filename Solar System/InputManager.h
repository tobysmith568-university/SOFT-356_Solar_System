#pragma once
#include "ConfigUtil.h"
#include <functional>
#include <GLFW/glfw3.h>

class InputManager
{
public:
	InputManager(ConfigUtil& _configUtil);
	void BindWindow(GLFWwindow* window);

	void RegisterKeyPress(KeyBinding keyBinding, std::function<void()> callback);
	void RegisterKeyRepeat(KeyBinding keyBinding, std::function<void()> callback);
	void RegisterKeyRelease(KeyBinding keyBinding, std::function<void()> callback);
	void RegisterMouseMovement(std::function<void(GLfloat, GLfloat)> callback);
	void RegisterScrollMovement(std::function<void(GLfloat, GLfloat)> callback);

	std::map<int, std::vector<std::function<void()>>> GetKeyPresses();
	std::map<int, std::vector<std::function<void()>>> GetKeyRepeats();
	std::map<int, std::vector<std::function<void()>>> GetKeyReleases();
	std::vector<std::function<void(GLfloat, GLfloat)>> GetMouseMovements();
	std::vector<std::function<void(GLfloat, GLfloat)>> GetScrollMovements();

private:
	ConfigUtil& configUtil;
	std::map<int, std::vector<std::function<void()>>> keyPresses;
	std::map<int, std::vector<std::function<void()>>> keyRepeats;
	std::map<int, std::vector<std::function<void()>>> keyReleases;
	std::vector<std::function<void(GLfloat, GLfloat)>> mouseMovements;
	std::vector<std::function<void(GLfloat, GLfloat)>> scrollMovements;
};