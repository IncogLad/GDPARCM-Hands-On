#include "StreamLoaderThread.h"
#include <iostream>
#include "TextureManager.h"



StreamLoaderThread::StreamLoaderThread(std::string SPath , IExecutionEvent* EE)
{
	this->path = SPath;
	this->execution_event_ = EE;
}

StreamLoaderThread::~StreamLoaderThread()
{
	std::cout << "Destroying stream asset loader." << std::endl;
}

void StreamLoaderThread::onStartTask()
{
	std::cout << "Running stream asset loader " << std::endl;

	IETThread::sleep(1000);
	TextureManager::getInstance()->instantiateAsTexture(this->path, this->path, true);
	//IETThread::sleep(1000);

	//<code here for loading asset>
	//String assetName = "";

	std::cout << "[TextureManager] Loaded streaming texture: " << this->path << std::endl;

	this->execution_event_->onFinishedExecution();
	delete this;

}
