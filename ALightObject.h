#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <Candle/RadialLight.hpp>

class ALightObject
{
public:
	typedef std::string String;

	ALightObject(String name, bool isFirefly = false);
	virtual ~ALightObject();

	virtual void initialize();
	virtual void initFireflies(std::vector<candle::RadialLight*>* fireflyBunch);
	virtual void processInput(sf::Event event);
	virtual void update(sf::Time deltaTime);
	virtual void draw(sf::RenderWindow* targetWindow);

	String getName();
	virtual sf::FloatRect getLocalBounds();
	virtual sf::Vector2f getPosition();
	virtual sf::Vector2f getScale();

	virtual void setPosition(float x, float y);
	virtual void setScale(float x, float y);

	virtual candle::RadialLight* getLight();
	std::vector<candle::RadialLight*>* getFireflyBunch();

	bool isFirefly = false;

protected:
	String name;
	candle::RadialLight* light;
	std::vector<candle::RadialLight*>* fireflyBunch;

	float posX = 0.0f;
	float posY = 0.0f;
	float scaleX = 1.0f;
	float scaleY = 1.0f;
};

