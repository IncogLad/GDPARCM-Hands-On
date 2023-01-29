#include "AGameObject.h"

#include <iostream>

AGameObject::AGameObject(String name)
{
	this->name = name;
}

AGameObject::~AGameObject()
{
	delete this->texture;
	delete this->sprite;
}

void AGameObject::initialize()
{
	//virtual
}

void AGameObject::processInput(sf::Event event)
{
	//virtual
}

void AGameObject::update(sf::Time deltaTime)
{
	//virtual
	//std::cout << this->name <<std::endl;
}

void AGameObject::draw(sf::RenderWindow* targetWindow)
{
	if (this->sprite != nullptr) {
		this->sprite->setPosition(this->posX, this->posY);
		this->sprite->setScale(this->scaleX, this->scaleY);
		targetWindow->draw(*this->sprite);
	}

}

AGameObject::String AGameObject::getName()
{
	return this->name;
}

void AGameObject::setPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;

	if (this->sprite != nullptr)
	{
		this->sprite->setPosition(this->posX, this->posY);
	}

}

void AGameObject::setScale(float x, float y)
{
	this->scaleX = x;
	this->scaleY = y;

	if (this->sprite != nullptr)
	{
		this->sprite->setScale(this->scaleX, this->scaleY);
	}

}

sf::FloatRect AGameObject::getLocalBounds()
{
	return this->sprite->getLocalBounds();
}

sf::Vector2f AGameObject::getPosition()
{
	return this->sprite->getPosition();
}

sf::Vector2f AGameObject::getScale()
{
	return this->sprite->getScale();
}
