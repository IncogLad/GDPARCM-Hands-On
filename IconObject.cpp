#include "IconObject.h"
#include <iostream>
#include "TextureManager.h"

IconObject::IconObject(String name, int textureIndex): AGameObject(name)
{
	this->textureIndex = textureIndex;
}

void IconObject::initialize()
{
	AGameObject::initialize();

	//std::cout << "Icon declared as " << this->getName() << "\n";

	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getStreamTextureFromList(this->textureIndex);
	this->sprite->setTexture(*texture);
}

void IconObject::processInput(sf::Event event)
{
	AGameObject::processInput(event);

}

void IconObject::update(sf::Time deltaTime)
{
	AGameObject::update(deltaTime);
	//std::cout << "Icon update for " << this->getName() << "\n";
}
