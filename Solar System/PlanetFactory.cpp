#include "PlanetFactory.h"

using namespace std;

PlanetFactory::PlanetFactory(CameraUtil& _cameraUtil, ConfigUtil& _configUtil, FileUtil& _fileUtil)
	: cameraUtil(_cameraUtil), configUtil(_configUtil), fileUtil(_fileUtil)
{
}

// Reads in the planet file and creates the objects for each one
std::vector<Planet> PlanetFactory::CreateSolarSystem(GLuint& program)
{
	string planetFileName = configUtil.GetString(StringSetting::PlanetFile);
	vector<string> planetFile = fileUtil.ReadFileAsLines(planetFileName);// Read in the planet data

	vector<Planet> planets = vector<Planet>();

	LoadBackground(planets, program);// Load in the background

	if (planetFile.size() > 0 && planetFile[0].size() > 0 && planetFile[0][0] != '#')// If the sun is not commented out
	{
		LoadSun(planets, stof(planetFile[0]), program);// Load the sun
	}

	if (planetFile.size() < 2)
	{
		return planets;
	}

	for (size_t i = 1; i < planetFile.size(); i++)// For every other line in the file
	{
		if (planetFile[i][0] != '#')
		{
			GetPlanetFromLine(planets, planetFile[i], program);// Load it in as a planet
		}
	}

	return planets;
}

// Loads in a background object
void PlanetFactory::LoadBackground(std::vector<Planet>& planets, GLuint& program)
{
	Planet background = Planet(cameraUtil, program);
	background.SetMass(0);
	background.SetName("The background");

	planets.push_back(background);
}

// Loads in a sun
void PlanetFactory::LoadSun(vector<Planet>& planets, GLfloat mass, GLuint& program)
{
	Planet sun = Planet(cameraUtil, program);
	sun.SetMass(mass);
	sun.SetName("The sun");

	planets.push_back(sun);
}

// Loads in a planet from a config line
void PlanetFactory::GetPlanetFromLine(vector<Planet>& planets, string line, GLuint& program)
{
	Planet newPlanet = Planet(cameraUtil, program);

	char* word;
	char* remaining = nullptr;
	word = strtok_s((char*)line.c_str(), " ", &remaining);// Get a 'word' from the line
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
			
			if (!foundEquals)
			{
				key += data[i];
				continue;
			}
			
			value += data[i];
		}

		if (key.size() > 0 && value.size() > 0)// If both a key and a value are found
		{
			ParsePlanetKeyValuePair(newPlanet, key, value);
		}

		word = strtok_s(remaining, " ", &remaining);
	}

	planets.push_back(newPlanet);
}

// Assigns a given key-value pair to a given planet
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

	if (key == "initialForce")
	{
		planet.SetInitialForce(stof(value));
		return;
	}
}
