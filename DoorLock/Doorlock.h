#pragma once

#include "common.h"
#include "Dht.h"
#include <thread>

class Doorlock
{
private:
	bool isOpen;
	CDht* dht;

public:
	Doorlock();
	~Doorlock();


	void OpenDoor();
	void CloseDoor();
	void checkTemp();
};

void getTemp(Doorlock *status, CDht* dht);