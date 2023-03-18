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
	//std::cout << "Destroying stream asset loader." << std::endl;
}

void StreamLoaderThread::onStartTask()
{
	IETThread::sleep(2500);
	TextureManager::getInstance()->instantiateAsTexture(this->path, this->path, true);
	
	std::cout << "[TextureManager] Loaded streaming texture: " << this->path << std::endl;

	this->execution_event_->onFinishedExecution();
	delete this;

}
