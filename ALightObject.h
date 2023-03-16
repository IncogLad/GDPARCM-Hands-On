#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <Candle/RadialLight.hpp>

class ALightObject
{
public:
	typedef std::string String;

	ALightObject(String name);
	virtual ~ALightObject();

	virtual void initialize();
	virtual void processInput(sf::Event event);
	virtual void update(sf::Time deltaTime);
	virtual void draw(sf::RenderWindow* targetWindow);

	String getName();
	virtual sf::FloatRect getLocalBounds();
	virtual sf::Vector2f getPosition();
	virtual sf::Vector2f getScale();

	virtual void setPosition(float x, float y);
	virtual void setScale(float x, float y);


protected:
	String name;
	sf::Sprite* sprite;
	sf::Texture* texture;

	float posX = 0.0f;
	float posY = 0.0f;
	float scaleX = 1.0f;
	float scaleY = 1.0f;
};

