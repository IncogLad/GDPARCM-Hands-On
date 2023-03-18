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
			this->startDisplay = true;

			LoadingStatus::getInstance()->setMaxItems(10000);
		}
		
		this->ticks = 0.0f;
	}

	this->displayTicks += deltaTime.asSeconds();

	if (startDisplay)
	{

		if (this->displayTicks >= 0.1f) 
		{
			if (displayIndex < iconList.size()-1)
			{
				GameObjectManager::getInstance()->addObject(iconList[displayIndex]);
				sf::Vector2u textureSize = iconList[displayIndex]->getSprite()->getTexture()->getSize();

				iconList[displayIndex]->setScale(static_cast<float>(BaseWindow::WINDOW_WIDTH) / static_cast<float>(textureSize.x),
					static_cast<float>(BaseWindow::WINDOW_HEIGHT) / static_cast<float>(textureSize.y));
				displayIndex++;
			}
			else
			{
				BaseWindow::getInstance()->displayTitle = true;
				if (BaseWindow::getInstance()->fadeDone)
				{
					GameObjectManager::getInstance()->addObject(iconList[iconList.size() - 1]);
					sf::Vector2u textureSize = iconList[displayIndex]->getSprite()->getTexture()->getSize();

					iconList[displayIndex]->setScale(static_cast<float>(BaseWindow::WINDOW_WIDTH) / static_cast<float>(textureSize.x),
						static_cast<float>(BaseWindow::WINDOW_HEIGHT) / static_cast<float>(textureSize.y));
					startDisplay = false;
				}
				
			}
			this->displayTicks = 0;
			
		}

	}


	
}

void TextureDisplay::onFinishedExecution()
{
	guard.lock();
	loadedObject();
	guard.unlock();
}

void TextureDisplay::loadedObject()
{
	String objectName = "Image_" + std::to_string(this->iconList.size());
	auto* iconObj = new IconObject(objectName, static_cast<int>(this->iconList.size()));

	this->iconList.push_back(iconObj);

	LoadingStatus::getInstance()->incrementItems();

}
