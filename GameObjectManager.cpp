#include <cstddef>
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
	if (game_object_table_[name] != nullptr)
	{
		return game_object_table_[name];
	}
	else
	{
		std::cout << "AGameObject name not found!" << std::endl;
		return nullptr;
	}
}

GameObjectList GameObjectManager::getGameObjectList()
{
	return game_object_list_;
}

int GameObjectManager::getActiveObjectsCount()
{
	return static_cast<int>(game_object_list_.size());
}

void GameObjectManager::processInput(sf::Event event)
{
	for (int i = 0; i < this->game_object_list_.size(); i++) {
		if (this->game_object_list_[i]!= nullptr)
			this->game_object_list_[i]->processInput(event);
	}
	for (int i = 0; i < this->UI_game_object_list_.size(); i++) {
		if (this->UI_game_object_list_[i] != nullptr)
			this->UI_game_object_list_[i]->processInput(event);
	}
	for (int i = 0; i < this->BG_game_object_list_.size(); i++) {
		if (this->BG_game_object_list_[i] != nullptr)
			this->BG_game_object_list_[i]->processInput(event);
	}
}

void GameObjectManager::update(sf::Time deltaTime)
{
	for (int i = 0; i < this->game_object_list_.size(); i++) {
		if (this->game_object_list_[i] != nullptr)
			this->game_object_list_[i]->update(deltaTime);
	}
	for (int i = 0; i < this->UI_game_object_list_.size(); i++) {
		if (this->UI_game_object_list_[i] != nullptr)
			this->UI_game_object_list_[i]->update(deltaTime);
	}
	for (int i = 0; i < this->BG_game_object_list_.size(); i++) {
		if (this->BG_game_object_list_[i] != nullptr)
			this->BG_game_object_list_[i]->update(deltaTime);
	}
}

void GameObjectManager::draw(sf::RenderWindow* window)
{
	for (int i = 0; i < this->game_object_list_.size(); i++) {
		if (this->game_object_list_[i] != nullptr)
			this->game_object_list_[i]->draw(window);
	}
}

void GameObjectManager::draw_UI(sf::RenderWindow* window)
{
	for (int i = 0; i < this->UI_game_object_list_.size(); i++) {
		if (this->UI_game_object_list_[i] != nullptr)
			this->UI_game_object_list_[i]->draw(window);
	}
}

void GameObjectManager::draw_BG(sf::RenderWindow* window)
{
	for (int i = 0; i < this->BG_game_object_list_.size(); i++) {
		if (this->BG_game_object_list_[i] != nullptr)
			this->BG_game_object_list_[i]->draw(window);
	}
}

void GameObjectManager::addObject_UI(AGameObject* gameObject)
{
	this->guard.lock();

	game_object_table_[gameObject->getName()] = gameObject;
	UI_game_object_list_.push_back(gameObject);

	game_object_table_[gameObject->getName()]->initialize();

	this->guard.unlock();
}

void GameObjectManager::addObject_BG(AGameObject* gameObject)
{
	this->guard.lock();

	game_object_table_[gameObject->getName()] = gameObject;
	BG_game_object_list_.push_back(gameObject);

	game_object_table_[gameObject->getName()]->initialize();

	this->guard.unlock();
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	this->guard.lock();

	game_object_table_[gameObject->getName()] = gameObject;
	game_object_list_.push_back(gameObject);
	
	game_object_table_[gameObject->getName()]->initialize();

	this->guard.unlock();
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
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

void GameObjectManager::deleteObject_UI(AGameObject* gameObject)
{
	this->game_object_table_.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < this->UI_game_object_list_.size(); i++) {
		if (this->UI_game_object_list_[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {

		this->UI_game_object_list_.erase(this->UI_game_object_list_.begin() + index);
		UI_game_object_list_.shrink_to_fit();
	}

	delete gameObject;
}

void GameObjectManager::deleteObject_BG(AGameObject* gameObject)
{
	this->game_object_table_.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < this->BG_game_object_list_.size(); i++) {
		if (this->BG_game_object_list_[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {

		this->BG_game_object_list_.erase(this->BG_game_object_list_.begin() + index);
		BG_game_object_list_.shrink_to_fit();
	}

	delete gameObject;
}

void GameObjectManager::deleteObjectByName(AGameObject::String name)
{
	AGameObject* object = this->findObjectByName(name);

	if (object != nullptr) {
		this->deleteObject(object);
	}

}
