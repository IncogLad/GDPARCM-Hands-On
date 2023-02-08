#pragma once
#include <thread>

class IETThread
{
public:
	IETThread();
	~IETThread();

	virtual void start();
	virtual void run() = 0;

public:

	virtual void sleep(int ms);
};

