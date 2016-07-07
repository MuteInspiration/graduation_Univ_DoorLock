#include "COMMON.h"
#include "CNet.h"


/*

 	 온도 확인, 문열림,닫힘 확인,미들서버와 연결

 * 온도 확인 센서는 계속 동작해야함.
 * 현재 io_service도 계속 동작해야됨. -> 소켓 비동기 프로그래밍
 *
 * 문여는 방법 2가지 경우
 * 1. 응급시에
 * 2. 사용자의 요청
 *
 * 응급시
 * 1. 미들서버로 넘겨야됨.
 *
 * 전송의 종류
 */

int main(int argc, char* argv[])
{
	wiringPiSetup();


	running("52.79.160.28", "9393");




	return 0;
}
