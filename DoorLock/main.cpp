#include "common.h"
#include "Doorlock.h"
#include <string>
/*

		스마트 디지털 도어락 개발일지

		16.04.08 Dht 송수신, 문열림 닫힘신호
*/



int main(void)
{
	wiringPiSetup();

	Doorlock doorlock;

	doorlock.checkTemp();



	
	return 0;
}