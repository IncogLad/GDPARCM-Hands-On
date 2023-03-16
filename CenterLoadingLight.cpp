#include "CenterLoadingLight.h"
#include <iostream>
#include "BaseWindow.h"

CenterLoadingLight::CenterLoadingLight(std::string name): ALightObject(name)
{
}

CenterLoadingLight::~CenterLoadingLight()
{
}

void CenterLoadingLight::initialize()
{
	ALightObject::initialize();
	std::cout << "BGObject declared as " << this->getName() << "\n";

	this->light->setRange(10);

	std::cout << BaseWindow::WINDOW_WIDTH  << " ";
	std::cout << BaseWindow::WINDOW_HEIGHT  << "\n";

	this->setScale(static_cast<float>(BaseWindow::WINDOW_WIDTH),
		static_cast<float>(BaseWindow::WINDOW_HEIGHT));
}

void CenterLoadingLight::processInput(sf::Event event)
{
	ALightObject::processInput(event);
}

void CenterLoadingLight::update(sf::Time deltaTime)
{
	ALightObject::update(deltaTime);
}
