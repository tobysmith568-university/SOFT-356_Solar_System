#define STB_IMAGE_IMPLEMENTATION

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "GLFWUtil.h"
#include "GLEWUtil.h"
#include "MVPBuilder.h"
#include "Scene.h"
#include "ConfigUtil.h"
#include "InputManager.h"
#include "ConsoleUtil.h"
#include "ModelLoaderFactory.h"

using namespace std;

void RunScene(FileUtil& fileUtil, ConsoleUtil& consoleUtil, ConfigUtil& configUtil, InputManager& inputManager,
	ModelLoaderFactory& modelLoaderFactory, GLFWUtil& glfwUtil, GLEWUtil& glewUtil);

// Main method
int main(int argc, char** argv)
{
	try
	{
		FileUtil fileUtil = FileUtil();// Init dependencies
		ConsoleUtil consoleUtil = ConsoleUtil(fileUtil);
		ConfigUtil configUtil = ConfigUtil(fileUtil);
		InputManager inputManager = InputManager(configUtil);
		ModelLoaderFactory modelLoaderFactory = ModelLoaderFactory(fileUtil, consoleUtil);
		GLFWUtil glfwUtil = GLFWUtil(configUtil, inputManager);
		GLEWUtil glewUtil = GLEWUtil();

		RunScene(fileUtil, consoleUtil, configUtil, inputManager, modelLoaderFactory, glfwUtil, glewUtil);// Run a scene
	}
	catch (exception ex)
	{
		cout << "There was an unknown error:"
			<< endl
			<< endl
			<< ex.what();
	}
	catch (...)
	{
		cout << "There was an unknown error!";
	}
}

void RunScene(FileUtil& fileUtil, ConsoleUtil& consoleUtil, ConfigUtil& configUtil, InputManager& inputManager,
	ModelLoaderFactory& modelLoaderFactory, GLFWUtil& glfwUtil, GLEWUtil& glewUtil)
{
	consoleUtil.ClearConsole();

	glfwUtil.Init();

	glewUtil.Init();
	
	Scene scene = Scene(configUtil, fileUtil, inputManager, consoleUtil, modelLoaderFactory);

	bool wireframesOnly = configUtil.GetBool(BoolSetting::UseWireframes);
	while (!glfwUtil.GetShouldClose())// Loop while the window has not been told to close
	{
		if (wireframesOnly)
		{
			glfwUtil.WireFrameOnly();
		}

		scene.Update();// Update the scene
		glfwUtil.Update();// Update the window
	}

	glfwUtil.Exit();
}