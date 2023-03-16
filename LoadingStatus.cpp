#include "LoadingStatus.h"

LoadingStatus* LoadingStatus::sharedInstance = nullptr;

LoadingStatus* LoadingStatus::getInstance()
{
	if (sharedInstance == nullptr) sharedInstance = new LoadingStatus();

	return sharedInstance;
}

void LoadingStatus::setLoadingStatus(bool status)
{
	this->loadingDone = status;
}

bool LoadingStatus::getLoadingStatus()
{
	return this->loadingDone;
}

LoadingStatus::LoadingStatus()
{
	this->loadingDone = false;
}

LoadingStatus::~LoadingStatus()
{
}
