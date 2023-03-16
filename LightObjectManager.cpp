#include "LightObjectManager.h"
#include <cstddef>
#include <iostream>

LightObjectManager* LightObjectManager::sharedInstance = nullptr;

LightObjectManager* LightObjectManager::getInstance()
{
	if (sharedInstance == nullptr) sharedInstance = new LightObjectManager();

	return sharedInstance;
}

ALightObject* LightObjectManager::findObjectByName(ALightObject::String name)
{
	if (game_object_table_[name] != nullptr)
	{
		return game_object_table_[name];
	}
	else
	{
		std::cout << "ALightObject name not found!" << std::endl;
		return nullptr;
	}
}

LightObjectList LightObjectManager::getLightObjectList()
{
	return game_object_list_;
}

int LightObjectManager::getActiveObjectsCount()
{
	return static_cast<int>(game_object_list_.size());
}

void LightObjectManager::processInput(sf::Event event)
{
	for (int i = 0; i < this->game_object_list_.size(); i++) {
		if (this->game_object_list_[i] != nullptr) {
			this->game_object_list_[i]->processInput(event);
		}
	}
}

void LightObjectManager::update(sf::Time deltaTime)
{
	for (int i = 0; i < this->game_object_list_.size(); i++) {
		if (this->game_object_list_[i] != nullptr)
			this->game_object_list_[i]->update(deltaTime);
	}
}

void LightObjectManager::draw(sf::RenderWindow* window)
{
	for (int i = 0; i < this->game_object_list_.size(); i++) {
		if (this->game_object_list_[i] != nullptr)
			this->game_object_list_[i]->draw(window);
	}
}

void LightObjectManager::addObject(ALightObject* gameObject)
{
	game_object_table_[gameObject->getName()] = gameObject;
	game_object_list_.push_back(gameObject);

	game_object_table_[gameObject->getName()]->initialize();
}

void LightObjectManager::deleteObject(ALightObject* gameObject)
{
	this->game_object_table_.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < this->game_object_list_.size(); i++) {
		if (this->game_object_list_[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {

		this->game_object_list_.erase(this->game_object_list_.begin() + index);
		game_object_list_.shrink_to_fit();
	}

	delete gameObject;
}

void LightObjectManager::deleteObjectByName(ALightObject::String name)
{
	ALightObject* object = this->findObjectByName(name);

	if (object != nullptr) {
		this->deleteObject(object);
	}

}
