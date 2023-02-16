#pragma once

#include <string>

#include "IWorkerAction.h"
#include "IExecutionEvent.h"

class IETThread;

class StreamLoaderThread :public IETThread
{
public:
	StreamLoaderThread(std::string, IExecutionEvent*);
	~StreamLoaderThread();

	//void onStartTask() override;

	void run() override;

private:
	std::string path;
	IExecutionEvent* execution_event_;

};

