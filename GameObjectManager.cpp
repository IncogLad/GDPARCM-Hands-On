#include <stddef.h>
#include "GameObjectManager.h"
#include <iostream>

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager* GameObjectManager::getInstance()
{
	if (sharedInstance == nullptr) sharedInstance = new GameObjectManager();

	return sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(AGameObject::String name)
{
}

GameObjectList GameObjectManager::getAllObjects()
{
}

int GameObjectManager::activeObjects()
{
}

void GameObjectManager::processInput(sf::Event event)
{
}

void GameObjectManager::update(sf::Time deltaTime)
{
}

void GameObjectManager::draw(sf::RenderWindow* window)
{
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
}

void GameObjectManager::deleteObjectByName(AGameObject::String name)
{
}
