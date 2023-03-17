#include "Fireflies.h"

Fireflies::Fireflies(std::string name, sf::Color color, sf::Vector2f initPosition): ALightObject(name)
{
	this->name = name;
	this->color = color;
	this->isFirefly = true;

	this->initPosition = initPosition;
	this->fireflyBunch = new std::vector<candle::RadialLight*>();
}

Fireflies::~Fireflies()
{
}

void Fireflies::initialize()
{
	ALightObject::initialize();

	candle::RadialLight* firefly1 = new candle::RadialLight();
	firefly1->setPosition(-27, 22);

	candle::RadialLight* firefly2 = new candle::RadialLight();
	firefly2->setPosition(13, 49);

	candle::RadialLight* firefly3 = new candle::RadialLight();
	firefly3->setPosition(-28, -36);

	candle::RadialLight* firefly4 = new candle::RadialLight();
	firefly4->setPosition(28, -36);

	this->fireflyBunch->push_back(firefly1);
	this->fireflyBunch->push_back(firefly2);
	this->fireflyBunch->push_back(firefly3);
	this->fireflyBunch->push_back(firefly4);

	this->initFireflies(this->fireflyBunch);

	this->light->setRange(100);
	this->light->setIntensity(0.5);
	this->light->setColor(this->color);

	this->setPosition(initPosition.x, initPosition.y);

	for (int i = 0; i < this->fireflyBunch->size(); i++)
	{
		this->fireflyBunch->at(i)->setColor(this->color);
		this->fireflyBunch->at(i)->setIntensity(1);
		this->fireflyBunch->at(i)->setRange(10);
	}

	std::vector<sf::Vector2f> f1 = { sf::Vector2f(30, 30) ,sf::Vector2f(-30, 50) , sf::Vector2f(20, -40) };
	std::vector<sf::Vector2f> f2 = { sf::Vector2f(-30, -30) ,sf::Vector2f(-30, 50) , sf::Vector2f(20, -40), sf::Vector2f(0, 20), sf::Vector2f(-40, 0) };
	std::vector<sf::Vector2f> f3 = { sf::Vector2f(30, 30) ,sf::Vector2f(30, 10) , sf::Vector2f(-20, -40), sf::Vector2f(50, 50) };
	std::vector<sf::Vector2f> f4 = { sf::Vector2f(30, -30) ,sf::Vector2f(30, -10) , sf::Vector2f(50, -40), sf::Vector2f(-4, 23) };

	fireflyPatrolRoutes = { f1,f2,f3,f4 };
	
	for (int i = 0; i < this->currentRoute.size(); i++)
	{
		this->currentRoute.at(i) = 0;
	}

}

void Fireflies::processInput(sf::Event event)
{
	ALightObject::processInput(event);
}

void Fireflies::update(sf::Time deltaTime)
{
	ALightObject::update(deltaTime);

	for (int i = 0; i < this->fireflyBunch->size(); i ++)
	{
		bool xArrived = false;
		bool yArrived = false;

		if (this->fireflyBunch->at(i)->getPosition().x < fireflyPatrolRoutes[i][currentRoute[i]].x + this->light->getPosition().x)
		{
			float increment = this->fireflyBunch->at(i)->getPosition().x + deltaTime.asSeconds() * SPEED_MULTIPLIER;
			this->fireflyBunch->at(i)->setPosition(increment, this->fireflyBunch->at(i)->getPosition().y);
		}
		else
		{
			float increment = this->fireflyBunch->at(i)->getPosition().x - deltaTime.asSeconds() * SPEED_MULTIPLIER;
			this->fireflyBunch->at(i)->setPosition(increment, this->fireflyBunch->at(i)->getPosition().y);
		}

		if (this->fireflyBunch->at(i)->getPosition().y < fireflyPatrolRoutes[i][currentRoute[i]].y + this->light->getPosition().y)
		{
			float increment = this->fireflyBunch->at(i)->getPosition().y + deltaTime.asSeconds() * SPEED_MULTIPLIER;
			this->fireflyBunch->at(i)->setPosition(this->fireflyBunch->at(i)->getPosition().x, increment);
		}
		else
		{
			float increment = this->fireflyBunch->at(i)->getPosition().y - deltaTime.asSeconds() * SPEED_MULTIPLIER;
			this->fireflyBunch->at(i)->setPosition(this->fireflyBunch->at(i)->getPosition().x, increment);
		}


		if ((this->fireflyBunch->at(i)->getPosition().x - fireflyPatrolRoutes[i][currentRoute[i]].x) <= 0.025f ||
			(this->fireflyBunch->at(i)->getPosition().x - fireflyPatrolRoutes[i][currentRoute[i]].x) >= -0.025f )
		{
			xArrived = true;
		}
		if ((this->fireflyBunch->at(i)->getPosition().y - fireflyPatrolRoutes[i][currentRoute[i]].y) <= 0.025f ||
			(this->fireflyBunch->at(i)->getPosition().y - fireflyPatrolRoutes[i][currentRoute[i]].y) >= -0.025f)
		{
			yArrived = true;
		}

		//std::cout << i << ": " << this->fireflyBunch->at(i)->getPosition().x << " " << this->fireflyBunch->at(i)->getPosition().y << std::endl;

		if (xArrived && yArrived)
		{
			currentRoute[i]++;
		}

		if (currentRoute[i] >= fireflyPatrolRoutes[i].size())
		{
			currentRoute[i] = 0;
		}
		
	}

}
