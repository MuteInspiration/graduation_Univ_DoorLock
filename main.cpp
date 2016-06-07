#include "COMMON.h"
#include "CNet.h"
#include "Doorlock.h"
#include "Dht.h"
#include "chat_message.h"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>


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




float getTemp(Doorlock *status, CDht* dht)
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
		{
				status->OpenDoor();
		}

		return avg;
	}
}

using boost::asio::ip::tcp;
int main(int argc, char* argv[])
{
	wiringPiSetup();
	
	try
	{
		Doorlock dl;
		CDht dht;

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(argv[1], argv[2]);
		tcp::resolver::iterator iterator = resolver.resolve(query);

		CNet c(io_service, iterator, &dl);
		boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

		char line[chat_message::max_body_length + 1];

		// 송신 위험할때.
		while(true)
		{
			if(getTemp(&dl, &dht) >= 45)
			{
				chat_message msg;
				strcpy(line, "warning");
				msg.body_length(strlen(line));
				memcpy(msg.body(), line, msg.body_length());  // msg.body()에 line을 msg.body_length()만큼 복사
				msg.encode_header();
				c.write(msg);
			}
		}

		c.close();
		t.join();

	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}






	return 0;
}
