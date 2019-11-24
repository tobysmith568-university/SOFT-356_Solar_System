#pragma once

#include "GL/glew.h"
#include "FileUtil.h"

class ShaderProgramBuilder
{
public:
	ShaderProgramBuilder(FileUtil& _fileUtil);
	ShaderProgramBuilder& AddVertexShader(std::string fileLocation);
	ShaderProgramBuilder& AddFragmentShader(std::string fileLocation);
	GLuint* BuildAndUse();
private:
	GLuint program;
	FileUtil fileUtil;

	void AddShader(std::string fileLocation, int shaderType);
};