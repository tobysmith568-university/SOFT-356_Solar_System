#include "Planet.h"
#include "PlanetMemento.h"

Planet::Planet(CameraUtil& _cameraUtil, GLuint& _program)
	: model(_cameraUtil, _program), mass(0), startingDistance(0), radiusPercentage(0), initialForce(0), velocity(vec3(0.0f)), hasInitialForceApplied(false)
{
}

void Planet::Update()
{
	model.Update();
}

PlanetMemento Planet::CreateMemento()
{
	return PlanetMemento(this);
}

void Planet::RestoreToMemento(PlanetMemento& memento)
{
	name = memento.name;
	mass = memento.mass;
	startingDistance = memento.startingDistance;
	radiusPercentage = memento.radiusPercentage;
	velocity = memento.velocity;
	hasInitialForceApplied = memento.hasInitialForceApplied;
	model.SetMVPBuilder(memento.mvpBuilder);
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

GLfloat Planet::GetInitialForce()
{
	return initialForce;
}

void Planet::SetInitialForce(GLfloat _initialForce)
{
	initialForce = _initialForce;
}

glm::vec3 Planet::GetVelocity()
{
	return velocity;
}

void Planet::SetVelocity(glm::vec3 _velocity)
{
	velocity = _velocity;
}

bool Planet::GetHasInitialForceApplied()
{
	return hasInitialForceApplied;
}

void Planet::SetInitialForceHasBeenApplied()
{
	hasInitialForceApplied = true;
}

Model& Planet::GetModel()
{
	return model;
}

GLdouble Planet::DistanceTo(Planet& otherPlanet)
{
	mat4 thisMVP = GetModel().GetMVPBuilder().GetTranslationMatrix();
	mat4 otherMVP = otherPlanet.GetModel().GetMVPBuilder().GetTranslationMatrix();

	return length(thisMVP[3] - otherMVP[3]);
}

vec3 Planet::NormalizedVectorTo(Planet& otherPlanet)
{
	mat4 thisMVP = GetModel().GetMVPBuilder().GetTranslationMatrix();
	mat4 otherMVP = otherPlanet.GetModel().GetMVPBuilder().GetTranslationMatrix();

	mat4 together = otherMVP - thisMVP;

	vec3 vector = vec3(together[3]);

	return normalize(vector);
}