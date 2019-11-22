#include "GlfwUtil.h"

using namespace std;

GlfwUtil::GlfwUtil(ConfigUtil& _configUtil, InputManager& _inputManager)
	: configUtil(_configUtil), inputManager(_inputManager)
{
	window = nullptr;
}

void GlfwUtil::Init()
{
	glfwInit();

	int windowWidth = configUtil.GetInt(IntSetting::WindowWidth);
	int windowHeight = configUtil.GetInt(IntSetting::WindowHeight);
	string windowTitle = configUtil.GetString(StringSetting::WindowTitle);

	if (configUtil.GetBool(BoolSetting::FullScreenOnStartup))
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		window = glfwCreateWindow(mode->width, mode->height, &windowTitle[0], monitor, NULL);
	}
	else
	{
		window = glfwCreateWindow(windowWidth, windowHeight, &windowTitle[0], NULL, NULL);
	}

	glfwMakeContextCurrent(window);

	inputManager.BindWindow(window);
	inputManager.RegisterKeyPress(KeyBinding::Quit, [&]()
		{
			SetShouldClose(true);
		});
}

void GlfwUtil::Update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void GlfwUtil::WireFrameOnly()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

bool GlfwUtil::GetShouldClose()
{
	return glfwWindowShouldClose(window);
}

void GlfwUtil::SetShouldClose(bool shouldClose)
{
	glfwSetWindowShouldClose(window, shouldClose);
}

void GlfwUtil::Exit()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
