#include "PlanetMemento.h"

PlanetMemento::PlanetMemento(Planet* planet)
	:
	name(planet->name),
	mass(planet->mass),
	startingDistance(planet->startingDistance),
	radiusPercentage(planet->radiusPercentage),

	velocity(planet->velocity),
	hasInitialForceApplied(planet->hasInitialForceApplied),

	mvpBuilder(planet->model.GetMVPBuilder())
{
}