#include "TextureDisplay.h"

#include <iostream>

#include "BaseWindow.h"
#include "GameObjectManager.h"
#include "IconObject.h"
#include "TextureManager.h"

TextureDisplay::TextureDisplay(): AGameObject("TEXTURE_DISPLAY")
{

}

void TextureDisplay::initialize()
{
	AGameObject::initialize();
}

void TextureDisplay::processInput(sf::Event event)
{
	AGameObject::processInput(event);
}

void TextureDisplay::update(sf::Time deltaTime)
{
	AGameObject::update(deltaTime);
	this->ticks += BaseWindow::TIME_PER_FRAME.asMilliseconds();

	if (this->ticks >= 200.0f) {
		if (static_cast<int>(this->iconList.size()) < TextureManager::getInstance()->streamingAssetCount)
		{
			TextureManager::getInstance()->loadSingleStreamAsset(static_cast<int>(this->iconList.size()));
			spawnObject();
		}
		this->ticks = 0.0f;
	}
	
}

void TextureDisplay::spawnObject()
{
	String objectName = "Icon_" + std::to_string(this->iconList.size());
	auto* iconObj = new IconObject(objectName, static_cast<int>(this->iconList.size()));

	this->iconList.push_back(iconObj);

	//set position
	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	float x = this->columnGrid * IMG_WIDTH;
	float y = this->rowGrid * IMG_HEIGHT;
	iconObj->setPosition(x, y);

	std::cout << "Set position: " << x << " " << y << std::endl;

	this->columnGrid++;
	if (this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}

	GameObjectManager::getInstance()->addObject(iconObj);

}
