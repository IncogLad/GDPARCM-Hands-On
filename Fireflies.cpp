#include "Fireflies.h"

Fireflies::Fireflies(std::string name): ALightObject(name)
{
	
}

Fireflies::~Fireflies()
{
}

void Fireflies::initialize()
{
	ALightObject::initialize();
}

void Fireflies::processInput(sf::Event event)
{
	ALightObject::processInput(event);
}

void Fireflies::update(sf::Time deltaTime)
{
	ALightObject::update(deltaTime);
}
