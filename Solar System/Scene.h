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
	~Scene();

	void Update();

private:
	ConfigUtil configUtil;
	FileUtil fileUtil;
	InputManager& inputManager;
	ConsoleUtil consoleUtil;
	ModelLoaderFactory modelLoaderFactory;

	bool autoRotate;
	bool backfaceCull;

	Planet* sun;
	std::vector<Planet> planets;

	GLuint program;

	void SetGlobalState();
	void BindMovements();
	void BindBackgroundColours();
	float NormalizeColour(float colour);
	void CreateAndBindShaderProgram();
	void AddSun(GLfloat mass);
	void LoadPlanets();
};