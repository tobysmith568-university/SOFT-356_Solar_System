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
	ConsoleUtil& _consoleUtil, ModelLoaderFactory& _modelLoaderFactory, PlanetFactory& _planetFactory, TimeUtil& _timeUtil, CameraUtil& _cameraUtil)
			: configUtil(_configUtil), fileUtil(_fileUtil), inputManager(_inputManager),
				consoleUtil(_consoleUtil), modelLoaderFactory(_modelLoaderFactory), planetFactory(_planetFactory), timeUtil(_timeUtil), cameraUtil(_cameraUtil)
{
	backfaceCull = configUtil.GetBool(BoolSetting::BackfaceCull);// Get some config data
	physicsEnabled = configUtil.GetBool(BoolSetting::PhysicsEnabled);
	lockSun = configUtil.GetBool(BoolSetting::LockSun);

	try
	{
		CreateAndBindShaderProgram();
		SetGlobalState();
		BindMovements();
		BindBackgroundColours();
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
	timeUtil.Update();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clears the previous buffers
	
	if (physicsEnabled)
	{
		UpdatePositions();
	}

	for (size_t i = 0; i < planets.size(); i++)// For every planet
	{
		planets[i].Update();// Updated the model
	}
}

void Scene::UpdatePositions()
{
	for (size_t i = 1; i < planets.size(); i++)
	{
		if (lockSun && i == 1)
		{
			continue;
		}

		Planet* planet = &planets[i];

		for (size_t ii = 1; ii < planets.size(); ii++)
		{
			Planet* otherPlanet = &planets[ii];

			if (planet == otherPlanet)
			{
				continue;
			}

			GLdouble planetaryDistance = planet->DistanceTo(*otherPlanet);
			GLdouble planetaryDistanceSquared = planetaryDistance * planetaryDistance;
			GLdouble planet1Mass = (GLdouble)planet->GetMass();
			GLdouble planet2Mass = (GLdouble)otherPlanet->GetMass();

			if (planetaryDistance < (GLdouble)planet->GetRadiusPercentage() + (GLdouble)otherPlanet->GetRadiusPercentage())
			{
				continue;
			}

			GLdouble value = (planet1Mass * planet2Mass) / planetaryDistanceSquared;
			if (value < numeric_limits<GLdouble>::epsilon() || value == numeric_limits<GLdouble>::infinity())
			{
				continue;
			}

			GLdouble force = GRAVITY * value;

			vec3 vector = planet->NormalizedVectorTo(*otherPlanet);

			vec3 forceVector = vector * (GLfloat)force;

			if (!planet->GetHasInitialForceApplied())
			{
				forceVector += vec3(0.0f, 0.0f, planet->GetInitialForce());
				planet->SetInitialForceHasBeenApplied();
			}

			vec3 acceleration = forceVector / planet->GetMass();

			vec3 velocity = planet->GetVelocity() + acceleration;
			planet->SetVelocity(velocity);

			planet->GetModel().GetMVPBuilder()
				.AddTranslation(velocity.x, velocity.y, velocity.z);
		}
	}
}

// Sets any config for OpenGL
void Scene::SetGlobalState()
{
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	float vAmbientLight[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, vAmbientLight);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_AMBIENT, GL_SHININESS, vAmbientLight);

	if (backfaceCull)
	{
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}

	// Setting up the light
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, -3.0f);
	GLuint dLightPosLoc = glGetUniformLocation(program, "lightPos");
	glUniform3fv(dLightPosLoc, 1, glm::value_ptr(lightPos));
}

// Creates lambda functions to be triggered on keypresses
void Scene::BindMovements()
{
	inputManager.RegisterKeyRepeat(KeyBinding::TogglePhysicsEnabled, [&]()
		{
			physicsEnabled = !physicsEnabled;
		});
	inputManager.RegisterKeyRepeat(KeyBinding::Reset, [&]()
		{
			for (size_t i = 0; i < planets.size(); i++)
			{
				planets[i].RestoreToMemento(planetMementos[i]);
			}
		});
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
	string backgroundPath = configUtil.GetString(StringSetting::BackgroundModel);
	string sunPath = configUtil.GetString(StringSetting::SunModel);
	string planetPath = configUtil.GetString(StringSetting::PlanetModel);
	GLfloat backgroundScale = configUtil.GetFloat(FloatSetting::BackgroundScale);
	GLfloat sunScale = configUtil.GetFloat(FloatSetting::SunScale);

	planets = planetFactory.CreateSolarSystem(program);

	if (planets.size() == 0)
	{
		return;
	}

	LoadPlanet(planets[0], backgroundPath);

	planets[0].GetModel().GetMVPBuilder()
		.AddScale(backgroundScale, backgroundScale, backgroundScale);

	planetMementos.push_back(planets[0].CreateMemento());

	if (planets.size() == 1)
	{
		return;
	}

	LoadPlanet(planets[1], sunPath);

	planets[1].GetModel().GetMVPBuilder()
		.AddScale(sunScale, sunScale, sunScale);

	planetMementos.push_back(planets[1].CreateMemento());

	for (size_t i = 2; i < planets.size(); i++)
	{
		LoadPlanet(planets[i], planetPath);

		GLfloat radiusScale = planets[i].GetRadiusPercentage();

		planets[i].GetModel().GetMVPBuilder()
			.AddScale(sunScale, sunScale, sunScale)
			.AddScale(radiusScale, radiusScale, radiusScale)
			.AddTranslation(planets[i].GetStartingDistance(), 0, 0);

		planetMementos.push_back(planets[i].CreateMemento());
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
