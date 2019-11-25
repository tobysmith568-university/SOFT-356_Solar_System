#pragma once

#include "GLFW/glfw3.h"
#include <string>

struct Planet
{
public:

	std::string GetName();
	void SetName(std::string _name);

	GLfloat GetMass();
	void SetMass(GLfloat _mass);

private:
	std::string name;
	GLfloat mass;
};

