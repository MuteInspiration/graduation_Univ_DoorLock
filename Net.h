#pragma once

#include "common.h"
#include "Doorlock.h"
#include "Dht.h"
#include "CHAT_MESSAGE.hpp"

// Node.js�� �ۼ����Ѵ�. TCP ��������
// Node.js�� ��������
// C++ ��Ʈ�� Ŭ���̾�Ʈ ����
// DHT���� ���޽�ȣ�� �������  Node.js�� �Ѱ��ش�.(inner.js)
// ������, �ݱ� ��ȣ�� ������� ó����.


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

