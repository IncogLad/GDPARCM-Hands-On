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

void StreamLoaderThread::run()
{
	std::cout << "Running stream asset loader " << std::endl;

	IETThread::sleep(100);

}
