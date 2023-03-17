#pragma once
#include "AGameObject.h"
#include <vector> 
#include "Candle/RadialLight.hpp"
#include "ALightObject.h"

class Fireflies : public ALightObject
{
public:
	Fireflies(std::string name, sf::Color color);
	~Fireflies();

	void initialize() override;
	void processInput(sf::Event event)override;
	void update(sf::Time deltaTime)override;

private:

	std::vector<candle::RadialLight*>* fireflyBunch;
	const float SPEED_MULTIPLIER = 3000.0f;

	sf::Color color = sf::Color::White;
};

