#include "Doorlock.h"

void getTemp(Doorlock *status, CDht* dht)
{
	while (true)
	{
		dht->initSig();
		dht->StartSig();
		int temp = 0;
		int temper;
		int times = 5;
		float avg = 0.0;

		for (int i = 0; i < times; i++)
		{
			temper = dht->getTemperture();

			if(temper < 50)
				temp += temper;

			delay(2000);
		}

		avg = temp / times;
			

		if (avg >= 45)
				status->OpenDoor();
		
	}
}


Doorlock::Doorlock()
{
	isOpen = false;

	pinMode(DECT_PIN, INPUT);

	pinMode(RELAY_PIN, OUTPUT);

	dht = new CDht();


}


Doorlock::~Doorlock()
{
}

void Doorlock::OpenDoor()
{
	cout << "trying to OpenDoor" << endl;

	if (isOpen == false)
	{
		digitalWrite(RELAY_PIN, HIGH);
		delay(1000);
		digitalWrite(RELAY_PIN, LOW);
		isOpen = true;
	}

}

void Doorlock::CloseDoor()
{
	if (isOpen == true)
	{
		digitalWrite(RELAY_PIN, HIGH);
		delay(1000);
		digitalWrite(RELAY_PIN, LOW);
	}
}

void Doorlock::checkTemp()
{

	thread temp(&getTemp, this ,dht);

	temp.join();
}

