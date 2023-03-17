#include "FPSCounter.h"
#include <iostream>
#include "BaseWindow.h"

FPSCounter::FPSCounter() : AGameObject("FPSCounter")
{
}

FPSCounter::~FPSCounter()
{
	delete this->statsText->getFont();
	delete this->statsText;
	AGameObject::~AGameObject();
}

void FPSCounter::initialize()
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Fonts/RestlessSoulBB-Bold.otf");

	this->statsText = new sf::Text();
	this->statsText->setFont(*font);
	this->statsText->setPosition(BaseWindow::WINDOW_WIDTH - 150, BaseWindow::WINDOW_HEIGHT - 70);
	this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->statsText->setOutlineThickness(2.5f);
	this->statsText->setCharacterSize(35);

	std::cout << "FPSCounter declared as " << this->getName() << "\n";
}

void FPSCounter::processInput(sf::Event event)
{
}

void FPSCounter::update(sf::Time deltaTime)
{
	this->updateFPS(deltaTime);
}

void FPSCounter::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if (this->statsText != nullptr)
		targetWindow->draw(*this->statsText);
}

void FPSCounter::updateFPS(sf::Time elapsedTime)
{
	int curr_fps;
	this->updateTime += elapsedTime;

	if (this->updateTime >= sf::seconds(0.5f)) {
		curr_fps = floor(BaseWindow::getInstance()->getFPS());  // NOLINT(clang-diagnostic-float-conversion)
		if (curr_fps > 60)
		{
			curr_fps = 60;
		}
		std::string fps_string = std::to_string(curr_fps);
		this->statsText->setString("FPS: " + fps_string);
		this->updateTime = sf::seconds(0.0f);
	}
}
