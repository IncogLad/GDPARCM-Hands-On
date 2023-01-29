#include "BaseWindow.h"

const sf::Time BaseWindow::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

BaseWindow* BaseWindow::sharedInstance = nullptr;

BaseWindow* BaseWindow::getInstance()
{
	if (sharedInstance == nullptr) sharedInstance = new BaseWindow();

	return sharedInstance;
}

BaseWindow::BaseWindow(): main_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Test Window", sf::Style::Close)
{
	sharedInstance = this;
	this->main_window.setFramerateLimit(60);
    //initialize GOs/Textures/...
    
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
		currTime = clock.getElapsedTime();
		float deltaTime = currTime.asSeconds() - prevTime.asSeconds();
		this->fps = floor(1.0f / deltaTime);

		processEvents();
		update(sf::seconds(1/fps));
		render();
	}
}

void BaseWindow::render()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


	this->main_window.clear();
	this->main_window.draw(shape);
	this->main_window.display();

}

void BaseWindow::processEvents()
{
	sf::Event event;
	while (this->main_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			this->main_window.close();
	}
}

void BaseWindow::update(sf::Time elapsedTime)
{
    //Update all Tex/GO/.. Managers

}

