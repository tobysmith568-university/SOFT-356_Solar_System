#include "ConfigUtil.h"
#include <string>

using namespace std;


ConfigUtil::ConfigUtil(FileUtil& _fileUtil)
	: fileUtil(_fileUtil)
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

// Loads in the config data from file
void ConfigUtil::GetConfigData()
{
	config = map<string, string>();

	vector<string> configFile = fileUtil.ReadFileAsLines(configFileLocation);// Read in the config file into lines

	for (int i = 0; i < configFile.size(); i++)// For every line in the file
	{
		string line = configFile.at(i);

		if (line.length() == 0 || line[0] == '#')
		{
			continue;
		}

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
	case BoolSetting::FullScreenOnStartup:
		return "fullScreenOnStartup";
	case BoolSetting::StartOnFPSStyle:
		return "startOnFPSStyle";
	case BoolSetting::PhysicsEnabled:
		return "physicsEnabled";
	case BoolSetting::LockSun:
		return "lockSun";
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
	case FloatSetting::MovementSpeed:
		return "movementSpeed";
	case FloatSetting::MouseSpeed:
		return "mouseSpeed";
	case FloatSetting::ScrollSpeed:
		return "scrollSpeed";
	case FloatSetting::SunScale:
		return "sunScale";
	case FloatSetting::BackgroundScale:
		return "backgroundScale";
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
	case StringSetting::PlanetModel:
		return "planetModel";
	case StringSetting::SunModel:
		return "sunModel";
	case StringSetting::BackgroundModel:
		return "backgroundModel";
	default:
		return "";
	}
}

// Returns the matching key in the config file for the passed in key binding enum
string ConfigUtil::GetKeyBindingValue(KeyBinding keyBinding)
{
	switch (keyBinding)
	{
	case KeyBinding::MoveForward:
		return "KeyBinding_MoveForward";
	case KeyBinding::MoveBackward:
		return "KeyBinding_MoveBackward";
	case KeyBinding::MoveLeft:
		return "KeyBinding_MoveLeft";
	case KeyBinding::MoveRight:
		return "KeyBinding_MoveRight";
	case KeyBinding::Quit:
		return "KeyBinding_Quit";
	case KeyBinding::Reset:
		return "KeyBinding_Reset";
	case KeyBinding::ToggleFPSStyle:
		return "KeyBinding_ToggleFPSStyle";
	case KeyBinding::TogglePhysicsEnabled:
		return "KeyBinding_TogglePhysicsEnabled";
	default:
		return "";
	}
}