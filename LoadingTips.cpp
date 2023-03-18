#include "LoadingTips.h"

#include "BaseWindow.h"
#include "LoadingStatus.h"

LoadingTips::LoadingTips() :AGameObject("TipsObject")
{
}

LoadingTips::~LoadingTips()
{
	delete this->TitleMechanic->getFont();
	delete this->TitleMechanic;
	delete this->HintsMechanic->getFont();
	delete this->HintsMechanic;
	AGameObject::~AGameObject();
}

void LoadingTips::initialize()
{
	AGameObject::initialize();

	sf::Font* bfont = new sf::Font();
	bfont->loadFromFile("Media/Fonts/RestlessSoulBB-Bold.otf");

	sf::Font* rfont = new sf::Font();
	rfont->loadFromFile("Media/Fonts/RestlessSoulBB-Regular.otf");

	this->TitleMechanic = new sf::Text();
	this->TitleMechanic->setFont(*bfont);
	this->TitleMechanic->setPosition(80, BaseWindow::WINDOW_HEIGHT / 2 + 300);
	this->TitleMechanic->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->TitleMechanic->setOutlineThickness(2.5f);
	this->TitleMechanic->setCharacterSize(70);

	this->HintsMechanic = new sf::Text();
	this->HintsMechanic->setFont(*rfont);
	this->HintsMechanic->setPosition(80, BaseWindow::WINDOW_HEIGHT / 2 + 390);
	this->HintsMechanic->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->HintsMechanic->setOutlineThickness(2.5f);
	this->HintsMechanic->setCharacterSize(30);

	this->TitleList = new std::vector<std::string>();
	this->TitleList->push_back("Health");
	this->TitleList->push_back("Sanity");
	this->TitleList->push_back("Safe Spots");
	this->TitleList->push_back("Roots & Thorns");
	this->TitleList->push_back("The Monster");
	this->TitleList->push_back("Bushes & Baits");
	this->TitleList->push_back("The Center Root");
	this->TitleList->push_back("I'm Okay");
	this->TitleList->push_back("Loading...");

	this->HintsList = new std::vector<std::string>();
	this->HintsList->push_back("Your health is shown by the saturation of your environment. ");
	this->HintsList->push_back("Your light range represents your sanity. Make sure to keep your lights on.");
	this->HintsList->push_back("Visit one eight corners of the map to replenish both health and sanity.");
	this->HintsList->push_back("Be careful of where you're stepping on!");
	this->HintsList->push_back("Deep in the darkness lurks the monster that haunts you.");
	this->HintsList->push_back("Use your environment to your advantage. Hide behind bushes and lay down lures.");
	this->HintsList->push_back("Reach the center of the maze to find the truth.");
	this->HintsList->push_back("Check out our game in GGJ 2023! :D");
	this->HintsList->push_back(" ");

	std::cout << "LoadingTexts declared as " << this->getName() << "\n";

}

void LoadingTips::processInput(sf::Event event)
{
	AGameObject::processInput(event);
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (textIndex >= TitleList->size()-1)
		{
			textIndex = 0;
		}
		else
		{
			textIndex++;
		}
		
	}
}

void LoadingTips::update(sf::Time deltaTime)
{
	AGameObject::update(deltaTime);
	updateText();
}

void LoadingTips::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if (!LoadingStatus::getInstance()->getLoadingStatus())
	{
		if (this->TitleMechanic != nullptr)
			targetWindow->draw(*this->TitleMechanic);

		if (this->HintsMechanic != nullptr)
			targetWindow->draw(*this->HintsMechanic);
	}
	

}

void LoadingTips::updateText()
{

	this->TitleMechanic->setString(TitleList->at(textIndex));
	this->HintsMechanic->setString(HintsList->at(textIndex));
}
