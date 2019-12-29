#include "Scene.h"
#include "ShaderProgramBuilder.h"

#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <cstddef>
#include <iostream>
#include <functional>
#include "InvalidModelFileException.h"

using namespace std;

Scene::Scene(ConfigUtil& _configUtil, FileUtil& _fileUtil, InputManager& _inputManager,
	ConsoleUtil& _consoleUtil, ModelLoaderFactory& _modelLoaderFactory)
			: configUtil(_configUtil), fileUtil(_fileUtil), inputManager(_inputManager),
				consoleUtil(_consoleUtil), modelLoaderFactory(_modelLoaderFactory)
{
	backfaceCull = configUtil.GetBool(BoolSetting::BackfaceCull);// Get some config data
	autoRotate = configUtil.GetBool(BoolSetting::AutoRotate);
	try
	{
		SetGlobalState();
		BindMovements();
		CreateAndBindShaderProgram();
		BindBackgroundColours();

		configUtil.LoadPlanetData(program);
		LoadPlanets();
	}
	catch (exception ex)
	{
		consoleUtil.Print("\n\nThe scene could not be properly configured\n\n");
		consoleUtil.Print(ex.what());
		exit(-1);
	}
}

// To be run each game tick
void Scene::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clears the previous buffers

	for (size_t i = 0; i < planets.size(); i++)// For every planet
	{
		if (autoRotate)// Rotate it if necessary
		{
			planets[i].GetModel().GetMVPBuilder()
				.AddRotation(0.005f, 0.0f, 1.0f, 0.0f);
		}

		planets[i].Update();// Updated the model
	}
}

// Sets any config for OpenGL
void Scene::SetGlobalState()
{
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	if (backfaceCull)
	{
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}
}

// Creates lambda functions to be triggered on keypresses
void Scene::BindMovements()
{
}

// Binds the default clear colour for the scene
void Scene::BindBackgroundColours()
{
	float backgroundR = configUtil.GetFloat(FloatSetting::BackgroundR);// Read in the colour values from config
	float backgroundG = configUtil.GetFloat(FloatSetting::BackgroundG);
	float backgroundB = configUtil.GetFloat(FloatSetting::BackgroundB);
	float backgroundA = configUtil.GetFloat(FloatSetting::BackgroundA);

	backgroundR = NormalizeColour(backgroundR);// Set the colour values to be between 0 and 1
	backgroundG = NormalizeColour(backgroundG);
	backgroundB = NormalizeColour(backgroundB);
	backgroundA = NormalizeColour(backgroundA);

	glClearColor(backgroundR, backgroundG, backgroundB, backgroundA);// Set the background colours
}

// Normalizes an R, G, B, or A value
float Scene::NormalizeColour(float colour)
{
	if (colour > 1)
	{
		colour /= 255;
	}

	return colour;
}

// Creates a shader program, links it, and uses it
void Scene::CreateAndBindShaderProgram()
{
	string vertexShaderLocation = configUtil.GetString(StringSetting::VertexShader);// Get the shader loacations from config
	string fragmentShaderLocation = configUtil.GetString(StringSetting::FragmentShader);

	program = *ShaderProgramBuilder(fileUtil)// Create and use a shader program
		.AddVertexShader(vertexShaderLocation)
		.AddFragmentShader(fragmentShaderLocation)
		.BuildAndUse();
}

void Scene::LoadPlanets()
{
	string sunPath = "Models/sun.obj";
	string planetPath = "Models/planet.obj";

	planets = configUtil.GetPlanets();

	if (planets.size() > 0)
	{
		LoadPlanet(planets[0], sunPath);

		planets[0].GetModel().GetMVPBuilder()
			.AddScale(0.5f, 0.5f, 0.5f);
	}

	for (size_t i = 1; i < planets.size(); i++)
	{
		LoadPlanet(planets[i], planetPath);
	}
}

void Scene::LoadPlanet(Planet& planet, string modelPath)
{
	try
	{
		IModelLoader& ml = modelLoaderFactory.GetLoaderForFile(modelPath);// Gets the correct model loader based on the paths .extension

		ml.GetModel(planet.GetModel(), modelPath, program);// Loads in model data using that model loader
		planet.GetModel().Init();// Inits the OpenGL code within the model
	}
	catch (InvalidModelFileException & ex)
	{
		string message = ex.What();// Print to console any errors
		consoleUtil.Print(message);
	}
	catch (...)// Catch any additional errors
	{
		consoleUtil.Print("An unknown error occurred!");
	}
}
