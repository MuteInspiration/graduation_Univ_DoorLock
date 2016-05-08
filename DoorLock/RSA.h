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

	int IsNotPrime(int n);		//소수인지검사
	long Make_Random_Prime_Number();// 랜덤 솟수(2개) 생성기
	long mod(long n, long e, long m);	// mod 수학 함수
	int GCD(long x, long y);

	
public:
	RSA();
	~RSA();

	int Make_Cyper_text(char *Plain_text, long *Cyper_text, int key); //평문을 암호문으로 만드는 함수
	int Make_Plain_text(long *Cyper_text, char *Plain_text, int key); //암호문을 평문으로 만드는 함수

	int Make_Public_Key(long e_pi);
};

