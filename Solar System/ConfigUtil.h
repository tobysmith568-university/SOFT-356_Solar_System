#pragma once

#include "GL/glew.h"

#include "FileUtil.h"
#include <map> 
#include <iterator>
#include <string>

enum class BoolSetting
{
	UseWireframes,
	BackfaceCull,
	FullScreenOnStartup,
	StartOnFPSStyle,
	PhysicsEnabled
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
	MovementSpeed
};

enum class StringSetting
{
	WindowTitle,
	VertexShader,
	FragmentShader,
	PlanetFile
};

enum class KeyBinding
{
	MoveForward,
	MoveBackward,
	MoveLeft,
	MoveRight,
	Quit,
	ToggleFPSStyle,
	TogglePhysicsEnabled
};

class ConfigUtil
{
public:
	ConfigUtil(FileUtil& _fileUtil);
	bool GetBool(BoolSetting boolSetting);
	int GetInt(IntSetting intSetting);
	float GetFloat(FloatSetting floatSetting);
	std::string GetString(StringSetting stringSetting);
	int GetKeyBinding(KeyBinding keybinding);

private:
	std::map<std::string, std::string> config;
	FileUtil& fileUtil;

	void GetConfigData();
	void CreateDefaultConfigData();

	std::string GetBoolValue(BoolSetting boolSetting);
	std::string GetIntValue(IntSetting intSetting);
	std::string GetFloatValue(FloatSetting floatSetting);
	std::string GetStringValue(StringSetting stringSetting);
	std::string GetKeyBindingValue(KeyBinding keybinding);

	std::string configFileLocation = "config.dat";
	std::string defaultConfigFileData =
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
\n\
vertexShader=media/shader.vert\n\
fragmentShader=media/shader.frag\n\
\n\
planetFile=planets.dat\n\
\n\
\n\
\n\
KeyBinding_Quit=256";

	std::string shaderFolder = "shaders";
	std::string vertexShaderLocation = "shaders/shader.vert";
	std::string defaultVertexShaderData =
"#version 400 core\n\
\n\
layout(location = 0) in vec3 vPosition;\n\
layout(location = 1) in vec4 vColour;\n\
layout(location = 2) in vec2 aTexCoord;\n\
uniform mat4 mvp;\n\
	\n\
out vec4 fragColour;\n\
out vec2 TexCoord;\n\
void\n\
	main()\n\
{\n\
	gl_Position = mvp * vec4(vPosition, 1.0);\n\
	fragColour = vColour;\n\
	TexCoord = aTexCoord;\n\
}\n\
";

	std::string fragmentShaderLocation = "shaders/shader.frag";
	std::string defaultFragmentShaderData =
"#version 450 core\n\
\n\
out vec4 fColor;\n\
in vec4 fragColour;\n\
in vec2 TexCoord;\n\
\n\
uniform sampler2D ourTexture;\n\
\n\
void main()\n\
{\n\
	fColor = texture(ourTexture, TexCoord) * fragColour;\n\
}\n\
";
};