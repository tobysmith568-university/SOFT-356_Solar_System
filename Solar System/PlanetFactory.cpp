#include "PlanetFactory.h"

using namespace std;

PlanetFactory::PlanetFactory(CameraUtil& _cameraUtil, ConfigUtil& _configUtil, FileUtil& _fileUtil)
	: cameraUtil(_cameraUtil), configUtil(_configUtil), fileUtil(_fileUtil)
{
}

std::vector<Planet> PlanetFactory::CreateSolarSystem(GLuint& program)
{
	string planetFileName = configUtil.GetString(StringSetting::PlanetFile);
	vector<string> planetFile = fileUtil.ReadFileAsLines(planetFileName);

	vector<Planet> planets = vector<Planet>();

	if (planetFile.size() > 0)
	{
		LoadSun(planets, stof(planetFile[0]), program);
	}

	if (planetFile.size() < 2)
	{
		return planets;
	}

	for (size_t i = 1; i < planetFile.size(); i++)
	{
		GetPlanetFromLine(planets, planetFile[i], program);
	}

	return planets;
}

void PlanetFactory::LoadSun(vector<Planet>& planets, GLfloat mass, GLuint& program)
{
	Planet sun = Planet(cameraUtil, program);
	sun.SetMass(mass);
	sun.SetName("The sun");

	planets.push_back(sun);
}

void PlanetFactory::GetPlanetFromLine(vector<Planet>& planets, string line, GLuint& program)
{
	Planet newPlanet = Planet(cameraUtil, program);

	char* word;
	char* remaining = nullptr;
	word = strtok_s((char*)line.c_str(), " ", &remaining);
	while (word != NULL)// While 'words' are still being found
	{
		string data = word;

		bool foundEquals = false;
		string key = "";
		string value = "";

		for (size_t i = 0; i < data.size(); i++)// Run through all the letters sorting them into the key or the value
		{
			if (!foundEquals && data[i] == '=')
			{
				foundEquals = true;
				continue;
			}
			else if (!foundEquals)
			{
				key += data[i];
			}
			else
			{
				value += data[i];
			}
		}

		if (key.size() > 0 && value.size() > 0)// If both a key and a value are found
		{
			ParsePlanetKeyValuePair(newPlanet, key, value);
		}

		word = strtok_s(remaining, " ", &remaining);
	}

	planets.push_back(newPlanet);
}

void PlanetFactory::ParsePlanetKeyValuePair(Planet& planet, std::string& key, std::string& value)
{
	if (key == "name")
	{
		planet.SetName(value);
		return;
	}

	if (key == "mass")
	{
		planet.SetMass(stof(value));
		return;
	}

	if (key == "distance")
	{
		planet.SetStartingDistance(stof(value));
		return;
	}

	if (key == "radius")
	{
		planet.SetRadiusPercentage(stof(value));
		return;
	}
}
