#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class BaseWindow: sf::NonCopyable
{
public:
	BaseWindow();
	~BaseWindow();

	void Run();

	static BaseWindow* getInstance();

	static const sf::Time TIME_PER_FRAME;
	static const unsigned int WINDOW_HEIGHT = 1080;
	static const unsigned int WINDOW_WIDTH = 1920;

private:
	static BaseWindow* sharedInstance;

	sf::RenderWindow main_window;
	float fps = 0.0f;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);


};

