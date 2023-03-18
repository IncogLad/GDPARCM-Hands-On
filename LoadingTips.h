#pragma once
#include "AGameObject.h"

class LoadingTips :public AGameObject
{
public:
	LoadingTips();
	~LoadingTips();
	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow* targetWindow) override;

private:
	sf::Text* TitleMechanic;
	sf::Text* HintsMechanic;

	std::vector<std::string>* TitleList;
	std::vector<std::string>* HintsList;

	void updateText();

	int textIndex = 0;

};

