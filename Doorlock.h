#pragma once

#include "COMMON.h"

// �Ӱ迵���� Doorlock Ŭ����

class Doorlock
{
private:
	bool isOpen;

public:
	Doorlock();
	~Doorlock();


	void OpenDoor();
	void CloseDoor();

};


