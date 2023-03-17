#pragma once
#include "ALightObject.h"
#include "BaseWindow.h"

class CenterLoadingLight : public ALightObject
{
public:
	CenterLoadingLight(std::string name);
	~CenterLoadingLight();

	void initialize() override;
	void processInput(sf::Event event)override;
	void update(sf::Time deltaTime)override;

private:
	const float SPEED_MULTIPLIER = 2.0f;

	const float initial_Range = 10.f;
	float actual_current_Range = 0;
	float anim_current_Range = 0;
	const float max_Range = BaseWindow::WINDOW_WIDTH;

	//for glowing animating
	bool glowSmall = true;
	bool glowBig = false;
	float lowerlimit = actual_current_Range - 8.f;
	float upperlimit = actual_current_Range + 10.f;


	void animatingLightRange(sf::Time deltaTime);

};
