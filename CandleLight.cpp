#include "CandleLight.h"

CandleLight::CandleLight(std::string name) 
{
	this->mouseHoverLight = new candle::RadialLight();
	this->mouseHoverLight->setRange(150);
}

CandleLight::~CandleLight()
{
}
