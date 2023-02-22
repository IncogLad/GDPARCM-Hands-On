#pragma once

#include <string>
#include "IExecutionEvent.h"
#include "IWorkerAction.h"

class IWorkerAction;

class StreamLoaderThread :public IWorkerAction
{
public:
	StreamLoaderThread(std::string, IExecutionEvent*);
	~StreamLoaderThread();

	void onStartTask() override;


private:
	std::string path;
	IExecutionEvent* execution_event_;

};

