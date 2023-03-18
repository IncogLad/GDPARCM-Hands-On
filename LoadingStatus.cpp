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

void LoadingStatus::setMaxItems(int amount)
{
	this->max_items = amount;
}

void LoadingStatus::incrementItems()
{
	this->itemsLoaded++;
}

float LoadingStatus::getLoadedItemsAmount()
{
	return this->itemsLoaded;
}

float LoadingStatus::getMaxItemsAmount()
{
	return this->max_items;
}

LoadingStatus::LoadingStatus()
{
	this->loadingDone = false;
}

LoadingStatus::~LoadingStatus()
{
}
