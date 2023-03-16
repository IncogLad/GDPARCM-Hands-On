#pragma once
#include "ALightObject.h"

class CenterLoadingLight : public ALightObject
{
public:
	CenterLoadingLight(std::string name);
	~CenterLoadingLight();

	void initialize() override;
	void processInput(sf::Event event)override;
	void update(sf::Time deltaTime)override;

private:
	const float SPEED_MULTIPLIER = 30.0f;
};
