#include "RSA.h"



RSA::RSA()
{
	e_pi = Make_Random_Prime_Number();		
	// 두개의 소수를 만들고 n값을 구한다.
	
	public_key = Make_Public_Key(e_pi); // 공개키를 만듬.
	private_key = Make_Private_Key(public_key, e_pi);	// 개인키를 만듬
}


RSA::~RSA()
{
}

long RSA::Make_Random_Prime_Number()// 랜덤 솟수(2개) 생성기
{
	int i;
	int Prime[2]; // P와 Q 두개의 솟수는 공개키, 비밀키의 기본 소수
	time_t t;
	srand((unsigned int)time(&t)); //난수생성
	for (i = 0; i<2; i++)				// 2개의 임의의 솟수 P와 Q를 생성한다. 
	{
		do	
			Prime[i] = rand() % 100;  //2자리로 제한 
		while (IsNotPrime(Prime[i]));	 //소수가 아니면 반복한다.
	}
	n = Prime[0] * Prime[1];		// 두개의 소수 p,q를 이용해 n값 생성
	printf("\nP=%d, Q=%d e_pi=%d n=%d \n", Prime[0], Prime[1], n);
	return (Prime[0] - 1)*(Prime[1] - 1);  // 오일러 파이값;
}

int RSA::Make_Public_Key(long e_pi)
{
	long e;
	do
	{
		e = rand() % 100;	//3자리로 제한	
		if ((e<e_pi) && (GCD(e, e_pi) == 1)) 
			return e;	// 오일러 파이와 서로 소인 e를 리턴. 
	} while (1);
}

int RSA::Make_Private_Key(int e, long e_pi)
{
	int d = 0;
	while (((e*d) % e_pi) != 1) d++;		//개인키 생성
	return d;	//개인키를 리턴한다. 
}

int RSA::IsNotPrime(int n)		//소수가 아닌지 검사
{
	int  i, limit;
	
	if (!(n % 2))  
		return (TRUE);	//짝수이면 소수가 아니다.

	limit = (int)sqrt(n) + 1;	//n제곱+1을 하여 보다 빨리 소수를 찾는다.

	for (i = 3; i <= limit; i += 2) //3부터 홀수 단위로 나머지 연산을 한다. 
		if (!(n%i))  
			return (TRUE);

	return (FALSE);
}

long RSA::mod(long n, long e, long m)
// residue = n^e (mod m)을 수행한다.
{
	long i, residue = 1;
	for (i = 1; i <= e; i++)
	{
		residue *= n;	//residue=residue*n
		residue %= m;
	}
	
	// residue=residue%n 오버플로를 방지하고자
	// mod연산을 이용하여 자릿수를 줄인다.
	return residue;
}

int RSA::GCD(long x, long y)		//최대 공약수 검사
{
	return y == 0 ? x : GCD(y, x % y);
}

int RSA::Make_Cyper_text(char *Plain_text, long *Cyper_text, int key)
{
	int i;
	message_length = strlen(Plain_text);
	for (i = 0; i<message_length; i++)	  //메세지 길이에 맞게 반복한다.
		Cyper_text[i] = (long)mod(Plain_text[i], key, n);  //암호화
	Cyper_text[i] = '\0';		//종료 표시

	printf("====================================================\n");
	printf(" 암호화된 데이터 = ");
	for (i = 0; i<message_length; i++)
		printf(" %d ", Cyper_text[i]);	//암호화된 데이터를 출력하여 보여준다.
	printf("\n");
	return 0;
}

int RSA::Make_Plain_text(long *Cyper_text, char *Plain_text, int key)
{
	int  i;
	for (i = 0; i<message_length; i++) // 메세지 길이에 맞게 반복한다.
		Plain_text[i] = (char)mod(Cyper_text[i], key, n);	//복호화
	Plain_text[i] = '\0';	//종료 표시

	printf("receive message = ");
	for (i = 0; i<message_length; i++)
		printf(" %d ", Plain_text[i]);	//복호화된 데이터를 출력하여 보여준다.
	printf("\n");
	return 0;
}
