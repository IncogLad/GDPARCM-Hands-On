#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include "ALightObject.h"
#include "Candle/LightingArea.hpp"

typedef std::unordered_map<std::string, ALightObject*> LightObjectTable;
typedef std::vector<ALightObject*> LightObjectList;

class LightObjectManager
{
public:
	static LightObjectManager* getInstance();

	ALightObject* findObjectByName(ALightObject::String name);
	LightObjectList getLightObjectList();

	int getActiveObjectsCount();

	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void draw(sf::RenderWindow* window);
	void drawOnFog(candle::LightingArea* fog);
	
	void addObject(ALightObject* gameObject);

	void deleteObject(ALightObject* gameObject);
	void deleteObjectByName(ALightObject::String name);

private:
	LightObjectManager() {};
	LightObjectManager(LightObjectManager const&) {};             // copy constructor is private
	LightObjectManager& operator=(LightObjectManager const&) {};  // assignment operator is private
	static LightObjectManager* sharedInstance;

	LightObjectTable game_object_table_;

	LightObjectList game_object_list_;
	LightObjectList ff_game_object_list_;
	
	
};
