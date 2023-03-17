#include "CenterLoadingLight.h"
#include <iostream>
#include "BaseWindow.h"
#include "LoadingStatus.h"

CenterLoadingLight::CenterLoadingLight(std::string name): ALightObject(name, false)
{
	
}

CenterLoadingLight::~CenterLoadingLight()
{
}

void CenterLoadingLight::initialize()
{
	ALightObject::initialize();
	std::cout << "Center Loading Light declared as " << this->getName() << "\n";

	this->light->setRange(this->initial_Range);
	this->light->setIntensity(11);
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

	animatingLightRange(deltaTime);

	this->completionPrecentage = LoadingStatus::getInstance()->getLoadedItemsAmount() / LoadingStatus::getInstance()->getMaxItemsAmount();
	std::cout << this->completionPrecentage << std::endl;

	this->actual_current_Range = this->completionPrecentage * this->max_Range;

	this->anim_current_Range = this->actual_current_Range;

}

void CenterLoadingLight::animatingLightRange(sf::Time deltaTime)
{

	if (lowerlimit)
	{
		anim_current_Range -= SPEED_MULTIPLIER * deltaTime.asSeconds();

		if (anim_current_Range <= lowerlimit)
		{
			lowerlimit = false;
			upperlimit = true;
		}
	}
	else if (upperlimit)
	{
		anim_current_Range += SPEED_MULTIPLIER * deltaTime.asSeconds();

		if (anim_current_Range >= upperlimit)
		{
			lowerlimit = true;
			upperlimit = false;
		}
	}

	this->light->setRange(anim_current_Range);


}
