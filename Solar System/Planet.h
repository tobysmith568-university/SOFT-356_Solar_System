#pragma once

#include "GL/glew.h"

#include "GLFW/glfw3.h"
#include <string>
#include "Model.h"

using namespace glm;

struct Planet
{
public:
	Planet(GLuint& _program);

	void Update();

	std::string GetName();
	void SetName(std::string _name);

	GLfloat GetMass();
	void SetMass(GLfloat _mass);

	GLfloat GetStartingDistance();
	void SetStartingDistance(GLfloat _startingDistance);

	Model& GetModel();

	GLdouble DistanceTo(Planet& otherPlanet);
	vec3 NormalizedVectorTo(Planet& otherPlanet);

private:
	std::string name;
	GLfloat mass;
	GLfloat startingDistance;

	Model model;
};