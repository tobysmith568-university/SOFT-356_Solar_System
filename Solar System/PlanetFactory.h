#pragma once

#include "GL/glew.h"

#include "GLFW/glfw3.h"

#include "CameraUtil.h"
#include "ConfigUtil.h"
#include "FileUtil.h"
#include "Planet.h"

#include <vector>
#include <string>

class PlanetFactory
{
public:
	PlanetFactory(CameraUtil& _cameraUtil, ConfigUtil& _configUtil, FileUtil& _fileUtil);

	std::vector<Planet> CreateSolarSystem(GLuint& program);

private:
	CameraUtil cameraUtil;
	ConfigUtil configUtil;
	FileUtil fileUtil;

	void LoadSun(std::vector<Planet>& planets, GLfloat mass, GLuint& program);
	void GetPlanetFromLine(std::vector<Planet>& planets, std::string line, GLuint& program);
	void ParsePlanetKeyValuePair(Planet& planet, std::string& key, std::string& value);
};