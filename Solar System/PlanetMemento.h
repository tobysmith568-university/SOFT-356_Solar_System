#pragma once

#include "Planet.h"
#include "Model.h"

#include "GLFW/glfw3.h"

class PlanetMemento
{
public:
    PlanetMemento(Planet* planet);

private:
    friend struct Planet;

	std::string name;
	GLfloat mass;
	GLfloat startingDistance;
	GLfloat radiusPercentage;

	glm::vec3 velocity;

	bool hasInitialForceApplied;

	MVPBuilder mvpBuilder;
};