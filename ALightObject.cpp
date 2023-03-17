#include "ALightObject.h"

ALightObject::ALightObject(String name, bool isFirefly)
{
	this->light = new candle::RadialLight();
	this->name = name;
	
	this->isFirefly = isFirefly;

	if(this->isFirefly)
	{
		this->fireflyBunch = new std::vector<candle::RadialLight*>();
	}
}

ALightObject::~ALightObject()
{
	//delete this->light;
}

void ALightObject::initialize()
{
	//virtual
}

void ALightObject::initFireflies(std::vector<candle::RadialLight*>* fireflyBunch)
{
	if (this->isFirefly)
	{
		this->fireflyBunch = fireflyBunch;
	}
}

void ALightObject::processInput(sf::Event event)
{
	//virtual
}

void ALightObject::update(sf::Time deltaTime)
{
	//virtual
}

void ALightObject::draw(sf::RenderWindow* targetWindow)
{
	
		this->light->setPosition(this->posX, this->posY);
		this->light->setScale(this->scaleX, this->scaleY);
		targetWindow->draw(*this->light);
		if (this->fireflyBunch)
		{
			for (int i = 0; i < this->fireflyBunch->size(); i++)
			{
				targetWindow->draw(*this->fireflyBunch->at(i));
			}
		}

	

}

ALightObject::String ALightObject::getName()
{
	return this->name;
}

void ALightObject::setPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;

	
	this->light->setPosition(this->posX, this->posY);
	if (this->fireflyBunch)
	{
		for (int i = 0; i < this->fireflyBunch->size(); i++)
		{
			this->fireflyBunch->at(i)->setPosition(this->posX + this->fireflyBunch->at(i)->getPosition().x, this->posY + this->fireflyBunch->at(i)->getPosition().y);
		}
	}
	

}

void ALightObject::setScale(float x, float y)
{
	this->scaleX = x;
	this->scaleY = y;

	this->light->setScale(this->scaleX, this->scaleY);
	

}

candle::RadialLight* ALightObject::getLight()
{
	return this->light;
}


std::vector<candle::RadialLight*>* ALightObject::getFireflyBunch()
{
	return this->fireflyBunch;
}

sf::FloatRect ALightObject::getLocalBounds()
{
	return this->light->getLocalBounds();
}

sf::Vector2f ALightObject::getPosition()
{
	return this->light->getPosition();
}

sf::Vector2f ALightObject::getScale()
{
	return this->light->getScale();
}
