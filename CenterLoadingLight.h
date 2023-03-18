#pragma once
#include "ALightObject.h"
#include "BaseWindow.h"

class CenterLoadingLight : public ALightObject
{
public:
	CenterLoadingLight(std::string name, bool animating = true);
	~CenterLoadingLight();

	void initialize() override;
	void processInput(sf::Event event)override;
	void update(sf::Time deltaTime)override;

private:
	bool animating = true;

	const float SPEED_MULTIPLIER = 20.0f;

	float initial_Range = 30.f;

	float completionPrecentage = 0;

	float actual_current_Range = 0;
	float anim_current_Range = 0;
	const float max_Range = BaseWindow::WINDOW_WIDTH;

	//for glowing animating
	bool glowSmall = true;
	bool glowBig = false;
	float lowerlimit = actual_current_Range - 20.f;
	float upperlimit = actual_current_Range + 25.f;

	//for intensity animation
	float ticks = 0;
	float currentIntensity = 0.01f;
	float max_ticks = 1.5f;
	bool increasing = true;


	void animatingLightRange(sf::Time deltaTime);

};
