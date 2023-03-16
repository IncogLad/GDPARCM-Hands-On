#pragma once
#include "AGameObject.h"

#include "Candle/RadialLight.hpp"


class CandleLight
{
public:
	CandleLight(std::string name);
	~CandleLight();

	candle::RadialLight* mouseHoverLight;
	

private:
	


};

