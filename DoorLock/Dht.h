#pragma once

#include "common.h"

class CDht
{

private:
	const int MAX_TIME = 85;

	int dht11_val[5]; 

	uint8_t lststate;
	uint8_t counter;



public:
	CDht();
	~CDht();

	void initSig();
	void StartSig();
	int getTemperture();
};

