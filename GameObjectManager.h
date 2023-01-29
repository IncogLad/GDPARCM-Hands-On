#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include "AGameObject.h"

typedef std::unordered_map<std::string, AGameObject*> GameObjectTable;
typedef std::vector<AGameObject*> GameObjectList;

class GameObjectManager
{
public:
	static GameObjectManager* getInstance();

	AGameObject* findObjectByName(AGameObject::String name);
	GameObjectList getGameObjectList();

	int getActiveObjectsCount();

	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* window);

	void addObject(AGameObject* gameObject);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(AGameObject::String name);

private:
	GameObjectManager() {};
	GameObjectManager(GameObjectManager const&) {};             // copy constructor is private
	GameObjectManager& operator=(GameObjectManager const&) {};  // assignment operator is private
	static GameObjectManager* sharedInstance;

	GameObjectTable game_object_table_;
	GameObjectList game_object_list_;

};