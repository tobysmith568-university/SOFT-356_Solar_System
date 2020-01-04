#include "GLFWUtil.h"
#include "GLFW/glfw3.h"

using namespace std;

GLFWUtil::GLFWUtil(ConfigUtil& _configUtil, InputManager& _inputManager, CameraUtil& _cameraUtil)
	: configUtil(_configUtil), inputManager(_inputManager), cameraUtil(_cameraUtil)
{
}

// Inits GLFW and the window
void GLFWUtil::Init()
{
	glfwInit();

	int windowWidth = configUtil.GetInt(IntSetting::WindowWidth);// Gets config
	int windowHeight = configUtil.GetInt(IntSetting::WindowHeight);
	string windowTitle = configUtil.GetString(StringSetting::WindowTitle);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();// Get monitor information
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	if (configUtil.GetBool(BoolSetting::FullScreenOnStartup))// If the program should be fullscreen
	{
		window = glfwCreateWindow(mode->width, mode->height, &windowTitle[0], monitor, NULL);// Creates a fullscreen window
		cameraUtil.SetAspectRatio((GLfloat)mode->width / (GLfloat)mode->height);
	}
	else
	{
		window = glfwCreateWindow(windowWidth, windowHeight, &windowTitle[0], NULL, NULL);// Creates a windowed window
		cameraUtil.SetAspectRatio((GLfloat)windowWidth / (GLfloat)windowHeight);
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);// Capture the cursor

	glfwMakeContextCurrent(window);

	inputManager.BindWindow(window);// Set the window as the current window in the input manager
	inputManager.RegisterKeyPress(KeyBinding::Quit, [&]()
	{
		SetShouldClose(true);
	});// Create a keybinding for closing the window
}

// To be run every game tick
void GLFWUtil::Update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

// Sets the polygon mode to only use wireframes
void GLFWUtil::WireFrameOnly()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

// Returns if the window has been told to close or not
bool GLFWUtil::GetShouldClose()
{
	return glfwWindowShouldClose(window);
}

// Tells the window that it should or shouldn't close
void GLFWUtil::SetShouldClose(bool shouldClose)
{
	glfwSetWindowShouldClose(window, shouldClose);
}

// Frees resources
void GLFWUtil::Exit()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}