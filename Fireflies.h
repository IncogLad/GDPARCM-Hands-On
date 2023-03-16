#pragma once
#include "AGameObject.h"
#include <vector> 
#include "Candle/RadialLight.hpp"


class Fireflies 
{
public:
	Fireflies(std::string name);
	~Fireflies();

	void initialize() override;
	void processInput(sf::Event event)override;
	void update(sf::Time deltaTime)override;

	std::vector<candle::RadialLight> fireflyBunch;

private:
	
	const float SPEED_MULTIPLIER = 3000.0f;

};

