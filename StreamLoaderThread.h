#pragma once

#include <string>

#include "IETThread.h"
#include "IExecutionEvent.h"


class StreamLoaderThread :public IETThread
{
public:
	StreamLoaderThread(std::string, IExecutionEvent*);
	~StreamLoaderThread();

	void run() override;

private:
	std::string path;
	IExecutionEvent* execution_event_;

};

