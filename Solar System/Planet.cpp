#include "Planet.h"

Planet::Planet(GLuint& _program)
	: model(Model(_program)), mass(0), startingRadius(0)
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

GLfloat Planet::GetStartingRadius()
{
	return startingRadius;
}

void Planet::SetStartingRadius(GLfloat _startingRadius)
{
	startingRadius = _startingRadius;
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

	return normalize(vec3(thisMVP[3] - otherMVP[3]));
}