#include "Dht.h"



CDht::CDht()
{
	initSig();
}


CDht::~CDht()
{
}


void CDht::initSig()
{
	for (int i = 0; i<5; i++)
		dht11_val[i] = 0;

	lststate = HIGH;
	counter = 0;
}

void CDht::StartSig()
{
	pinMode(DHT_PIN, OUTPUT);
	digitalWrite(DHT_PIN, LOW);
	delay(18);
	digitalWrite(DHT_PIN, HIGH);
	delayMicroseconds(40);
	pinMode(DHT_PIN, INPUT);
}

int CDht::getTemperture()
{
	int j = 0;
	for (int i = 0; i < MAX_TIME; i++)
	{
		counter = 0;

		while (digitalRead(DHT_PIN) == lststate)
		{
			counter++;
			delayMicroseconds(1);
			if (counter == 255) break;
		}

		lststate = digitalRead(DHT_PIN);
		if (counter == 255) break;

		// 1~3�� ���� ���� �����ؾߵ�
		if ((i >= 4) && ((i % 2) == 0))
		{
			dht11_val[j / 8] <<= 1;

			if (counter > 16)
				dht11_val[j / 8] |= 1;

			j++;
		}
	}

	// ������ �������� ����
	// ���� ����� ���Ӵ��� Ȯ���ϰ� �����Ѵ�.
	if ((j >= 40) && (dht11_val[4] == ((dht11_val[0] + dht11_val[1] + dht11_val[2] + dht11_val[3]) & 0xFF)))
	{
		return dht11_val[2];
	}

	cout << "Debugging for Temperture : " << dht11_val[2] << endl;
	return dht11_val[2];
}
