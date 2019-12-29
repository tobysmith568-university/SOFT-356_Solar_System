#include "ConfigUtil.h"
#include <string>

using namespace std;

ConfigUtil::ConfigUtil(FileUtil& _fileUtil) : fileUtil(_fileUtil)
{
	try
	{
		GetConfigData();
	}
	catch (runtime_error ex)
	{
		CreateDefaultConfigData();
		GetConfigData();
	}
}

// Gets the value of a boolean setting from the config
bool ConfigUtil::GetBool(BoolSetting boolSetting)
{
	string stringValue = config[GetBoolValue(boolSetting)];
	return stringValue == "1";
}

// Gets the value of an int setting from the config
int ConfigUtil::GetInt(IntSetting intSetting)
{
	string stringValue = config[GetIntValue(intSetting)];
	return stoi(stringValue);
}

// Gets the value of a float setting from the config
float ConfigUtil::GetFloat(FloatSetting floatSetting)
{
	string stringValue = config[GetFloatValue(floatSetting)];
	return stof(stringValue);
}

// Gets the value of a string setting from the config
std::string ConfigUtil::GetString(StringSetting stringSetting)
{
	return config[GetStringValue(stringSetting)];
}

// Gets the value of a keybinding from the config
int ConfigUtil::GetKeyBinding(KeyBinding keybinding)
{
	string stringValue = config[GetKeyBindingValue(keybinding)];
	return stoi(stringValue);
}

std::vector<Planet> ConfigUtil::GetPlanets()
{
	return planets;
}

// Loads in the config data from file
void ConfigUtil::GetConfigData()
{
	config = map<string, string>();

	vector<string> configFile = fileUtil.ReadFileAsLines(configFileLocation);// Read in the config file into lines

	for (int i = 0; i < configFile.size(); i++)// For every line in the file
	{
		string line = configFile.at(i);

		string key = "";
		string value = "";
		bool atEquals = false;

		for (char& c : line)// For every character in the line
		{
			if (c == '=' && !atEquals)// If it is an equals
			{
				atEquals = true;// Declare that an equals has been found and continue the loop
				continue;
			}

			if (!atEquals)// Otherwise, either add it to the key
			{
				key += c;
				continue;
			}

			value += c;// Or the value
		}

		config[key] = value;
	}
}

void ConfigUtil::LoadPlanetData(GLuint& program)
{
	string planetFileName = GetString(StringSetting::PlanetFile);

	vector<string> planetFile = fileUtil.ReadFileAsLines(planetFileName);

	if (planetFile.size() > 0)
	{
		LoadSun(stof(planetFile[0]), program);
	}

	if (planetFile.size() < 2)
	{
		return;
	}

	for (size_t i = 1; i < planetFile.size(); i++)
	{
		GetPlanetFromLine(planetFile[i], program);
	}
}

void ConfigUtil::LoadSun(GLfloat mass, GLuint& program)
{
	Planet sun = Planet(program);
	sun.SetMass(mass);
	sun.SetName("The sun");

	planets.push_back(sun);
}

void ConfigUtil::GetPlanetFromLine(std::string line, GLuint& program)
{
	Planet newPlanet = Planet(program);

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

void ConfigUtil::ParsePlanetKeyValuePair(Planet& planet, std::string& key, std::string& value)
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
}

// Creates the config file with the default config
void ConfigUtil::CreateDefaultConfigData()
{
	if (!fileUtil.DoesFileExist(configFileLocation))
	{
		fileUtil.SaveFile(defaultConfigFileData, configFileLocation);
	}

	fileUtil.EnsureFolderExists(shaderFolder);

	if (!fileUtil.DoesFileExist(vertexShaderLocation))
	{
		fileUtil.SaveFile(defaultVertexShaderData, vertexShaderLocation);
	}

	if (!fileUtil.DoesFileExist(fragmentShaderLocation))
	{
		fileUtil.SaveFile(defaultFragmentShaderData, fragmentShaderLocation);
	}
}

// Returns the matching key in the config file for the passed in bool setting enum
string ConfigUtil::GetBoolValue(BoolSetting boolSetting)
{
	switch (boolSetting)
	{
	case BoolSetting::UseWireframes:
		return "useWireframes";
	case BoolSetting::BackfaceCull:
		return "backfaceCull";
	case BoolSetting::AutoRotate:
		return "autoRotate";
	case BoolSetting::FullScreenOnStartup:
		return "fullScreenOnStartup";
	default:
		return "";
	}
}

// Returns the matching key in the config file for the passed in int setting enum
string ConfigUtil::GetIntValue(IntSetting intSetting)
{
	switch (intSetting)
	{
	case IntSetting::WindowWidth:
		return "windowWidth";
	case IntSetting::WindowHeight:
		return "windowHeight";
	default:
		return "";
	}
}

// Returns the matching key in the config file for the passed in float setting enum
string ConfigUtil::GetFloatValue(FloatSetting floatSetting)
{
	switch (floatSetting)
	{
	case FloatSetting::BackgroundR:
		return "backgroundR";
	case FloatSetting::BackgroundG:
		return "backgroundG";
	case FloatSetting::BackgroundB:
		return "backgroundB";
	case FloatSetting::BackgroundA:
		return "backgroundA";
	default:
		return "";
	}
}

// Returns the matching key in the config file for the passed in string setting enum
string ConfigUtil::GetStringValue(StringSetting stringSetting)
{
	switch (stringSetting)
	{
	case StringSetting::WindowTitle:
		return "windowTitle";
	case StringSetting::VertexShader:
		return "vertexShader";
	case StringSetting::FragmentShader:
		return "fragmentShader";
	case StringSetting::PlanetFile:
		return "planetFile";
	default:
		return "";
	}
}

// Returns the matching key in the config file for the passed in key binding enum
string ConfigUtil::GetKeyBindingValue(KeyBinding keyBinding)
{
	switch (keyBinding)
	{
	case KeyBinding::Quit:
		return "KeyBinding_Quit";
	default:
		return "";
	}
}