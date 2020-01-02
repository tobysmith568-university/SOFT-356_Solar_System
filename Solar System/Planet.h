#pragma once

#include "GL/glew.h"

#include "GLFW/glfw3.h"
#include <string>
#include "Model.h"

using namespace glm;

class PlanetMemento;

struct Planet
{
public:
	Planet(CameraUtil& _cameraUtil, GLuint& _program);

	void Update();
	PlanetMemento CreateMemento();
	void RestoreToMemento(PlanetMemento& memento);

	std::string GetName();
	void SetName(std::string _name);

	GLfloat GetMass();
	void SetMass(GLfloat _mass);

	GLfloat GetStartingDistance();
	void SetStartingDistance(GLfloat _startingDistance);

	GLfloat GetRadiusPercentage();
	void SetRadiusPercentage(GLfloat _radiusPercentage);

	glm::vec3 GetVelocity();
	void SetVelocity(glm::vec3 _velocity);

	Model& GetModel();

	GLdouble DistanceTo(Planet& otherPlanet);
	vec3 NormalizedVectorTo(Planet& otherPlanet);

private:
	friend class PlanetMemento;

	std::string name;
	GLfloat mass;
	GLfloat startingDistance;
	GLfloat radiusPercentage;

	glm::vec3 velocity;

	Model model;
};