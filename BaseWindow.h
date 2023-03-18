#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <Candle/LightingArea.hpp>
#include <Candle/RadialLight.hpp>


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

	/*static const int WINDOW_HEIGHT = 720;
	static const int WINDOW_WIDTH = 1280;*/

	float getFPS();
	bool displayTitle = false;
	bool fadeDone = false;

private:
	static BaseWindow* sharedInstance;

	sf::RenderWindow main_window;
	float fps = 0.0f;
	int frames = 0;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);

	void fadeToBlack(sf::Time elapsedTime);
	void fadeToNormal(sf::Time elapsedTime);

	//temp vars
	candle::RadialLight mouse_light;
	candle::LightingArea fog;

	sf::Music music;
	sf::SoundBuffer sfxFile;
	sf::Sound sfxPlayer;

	float m_ticks = 0;
	float l_ticks = 1;
	const float MAX_TICKS = 1;
	const float LEAST_TICKS = 0;

	int fadeIn = 0;
	
};

