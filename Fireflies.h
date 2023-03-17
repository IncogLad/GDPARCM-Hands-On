#pragma once
#include "AGameObject.h"
#include <vector> 
#include "Candle/RadialLight.hpp"
#include "ALightObject.h"

class Fireflies : public ALightObject
{
public:
	Fireflies(std::string name, sf::Color color, sf::Vector2f initPosition);
	~Fireflies();

	void initialize() override;
	void processInput(sf::Event event)override;
	void update(sf::Time deltaTime)override;


private:

	std::vector<candle::RadialLight*>* fireflyBunch;
	const float SPEED_MULTIPLIER = 200.0f;

	std::vector<std::vector<sf::Vector2f>> fireflyPatrolRoutes;
	std::vector<int> currentRoute = {0, 0 ,0, 0};

	sf::Color color = sf::Color::White;

	sf::Vector2f initPosition;
};

