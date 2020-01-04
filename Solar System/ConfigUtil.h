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
	PhysicsEnabled,
	LockSun
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
	MovementSpeed,
	MouseSpeed,
	ScrollSpeed,
	SunScale,
	BackgroundScale
};

enum class StringSetting
{
	WindowTitle,
	VertexShader,
	FragmentShader,
	PlanetFile,
	PlanetModel,
	SunModel,
	BackgroundModel
};

enum class KeyBinding
{
	MoveForward,
	MoveBackward,
	MoveLeft,
	MoveRight,
	Quit,
	Reset,
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
"# Window Setup\n\
# ============\n\
\n\
windowWidth=800\n\
windowHeight=600\n\
windowTitle=My Window\n\
fullScreenOnStartup=0\n\
\n\
backgroundR=0\n\
backgroundG=0\n\
backgroundB=0\n\
backgroundA=1\n\
\n\
\n\
\n\
# Shader Setup\n\
# ============\n\
\n\
vertexShader=Shaders/shader.vert\n\
fragmentShader=Shaders/shader.frag\n\
\n\
useWireframes=0\n\
backfaceCull=0\n\
\n\
\n\
\n\
# Planet and Model Setup\n\
# ======================\n\
\n\
planetFile=planets.dat\n\
\n\
#sunScale=0.01\n\
sunScale=0.4\n\
\n\
#sunModel=Models/sun.obj\n\
sunModel=Models/sunHP.obj\n\
\n\
#planetModel=Models/planet.obj\n\
planetModel=Models/planetHP.obj\n\
\n\
backgroundScale=33.0\n\
backgroundModel=Models/background.obj\n\
\n\
\n\
\n\
# Behaviour Setup\n\
# ===============\n\
\n\
physicsEnabled=0\n\
lockSun=1\n\
\n\
startOnFPSStyle=0\n\
movementSpeed=50\n\
mouseSpeed=-7\n\
scrollSpeed=5;\n\
\n\
\n\
# Keybindings\n\
# ===========\n\
\n\
KeyBinding_Quit=256\n\
KeyBinding_Reset=82\n\
KeyBinding_MoveForward=87\n\
KeyBinding_MoveBackward=83\n\
KeyBinding_MoveLeft=65\n\
KeyBinding_MoveRight=68\n\
KeyBinding_ToggleFPSStyle=84\n\
KeyBinding_TogglePhysicsEnabled=80";

	std::string shaderFolder = "Shaders";
	std::string vertexShaderLocation = "Shaders/shader.vert";
	std::string defaultVertexShaderData =
"#version 400 core\n\
\n\
layout( location = 0 ) in vec3 vPosition;\n\
layout( location = 1 ) in vec4 vColour;\n\
layout( location = 2 ) in vec3 vNormal;\n\
layout( location = 3 ) in vec2 aTexCoord;\n\
\n\
uniform vec3 lightPos; \n\
\n\
uniform vec4 ambient;\n\
uniform vec3 dLight; \n\
\n\
uniform vec3 sLight;\n\
uniform float sShine;\n\
\n\
uniform mat4 mv_matrix; \n\
uniform mat4 p_matrix;\n\
\n\
out vec4 fragColour;\n\
out vec2 TexCoord;\n\
\n\
void\n\
main()\n\
{\n\
	// view-space coordinate\n\
	vec4 P = mv_matrix * vec4(vPosition,1.0);\n\
	// calculate normal in view-space\n\
	vec3 N = mat3(mv_matrix) * vNormal; \n\
	// calcuate light vector in view space\n\
	vec3 L = lightPos - P.xyz;\n\
	// calc the view vector\n\
	vec3 V = -P.xyz;\n\
	\n\
	//Normalise\n\
	N = normalize(N);\n\
	L = normalize(L);\n\
	V = normalize(V);\n\
\n\
	// calc the reflection on the plane for the normal\n\
	vec3 R = reflect(-L,N);\n\
\n\
	// added specular and diffuse contributions to the colour \n\
	vec3 diffuse = max(0.0, dot(N,L)) * dLight;\n\
	vec3 specular = pow(max(dot(R,V), 0.0), sShine) * sLight;\n\
\n\
	fragColour =  (ambient + vec4(diffuse,1.0) + vec4(specular,1.0) ) * vColour;\n\
\n\
	gl_Position = p_matrix * P;\n\
	TexCoord = aTexCoord; \n\
}\n\
\n\
";

	std::string fragmentShaderLocation = "Shaders/shader.frag";
	std::string defaultFragmentShaderData =
"#version 450 core\n\
\n\
out vec4 fColor;\n\
in vec4 fragColour;\n\
in vec2 TexCoord; \n\
\n\
uniform sampler2D ourTexture;\n\
\n\
void main()\n\
{\n\
	fColor = texture(ourTexture, TexCoord) * fragColour;\n\
}\n\
\n\
";

	std::string planetFileLocation = "planets.dat";
	std::string defaultPlanetData =
"5000\n\
name=earth mass=180 distance=1 radius=0.2 initialForce=0.09\n\
";
};