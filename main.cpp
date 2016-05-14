#include "common.h"
#include "Net.h"
#include <string>

/*

		스마트 디지털 도어락 개발일지

		16.04.08 Dht 송수신, 문열림 닫힘신호
		16.05.12 boost Library 설치 완료. - Socket을 통해 안드로이드와 통신예정
				  SHA-1 SALT 방식
		16.05.13  Node.js 미들서버로 도입예정 -> 이 C++ App에서 Node.js 동시 실행해줄예정.
		 outer.js를 실행 -> 만약 중간에 에러로 꺼지면??? 아직 방도 없음.
*/



int main(void)
{
	wiringPiSetup();
	
	try
	{
		//asio를 사용하는 모든 프로그램은 적어도 하나이상의 boost::asio::io_service 객체가 필요함
		boost::asio::io_service io_service;
		// boost::asio::ip::tcp::resolver를 사용하기 위해 어플리케이션의 매개변수로 정의된 서버의 이름 TCP 단말점으로 변환해야된다
		tcp::resolver resolver(io_service);	// resolver = 결정자

		// 인자는 Query라고 부르며 boost::asio::ip::tcp::resolver::iterator 타입의 반복자를 이용해서 반환됨.
		auto endpoint_iterator = resolver.resolve( {"127.0.0.1", "2551"} );


		CNet net(io_service, endpoint_iterator);

		thread t([&io_service]() { io_service.run(); });		// 람다식
		char line[chat_message::max_body_length + 1];

		// 메세지 입력
		while(cin.getline(line, chat_message::max_body_length + 1))
		{
			chat_message msg;
			msg.body_length(strlen(line));
			memcpy(msg.body(), line, msg.body_length());
			msg.encode_header();
			net.write(msg);	// 전송
		}


		net.close();		// 연결 닫기
		t.join();		//
	}
	catch(exception& e)
	{
		cerr << "Exception : " << e.what() << "\n";
	}

	return 0;
}
