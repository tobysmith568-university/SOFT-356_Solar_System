#pragma once

#include "ConfigUtil.h"
#include "InputManager.h"
#include "ConsoleUtil.h"

#include <vector>
#include <GLFW\glfw3.h>

class Scene
{
public:
	Scene(ConfigUtil& _configUtil, FileUtil& _fileUtil, InputManager& _inputManager,
		ConsoleUtil& _consoleUtil, ModelLoaderFactory& _modelLoaderFactory);
	void Update();

private:
	ConfigUtil configUtil;
	FileUtil fileUtil;
	InputManager& inputManager;
	ConsoleUtil consoleUtil;
	ModelLoaderFactory modelLoaderFactory;

	bool autoRotate;
	bool backfaceCull;

	std::vector<Model> models;

	GLuint program;

	void SetGlobalState();
	void BindMovements();
	void BindBackgroundColours();
	float NormalizeColour(float colour);
	void CreateAndBindShaderProgram();
	void AddModel();
};

