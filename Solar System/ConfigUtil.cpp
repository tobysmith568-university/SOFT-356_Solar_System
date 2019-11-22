#include "ConfigUtil.h"

using namespace std;

ConfigUtil::ConfigUtil(FileUtil& _fileUtils)
	: fileUtils(_fileUtils)
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

bool ConfigUtil::GetBool(BoolSetting boolSetting)
{
	string stringValue = config[GetBoolValue(boolSetting)];
	return stringValue == "1";
}

int ConfigUtil::GetInt(IntSetting intSetting)
{
	string stringValue = config[GetIntValue(intSetting)];
	return stoi(stringValue);
}

float ConfigUtil::GetFloat(FloatSetting floatSetting)
{
	string stringValue = config[GetFloatValue(floatSetting)];
	return stof(stringValue);
}

std::string ConfigUtil::GetString(StringSetting stringSetting)
{
	return config[GetStringValue(stringSetting)];
}

int ConfigUtil::GetKeyBinding(KeyBinding keybinding)
{
	string stringValue = config[GetKeyBindingValue(keybinding)];
	return stoi(stringValue);
}

void ConfigUtil::GetConfigData()
{
	config = map<string, string>();

	vector<string> configFile = fileUtils.ReadFileAsLines(configFileLocation);

	for (int i = 0; i < configFile.size(); i++)
	{
		string line = configFile.at(i);

		string key = "";
		string value = "";
		bool atEquals = false;

		for (char& c : line)
		{
			if (c == '=' && !atEquals)
			{
				atEquals = true;
				continue;
			}

			if (!atEquals)
			{
				key += c;
				continue;
			}

			value += c;
		}

		config[key] = value;
	}
}

void ConfigUtil::CreateDefaultConfigData()
{
	if (!fileUtils.DoesFileExist(configFileLocation))
	{
		fileUtils.SaveFile(defaultFileData, configFileLocation);
	}

	fileUtils.EnsureFolderExists(defaultShaderFolder);

	if (!fileUtils.DoesFileExist(vertexShaderLocation))
	{
		fileUtils.SaveFile(defaultVertexShaderData, vertexShaderLocation);
	}

	if (!fileUtils.DoesFileExist(fragmentShaderLocation))
	{
		fileUtils.SaveFile(defaultFragmentShaderData, fragmentShaderLocation);
	}
}

std::string ConfigUtil::GetBoolValue(BoolSetting boolSetting)
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

std::string ConfigUtil::GetIntValue(IntSetting intSetting)
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

std::string ConfigUtil::GetFloatValue(FloatSetting floatSetting)
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

std::string ConfigUtil::GetStringValue(StringSetting stringSetting)
{
	switch (stringSetting)
	{
	case StringSetting::WindowTitle:
		return "windowTitle";
	case StringSetting::VertexShader:
		return "vertexShader";
	case StringSetting::FragmentShader:
		return "fragmentShader";
	default:
		return "";
	}
}

std::string ConfigUtil::GetKeyBindingValue(KeyBinding keybinding)
{
	switch (keybinding)
	{
	case KeyBinding::Quit:
		return "KeyBinding_Quit";

	default:
		return "";
	}
}