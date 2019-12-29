#pragma once

#include "GL/glew.h"
#include "GLFWUtil.h"
#include "MVPBuilder.h"
#include "ConfigUtil.h"
#include "Model.h"
#include "InputManager.h"
#include "Texture.h"
#include "ConsoleUtil.h"
#include "ModelLoaderFactory.h"

#include <glm/glm.hpp>
#include <vector>

class Scene
{
public:
	Scene(ConfigUtil& _configUtil, FileUtil& _fileUtil, InputManager& _inputManager,
		ConsoleUtil& _consoleUtil, ModelLoaderFactory& _modelLoaderFactory);

	void Update();

private:
	//const GLdouble GRAVITY = 0.000000000066742;
	const GLdouble GRAVITY = -0.000000001066742;

	ConfigUtil configUtil;
	FileUtil fileUtil;
	InputManager& inputManager;
	ConsoleUtil consoleUtil;
	ModelLoaderFactory modelLoaderFactory;

	bool backfaceCull;

	std::vector<Planet> planets;

	GLuint program;

	void UpdatePositions();
	void SetGlobalState();
	void BindMovements();
	void BindBackgroundColours();
	float NormalizeColour(float colour);
	void CreateAndBindShaderProgram();
	void LoadPlanets();
	void LoadPlanet(Planet& planet, std::string modelPath);
};