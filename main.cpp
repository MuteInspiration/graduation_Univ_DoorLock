#include "COMMON.h"
#include "CNet.h"
#include "Doorlock.h"
#include "Dht.h"
#include "chat_message.h"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>


/*

 	 �µ� Ȯ��, ������,���� Ȯ��,�̵鼭���� ����

 * �µ� Ȯ�� ������ ��� �����ؾ���.
 * ���� io_service�� ��� �����ؾߵ�. -> ���� �񵿱� ���α׷���
 *
 * ������ ��� 2���� ���
 * 1. ���޽ÿ�
 * 2. ������� ��û
 *
 * ���޽�
 * 1. �̵鼭���� �Ѱܾߵ�.
 *
 * ������ ����
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

		// �۽� �����Ҷ�.
		while(true)
		{
			if(getTemp(&dl, &dht) >= 45)
			{
				chat_message msg;
				strcpy(line, "warning");
				msg.body_length(strlen(line));
				memcpy(msg.body(), line, msg.body_length());  // msg.body()�� line�� msg.body_length()��ŭ ����
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
