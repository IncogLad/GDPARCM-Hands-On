#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class BaseWindow: sf::NonCopyable
{
public:
	BaseWindow();
	~BaseWindow();

	void Run();

	static const unsigned int WINDOW_HEIGHT = 1080;
	static const unsigned int WINDOW_WIDTH = 1920;

private:

	sf::RenderWindow main_window;

	void render();
	void processEvents();
	void update(sf::Time deltaTime);


};

