#include "TextureDisplay.h"

#include <iostream>

#include "BaseWindow.h"
#include "GameObjectManager.h"
#include "IconObject.h"
#include "TextureManager.h"
#include "LoadingStatus.h"

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

	if (this->ticks >= 10.0f) {

		
		if (static_cast<int>(this->iconList.size()) < LoadingStatus::getInstance()->getMaxItemsAmount())
		{
			//TextureManager::getInstance()->loadSingleStreamAsset(static_cast<int>(this->iconList.size()), this);
			TextureManager::getInstance()->loadSingleStreamAsset(numDisplayed, this);
			numDisplayed++;

		}

		
		if (LoadingStatus::getInstance()->getLoadedItemsAmount() >= LoadingStatus::getInstance()->getMaxItemsAmount())
		{
			LoadingStatus::getInstance()->setLoadingStatus(true);
			LoadingStatus::getInstance()->finishedOnce = true;


			LoadingStatus::getInstance()->setMaxItems(10000);
		}
		
		this->ticks = 0.0f;
	}
	
}

void TextureDisplay::onFinishedExecution()
{
	guard.lock();

	spawnObject();
	
	guard.unlock();
}

void TextureDisplay::spawnObject()
{
	String objectName = "Image_" + std::to_string(this->iconList.size());
	auto* iconObj = new IconObject(objectName, static_cast<int>(this->iconList.size()));

	this->iconList.push_back(iconObj);

	//set position
	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	//int IMG_WIDTH = 45; int IMG_HEIGHT = 45;
	float x = this->columnGrid * IMG_WIDTH;
	float y = this->rowGrid * IMG_HEIGHT;
	iconObj->setPosition(x, y);
	//old pc values
	//iconObj->setScale(0.67, 0.67);

	//std::cout << "Set position: " << x << " " << y << std::endl;

	this->columnGrid++;
	if (this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}

	LoadingStatus::getInstance()->incrementItems();
	//GameObjectManager::getInstance()->addObject(iconObj);

}
