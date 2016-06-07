#pragma once

#include "COMMON.h"

// 임계영역인 Doorlock 클래스

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


