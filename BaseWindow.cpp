#include "BaseWindow.h"

#include "BGObject.h"
#include "FPSCounter.h"
#include "GameObjectManager.h"
#include "TextureDisplay.h"
#include "TextureManager.h"

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

BaseWindow::BaseWindow(): main_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Testing this on *OLD PC* Window", sf::Style::Close)
{
	sharedInstance = this;
	this->main_window.setFramerateLimit(60);

	TextureManager::getInstance()->loadFromAssetList();

    //initialize GOs/Textures/...
	BGObject* bg_object = new BGObject("mainBG");
	GameObjectManager::getInstance()->addObject(bg_object);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fps_counter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fps_counter);
    
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
	this->main_window.clear();
	GameObjectManager::getInstance()->draw(&this->main_window);
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
				break;
			case sf::Event::Closed:
				this->main_window.close();
				break;

		}
	}
}

void BaseWindow::update(sf::Time elapsedTime)
{
	GameObjectManager::getInstance()->update(elapsedTime);

}

