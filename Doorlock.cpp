#include "Doorlock.h"



Doorlock::Doorlock()
{
	isOpen = false;

	pinMode(RELAY_PIN, OUTPUT);

}

Doorlock::~Doorlock()
{
}

void Doorlock::OpenDoor()
{
	cout << "The Door is Opening now \n";
	// 여기에 체크하는 함수를 넣어야함.
	digitalWrite(RELAY_PIN, HIGH);
	delay(1000);
	digitalWrite(RELAY_PIN, LOW);
	isOpen = true;

}
/*
void Doorlock::CloseDoor()
{
	if (isOpen == true)
	{
		// 여기에 체크하는 함수를 넣어야함.
		digitalWrite(RELAY_PIN, HIGH);
		delay(1000);
		digitalWrite(RELAY_PIN, LOW);
		isOpen = false;
	}
}
*/

