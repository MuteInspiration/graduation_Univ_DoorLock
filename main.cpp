#include "common.h"
#include "Net.h"
#include <string>

/*

		����Ʈ ������ ����� ��������

		16.04.08 Dht �ۼ���, ������ ������ȣ
		16.05.12 boost Library ��ġ �Ϸ�. - Socket�� ���� �ȵ���̵�� ��ſ���
				  SHA-1 SALT ���
		16.05.13  Node.js �̵鼭���� ���Կ��� -> �� C++ App���� Node.js ���� �������ٿ���.
		 outer.js�� ���� -> ���� �߰��� ������ ������??? ���� �浵 ����.
*/



int main(void)
{
	wiringPiSetup();
	
	try
	{
		//asio�� ����ϴ� ��� ���α׷��� ��� �ϳ��̻��� boost::asio::io_service ��ü�� �ʿ���
		boost::asio::io_service io_service;
		// boost::asio::ip::tcp::resolver�� ����ϱ� ���� ���ø����̼��� �Ű������� ���ǵ� ������ �̸� TCP �ܸ������� ��ȯ�ؾߵȴ�
		tcp::resolver resolver(io_service);	// resolver = ������

		// ���ڴ� Query��� �θ��� boost::asio::ip::tcp::resolver::iterator Ÿ���� �ݺ��ڸ� �̿��ؼ� ��ȯ��.
		auto endpoint_iterator = resolver.resolve( {"127.0.0.1", "2551"} );


		CNet net(io_service, endpoint_iterator);

		thread t([&io_service]() { io_service.run(); });		// ���ٽ�
		char line[chat_message::max_body_length + 1];

		// �޼��� �Է�
		while(cin.getline(line, chat_message::max_body_length + 1))
		{
			chat_message msg;
			msg.body_length(strlen(line));
			memcpy(msg.body(), line, msg.body_length());
			msg.encode_header();
			net.write(msg);	// ����
		}


		net.close();		// ���� �ݱ�
		t.join();		//
	}
	catch(exception& e)
	{
		cerr << "Exception : " << e.what() << "\n";
	}

	return 0;
}
