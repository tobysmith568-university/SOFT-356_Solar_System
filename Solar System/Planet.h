#pragma once

#include "GL/glew.h"

#include "GLFW/glfw3.h"
#include <string>
#include "Model.h"

struct Planet
{
public:
	Planet(GLuint& _program);

	void Update();

	std::string GetName();
	void SetName(std::string _name);

	GLfloat GetMass();
	void SetMass(GLfloat _mass);

	GLfloat GetStartingRadius();
	void SetStartingRadius(GLfloat _startingRadius);

	Model& GetModel();

private:
	std::string name;
	GLfloat mass;
	GLfloat startingRadius;

	Model model;
};

