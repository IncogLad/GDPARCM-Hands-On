#pragma once

class LoadingStatus
{
public:
	LoadingStatus();
	~LoadingStatus();

	static LoadingStatus* getInstance();

	void setLoadingStatus(bool status);
	bool getLoadingStatus();

private:
	static LoadingStatus* sharedInstance;
	bool loadingDone;
};