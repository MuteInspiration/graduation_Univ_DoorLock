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
	// ���⿡ üũ�ϴ� �Լ��� �־����.
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
		// ���⿡ üũ�ϴ� �Լ��� �־����.
		digitalWrite(RELAY_PIN, HIGH);
		delay(1000);
		digitalWrite(RELAY_PIN, LOW);
		isOpen = false;
	}
}
*/

