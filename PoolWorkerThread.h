#pragma once
#include "IETThread.h"
class IWorkerAction;
class IFinishedTask;

class PoolWorkerThread: public IETThread
{
public:
	PoolWorkerThread(int id, IFinishedTask* finishedTask);
	~PoolWorkerThread();

	//void onStartTask() override;


private:

	void run() override;

	int id;
	IWorkerAction* action;
	IFinishedTask* finishedTask;

	
};

