#include "Planet.h"
#include "PlanetMemento.h"

Planet::Planet(CameraUtil& _cameraUtil, GLuint& _program)
	: model(_cameraUtil, _program), mass(0), startingDistance(0), radiusPercentage(0), initialForce(0), velocity(vec3(0.0f)), hasInitialForceApplied(false)
{
}

// Updates the model for the planet
void Planet::Update()
{
	model.Update();
}

// Returns a memento for the current state
PlanetMemento Planet::CreateMemento()
{
	return PlanetMemento(this);
}

// Restores this planet to a given memento
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

// Returns the name of the planet
std::string Planet::GetName()
{
	return name;
}

// Sets the name of the planet
void Planet::SetName(std::string _name)
{
	name = _name;
}

// Returns the mass of the planet
GLfloat Planet::GetMass()
{
	return mass;
}

// Sets the mass of the planet
void Planet::SetMass(GLfloat _mass)
{
	mass = _mass;
}

// Returns the starting distance of the planet
GLfloat Planet::GetStartingDistance()
{
	return startingDistance;
}

// Sets the starting distance of the planet
void Planet::SetStartingDistance(GLfloat _startingDistance)
{
	startingDistance = _startingDistance;
}

// Gets the radius of the planet
GLfloat Planet::GetRadiusPercentage()
{
	return radiusPercentage;
}

// Sets the radius of the planet
void Planet::SetRadiusPercentage(GLfloat _radiusPercentage)
{
	radiusPercentage = _radiusPercentage;
}

// Gets the initial force of the planet
GLfloat Planet::GetInitialForce()
{
	return initialForce;
}

// Sets the initial force of the planet
void Planet::SetInitialForce(GLfloat _initialForce)
{
	initialForce = _initialForce;
}

// Gets the velocity of the planet
glm::vec3 Planet::GetVelocity()
{
	return velocity;
}

// Sets the velocity of the planet
void Planet::SetVelocity(glm::vec3 _velocity)
{
	velocity = _velocity;
}

// Gets if the planet has had it's initial force applied to it
bool Planet::GetHasInitialForceApplied()
{
	return hasInitialForceApplied;
}

// Sets that the planet has had it's initial force applied to it
void Planet::SetInitialForceHasBeenApplied()
{
	hasInitialForceApplied = true;
}

// Gets the model of the planet
Model& Planet::GetModel()
{
	return model;
}

// Returns the distance from this planet to the given planet
GLdouble Planet::DistanceTo(Planet& otherPlanet)
{
	mat4 thisMVP = GetModel().GetMVPBuilder().GetTranslationMatrix();
	mat4 otherMVP = otherPlanet.GetModel().GetMVPBuilder().GetTranslationMatrix();

	return length(thisMVP[3] - otherMVP[3]);
}

// Returns a normalised vector between this planet and the given planet
vec3 Planet::NormalizedVectorTo(Planet& otherPlanet)
{
	mat4 thisMVP = GetModel().GetMVPBuilder().GetTranslationMatrix();
	mat4 otherMVP = otherPlanet.GetModel().GetMVPBuilder().GetTranslationMatrix();

	mat4 together = otherMVP - thisMVP;

	vec3 vector = vec3(together[3]);

	return normalize(vector);
}