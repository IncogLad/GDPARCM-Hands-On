#pragma once

class LoadingStatus
{
public:
	LoadingStatus();
	~LoadingStatus();

	static LoadingStatus* getInstance();

	void setLoadingStatus(bool status);
	bool getLoadingStatus();

	void setMaxItems(int amount);
	void incrementItems();

	float getLoadedItemsAmount();
	float getMaxItemsAmount();

private:
	static LoadingStatus* sharedInstance;

	int itemsLoaded = 0;

	int max_items;

	bool loadingDone;
};