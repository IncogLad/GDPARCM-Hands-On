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
#include "LoadingTips.h"


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

	LoadingTips* loading_tips = new LoadingTips();
	GameObjectManager::getInstance()->addObject_UI(loading_tips);

	CenterLoadingLight* loading_light = new CenterLoadingLight("center_light");
	LightObjectManager::getInstance()->addObject(loading_light);

	
	Fireflies* fireflies1 = new Fireflies("fireflies1", sf::Color::Green, sf::Vector2f(183, 476));
	LightObjectManager::getInstance()->addObject(fireflies1);

	Fireflies* fireflies2 = new Fireflies("fireflies2", sf::Color::Magenta, sf::Vector2f(397, 757));
	LightObjectManager::getInstance()->addObject(fireflies2);

	Fireflies* fireflies3 = new Fireflies("fireflies3", sf::Color::Blue, sf::Vector2f(920, 964));
	LightObjectManager::getInstance()->addObject(fireflies3);

	Fireflies* fireflies4 = new Fireflies("fireflies4", sf::Color::Cyan, sf::Vector2f(1469, 762));
	LightObjectManager::getInstance()->addObject(fireflies4);

	Fireflies* fireflies5 = new Fireflies("fireflies5", sf::Color::White, sf::Vector2f(1764, 471));
	LightObjectManager::getInstance()->addObject(fireflies5);

	Fireflies* fireflies6 = new Fireflies("fireflies6", sf::Color::White, sf::Vector2f(1422, 208));
	LightObjectManager::getInstance()->addObject(fireflies6);

	Fireflies* fireflies7 = new Fireflies("fireflies7", sf::Color::Yellow, sf::Vector2f(932, 97));
	LightObjectManager::getInstance()->addObject(fireflies7);

	Fireflies* fireflies8 = new Fireflies("fireflies8", sf::Color::Red, sf::Vector2f(480, 225));
	LightObjectManager::getInstance()->addObject(fireflies8);


	this->mouse_light.setRange(50);
	this->fog.setAreaColor(sf::Color::Black);

	if (!music.openFromFile("Media/Audio/Horror_Ambience_BGM.ogg"))
	{
		return;
	}

	this->music.play();
	this->music.setLoop(true);

	if (!sfxFile.loadFromFile("Media/Audio/Bush_Hide_SFX.ogg"))
	{
		return;
	}
	this->sfxPlayer.setBuffer(sfxFile);

}

BaseWindow::~BaseWindow()
{
	this->music.stop();
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
		this->fog.draw(this->mouse_light);
		LightObjectManager::getInstance()->drawOnFog(&this->fog);
		this->fog.display();
	}
	else
	{
		if (LoadingStatus::getInstance()->finishedOnce)
		{
			this->music.stop();
			if (!music.openFromFile("Media/Audio/Ending_BGM.ogg"))
			{
				return;
			}

			this->music.play();
			this->music.setLoop(true);
			LoadingStatus::getInstance()->finishedOnce = false;
		}
		
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
			case sf::Event::MouseButtonReleased:
				GameObjectManager::getInstance()->processInput(event);
				sfxPlayer.setVolume(15);
				sfxPlayer.play();
				break;
			case sf::Event::MouseMoved:
				sf::Vector2f mp(sf::Mouse::getPosition().x - this->main_window.getPosition().x - 5.f,sf::Mouse::getPosition().y - this->main_window.getPosition().y - 25.f);
				this->mouse_light.setPosition(mp);
				//std::cout << sf::Mouse::getPosition().x - this->main_window.getPosition().x - 5.f << " " <<sf::Mouse::getPosition().y - this->main_window.getPosition().y - 25.f << std::endl;
				break;
			
		}
	}
}

void BaseWindow::update(sf::Time elapsedTime)
{
	GameObjectManager::getInstance()->update(elapsedTime);
	LightObjectManager::getInstance()->update(elapsedTime);
	
}

