#pragma once

#include "common.h"

class CDht
{

private:
	const int MAX_TIME = 85;

	int dht11_val[5]; 


	int lststate;
	int counter;



public:
	CDht();
	~CDht();

	void initSig();
	void StartSig();
	int getTemperture();
};

