#include "CenterLoadingLight.h"
#include <iostream>
#include "BaseWindow.h"
#include "LoadingStatus.h"

CenterLoadingLight::CenterLoadingLight(std::string name, bool animating): ALightObject(name, false)
{
	this->animating = animating;
		
}

CenterLoadingLight::~CenterLoadingLight()
{
}

void CenterLoadingLight::initialize()
{
	ALightObject::initialize();
	std::cout << "Center Loading Light declared as " << this->getName() << "\n";

	this->light->setRange(this->initial_Range);
	this->light->setIntensity(0.01f);

	if (!animating)
	{
		this->initial_Range = 30.f;
		this->light->setRange(this->initial_Range);
		this->light->setIntensity(1.f);
	}
	
	this->anim_current_Range = this->initial_Range;
	this->actual_current_Range = this->initial_Range;

	this->setPosition(BaseWindow::WINDOW_WIDTH / 2, BaseWindow::WINDOW_HEIGHT / 2);

}

void CenterLoadingLight::processInput(sf::Event event)
{
	ALightObject::processInput(event);
}

void CenterLoadingLight::update(sf::Time deltaTime)
{
	ALightObject::update(deltaTime);

	if (animating) {
		animatingLightRange(deltaTime);

		this->completionPrecentage = LoadingStatus::getInstance()->getLoadedItemsAmount() / LoadingStatus::getInstance()->getMaxItemsAmount();
		//std::cout << this->completionPrecentage << std::endl;

		this->actual_current_Range = this->completionPrecentage * this->max_Range;
		this->anim_current_Range = this->actual_current_Range;
	}

}

void CenterLoadingLight::animatingLightRange(sf::Time deltaTime)
{

	if (glowSmall)
	{
		anim_current_Range -= SPEED_MULTIPLIER * deltaTime.asSeconds();
		
		if (anim_current_Range <= lowerlimit)
		{
			glowSmall = false;
			glowBig = true;
		}
	}
	else if (glowBig)
	{
		anim_current_Range += SPEED_MULTIPLIER * deltaTime.asSeconds();
		if (anim_current_Range >= upperlimit)
		{
			glowSmall = true;
			glowBig = false;
		}
	}

	
	if (increasing)
	{
		this->currentIntensity += deltaTime.asSeconds() * 1;
		if (currentIntensity >= 1.0f)
		{
			currentIntensity = 1.0f;
			increasing = false;
		}
	}
	else
	{
		this->currentIntensity -= deltaTime.asSeconds() * 1;
		if (currentIntensity <= 0.9f)
		{
			increasing = true;
		}
	}
	
	
	//std::cout << currentIntensity << std::endl;
	this->light->setRange(anim_current_Range);
	this->light->setIntensity(currentIntensity);
	lowerlimit = actual_current_Range - 20.f;
	upperlimit = actual_current_Range + 25.f;

}
