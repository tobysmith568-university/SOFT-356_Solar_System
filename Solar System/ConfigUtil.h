#pragma once

#include "FileUtil.h"

#include <map>
#include <string>
#include <stdexcept>
#include <iostream>

enum class BoolSetting
{
	UseWireframes,
	BackfaceCull,
	AutoRotate,
	FullScreenOnStartup
};

enum class IntSetting
{
	WindowWidth,
	WindowHeight
};

enum class FloatSetting
{
	BackgroundR,
	BackgroundG,
	BackgroundB,
	BackgroundA,
};

enum class StringSetting
{
	WindowTitle,
	VertexShader,
	FragmentShader
};

enum class KeyBinding
{
	Quit
};

class ConfigUtil
{
public:
	ConfigUtil(FileUtil& _fileUtils);
	bool GetBool(BoolSetting boolSetting);
	int GetInt(IntSetting intSetting);
	float GetFloat(FloatSetting floatSetting);
	std::string GetString(StringSetting stringSetting);
	int GetKeyBinding(KeyBinding keybinding);

private:
	std::map<std::string, std::string> config;
	FileUtil& fileUtils;

	void GetConfigData();
	void CreateDefaultConfigData();

	std::string GetBoolValue(BoolSetting boolSetting);
	std::string GetIntValue(IntSetting intSetting);
	std::string GetFloatValue(FloatSetting floatSetting);
	std::string GetStringValue(StringSetting stringSetting);
	std::string GetKeyBindingValue(KeyBinding keybinding);

	std::string configFileLocation = "config.dat";
	std::string defaultFileData =
		"windowWidth=800\n\
windowHeight=600\n\
windowTitle=My Window\n\
fullScreenOnStartup=0\n\
\n\
backgroundR=127\n\
backgroundG=202\n\
backgroundB=240\n\
backgroundA=1\n\
\n\
useWireframes=0\n\
backfaceCull=0\n\
autoRotate=0\n\
\n\
vertexShader=shaders/shader.vert\n\
fragmentShader=shaders/shader.frag\n\
\n\
\n\
\n\
KeyBinding_Quit=256";

	std::string defaultShaderFolder = "shaders";

	std::string vertexShaderLocation = "shaders/shader.vert";
	std::string defaultVertexShaderData = "";

	std::string fragmentShaderLocation = "shaders/shader.frag";
	std::string defaultFragmentShaderData = "";
};