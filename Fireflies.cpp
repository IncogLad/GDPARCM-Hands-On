#include "Fireflies.h"

Fireflies::Fireflies(std::string name, sf::Color color): ALightObject(name)
{
	this->name = name;
	this->color = color;
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
