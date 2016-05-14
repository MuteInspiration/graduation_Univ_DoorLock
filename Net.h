#pragma once

#include "common.h"
#include "Doorlock.h"
#include "Dht.h"
#include "CHAT_MESSAGE.hpp"

// Node.js와 송수신한다. TCP 소켓으로
// Node.js가 서버역할
// C++ 파트는 클라이언트 역할
// DHT에서 응급신호가 날라오면  Node.js로 넘겨준다.(inner.js)
// 문열기, 닫기 신호가 날라오면 처리함.


using boost::asio::ip::tcp;
typedef deque<chat_message> chat_message_queue;


class CNet
{
private:
	string address;
	string port;

	bool isEmergency;

	boost::asio::io_service& io_service_;
	tcp::socket socket_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;

	void do_connect(tcp::resolver::iterator endpoint_iterator);
	void do_read_header();
	void do_write();
	void do_read_body();

public:
	CNet(boost::asio::io_service& io_service,
			tcp::resolver::iterator endpoint_iterator);
	~CNet();

	void write(const chat_message &msg);
	void close();



};

