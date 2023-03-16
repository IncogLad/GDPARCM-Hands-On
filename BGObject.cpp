#include "BGObject.h"
#include <iostream>
#include "BaseWindow.h"
#include "TextureManager.h"

BGObject::BGObject(std::string name) :AGameObject(name)
{
	
}

void BGObject::initialize()
{
	AGameObject::initialize();
	std::cout << "BGObject declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	this->texture = TextureManager::getInstance()->getFromTextureMap("InteractiveBG", 0);

	//texture->setRepeated(true);
	this->sprite->setTexture(*texture);
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();

	std::cout << BaseWindow::WINDOW_WIDTH / textureSize.x << " ";
	std::cout << BaseWindow::WINDOW_HEIGHT / textureSize.y << "\n";

	this->setScale(static_cast<float>(BaseWindow::WINDOW_WIDTH) / static_cast<float>(textureSize.x),
		static_cast<float>(BaseWindow::WINDOW_HEIGHT) / static_cast<float>(textureSize.y));
	

}

void BGObject::processInput(sf::Event event)
{
	AGameObject::processInput(event);
}

void BGObject::update(sf::Time deltaTime)
{
	AGameObject::update(deltaTime);
	//make BG scroll slowly
#ifdef OLD_BG
	sf::Vector2f position = this->getPosition();
	position.y += this->SPEED_MULTIPLIER * deltaTime.asSeconds();
	this->setPosition(position.x, position.y);

	sf::Vector2f localPos = this->sprite->getPosition();
	if (localPos.y * deltaTime.asSeconds() > 0) {
		//reset position
		this->setPosition(0, -BaseWindow::WINDOW_HEIGHT * 7);
	}
#endif


}
