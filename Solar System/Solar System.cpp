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
#include "CameraUtil.h"
#include "InputManager.h"
#include "ConsoleUtil.h"
#include "ModelLoaderFactory.h"
#include "PlanetFactory.h"
#include "TimeUtil.h"

using namespace std;

void RunScene(FileUtil& fileUtil, ConsoleUtil& consoleUtil, ConfigUtil& configUtil, InputManager& inputManager,
	ModelLoaderFactory& modelLoaderFactory, PlanetFactory& planetFactory, GLFWUtil& glfwUtil, GLEWUtil& glewUtil, TimeUtil& timeUtil);

// Main method
int main(int argc, char** argv)
{
	try
	{
		FileUtil fileUtil = FileUtil();// Init dependencies
		TimeUtil timeUtil = TimeUtil();
		ConsoleUtil consoleUtil = ConsoleUtil(fileUtil);
		ConfigUtil configUtil = ConfigUtil(fileUtil);
		InputManager inputManager = InputManager(configUtil);
		CameraUtil cameraUtil = CameraUtil(inputManager, timeUtil);
		PlanetFactory planetFactory = PlanetFactory(cameraUtil, configUtil, fileUtil);
		ModelLoaderFactory modelLoaderFactory = ModelLoaderFactory(fileUtil, consoleUtil);
		GLFWUtil glfwUtil = GLFWUtil(configUtil, inputManager);
		GLEWUtil glewUtil = GLEWUtil();

		RunScene(fileUtil, consoleUtil, configUtil, inputManager, modelLoaderFactory, planetFactory, glfwUtil, glewUtil, timeUtil);// Run a scene
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
	ModelLoaderFactory& modelLoaderFactory, PlanetFactory& planetFactory, GLFWUtil& glfwUtil, GLEWUtil& glewUtil, TimeUtil& timeUtil)
{
	consoleUtil.ClearConsole();

	glfwUtil.Init();

	glewUtil.Init();
	
	Scene scene = Scene(configUtil, fileUtil, inputManager, consoleUtil, modelLoaderFactory, planetFactory, timeUtil);

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