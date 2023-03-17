#include "BaseWindow.h"

#include <iostream>

#include "BGObject.h"
#include "FPSCounter.h"
#include "GameObjectManager.h"
#include "TextureDisplay.h"
#include "TextureManager.h"
#include "Fireflies.h"
#include "LoadingStatus.h"
#include "LightObjectManager.h"
#include "CenterLoadingLight.h"
#include "Fireflies.h"


const sf::Time BaseWindow::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

BaseWindow* BaseWindow::sharedInstance = nullptr;

BaseWindow* BaseWindow::getInstance()
{
	if (sharedInstance == nullptr) sharedInstance = new BaseWindow();

	return sharedInstance;
}

float BaseWindow::getFPS()
{
	return this->fps;
}

BaseWindow::BaseWindow(): main_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Back to Laptop Window", sf::Style::Close),
fog(candle::LightingArea::FOG, sf::Vector2f(0.f, 0.f), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))
{
	sharedInstance = this;
	this->main_window.setFramerateLimit(60);

	TextureManager::getInstance()->loadFromAssetList();

    //initialize GOs/Textures/...
	BGObject* bg_object = new BGObject("mainBG");
	GameObjectManager::getInstance()->addObject_BG(bg_object);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fps_counter = new FPSCounter();
	GameObjectManager::getInstance()->addObject_UI(fps_counter);

	CenterLoadingLight* loading_light = new CenterLoadingLight("center_light");
	LightObjectManager::getInstance()->addObject(loading_light);

	mouse_light.setRange(150);
	fog.setAreaColor(sf::Color::Black);
    
}

BaseWindow::~BaseWindow()
{
	
}

void BaseWindow::Run()
{
	sf::Clock clock;
	sf::Time prevTime = clock.getElapsedTime();
	sf::Time currTime = sf::Time::Zero;

	while (this->main_window.isOpen())
	{
		++frames;
		currTime = clock.getElapsedTime();
		float deltaTime = currTime.asSeconds() - prevTime.asSeconds();
		//this->fps = floor(1.0f / deltaTime);
		this->fps = frames / deltaTime;

		processEvents();
		update(sf::seconds(1/fps));
		render();
	}
}

void BaseWindow::render()
{
	if (!LoadingStatus::getInstance()->getLoadingStatus()) {
		this->fog.clear();
		this->fog.draw(mouse_light);
		for(int i = 0; i < LightObjectManager::getInstance()->getLightObjectList().size(); i++)
		{
			if (LightObjectManager::getInstance()->getLightObjectList().at(i) != nullptr) {
				this->fog.draw(*LightObjectManager::getInstance()->getLightObjectList().at(i)->getLight());
			}
		}
		this->fog.display();
	}

	this->main_window.clear();
	GameObjectManager::getInstance()->draw_BG(&this->main_window);
	GameObjectManager::getInstance()->draw(&this->main_window);
	
	if (!LoadingStatus::getInstance()->getLoadingStatus()) {
		this->main_window.draw(fog);
	}
	//LightObjectManager::getInstance()->draw(&this->main_window);

	GameObjectManager::getInstance()->draw_UI(&this->main_window);
	this->main_window.display();

}

void BaseWindow::processEvents()
{
	sf::Event event;
	while (this->main_window.pollEvent(event))
	{
		switch (event.type)
		{
			default: 
				GameObjectManager::getInstance()->processInput(event);
				LightObjectManager::getInstance()->processInput(event);
				break;
			case sf::Event::Closed:
				this->main_window.close();
				break;
			case sf::Event::MouseMoved:
				sf::Vector2f mp(sf::Mouse::getPosition().x - this->main_window.getPosition().x - 5.f,
					sf::Mouse::getPosition().y - this->main_window.getPosition().y - 25.f);
				mouse_light.setPosition(mp);
				break;
		}
	}
}

void BaseWindow::update(sf::Time elapsedTime)
{
	GameObjectManager::getInstance()->update(elapsedTime);
	LightObjectManager::getInstance()->update(elapsedTime);
}

