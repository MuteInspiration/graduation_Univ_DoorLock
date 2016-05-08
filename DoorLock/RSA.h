#pragma once

#include "common.h"
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cstdlib>

class RSA
{
private:
	int n, message_length;

	long send_msg[100];
	char recv_msg[100], buffer[100];
	int public_key, private_key;
	long e_pi;

	int Make_Private_Key(int e, long e_pi);

	int IsNotPrime(int n);		//�Ҽ������˻�
	long Make_Random_Prime_Number();// ���� �ڼ�(2��) ������
	long mod(long n, long e, long m);	// mod ���� �Լ�
	int GCD(long x, long y);

	
public:
	RSA();
	~RSA();

	int Make_Cyper_text(char *Plain_text, long *Cyper_text, int key); //���� ��ȣ������ ����� �Լ�
	int Make_Plain_text(long *Cyper_text, char *Plain_text, int key); //��ȣ���� ������ ����� �Լ�

	int Make_Public_Key(long e_pi);
};

