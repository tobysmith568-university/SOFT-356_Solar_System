#include "Planet.h"

Planet::Planet(GLuint& _program)
	: model(Model(_program)), mass(0), startingDistance(0), radiusPercentage(0), velocity(vec3(0.0f))
{
}

void Planet::Update()
{
	model.Update();
}

std::string Planet::GetName()
{
	return name;
}

void Planet::SetName(std::string _name)
{
	name = _name;
}

GLfloat Planet::GetMass()
{
	return mass;
}

void Planet::SetMass(GLfloat _mass)
{
	mass = _mass;
}

GLfloat Planet::GetStartingDistance()
{
	return startingDistance;
}

void Planet::SetStartingDistance(GLfloat _startingDistance)
{
	startingDistance = _startingDistance;
}

GLfloat Planet::GetRadiusPercentage()
{
	return radiusPercentage;
}

void Planet::SetRadiusPercentage(GLfloat _radiusPercentage)
{
	radiusPercentage = _radiusPercentage;
}

glm::vec3 Planet::GetVelocity()
{
	return velocity;
}

void Planet::SetVelocity(glm::vec3 _velocity)
{
	velocity = _velocity;
}

Model& Planet::GetModel()
{
	return model;
}

GLdouble Planet::DistanceTo(Planet& otherPlanet)
{
	mat4 thisMVP = GetModel().GetMVP();
	mat4 otherMVP = otherPlanet.GetModel().GetMVP();

	return length(thisMVP[3] - otherMVP[3]);
}

vec3 Planet::NormalizedVectorTo(Planet& otherPlanet)
{
	mat4 thisMVP = GetModel().GetMVP();
	mat4 otherMVP = otherPlanet.GetModel().GetMVP();

	return normalize(vec3(otherMVP[3] - thisMVP[3]));
}