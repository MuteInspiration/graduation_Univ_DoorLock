#include "common.h"
#include "Doorlock.h"
#include <string>
/*

		����Ʈ ������ ����� ��������

		16.04.08 Dht �ۼ���, ������ ������ȣ
*/



int main(void)
{
	wiringPiSetup();

	Doorlock doorlock;

	doorlock.checkTemp();



	
	return 0;
}