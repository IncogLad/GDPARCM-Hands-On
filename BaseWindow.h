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
	static const int WINDOW_HEIGHT = 1080;
	static const int WINDOW_WIDTH = 1920;

	float getFPS();

private:
	static BaseWindow* sharedInstance;

	sf::RenderWindow main_window;
	float fps = 0.0f;
	int frames = 0;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);


};

