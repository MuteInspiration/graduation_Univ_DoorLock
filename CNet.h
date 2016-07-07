

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include "COMMON.h"
#include "chat_message.h"
#include "Doorlock.h"
#include "Dht.h"

using boost::asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;


class CNet
{
public:
	CNet(boost::asio::io_service& io_service,
			tcp::resolver::iterator endpoint_iterator, Doorlock *dl)
			: io_service_(io_service),
			socket_(io_service)
		{
			// 비동기 연결
			boost::asio::async_connect(socket_, endpoint_iterator,
				boost::bind(&CNet::handle_connect, this,
					boost::asio::placeholders::error));

			doorlock = dl;
		}

	void write(const chat_message& msg);
	void close();
	bool isRun() { return isrun; }
	void setIpPort(char *ip, char *port)
	{
		strcpy(ipaddress, ip);
		strcpy(this->port, port);
	}

private:

	void handle_connect(const boost::system::error_code& error);
	void handle_read(const boost::system::error_code& error);
	void do_write(chat_message msg);
	void handle_write(const boost::system::error_code& error);
	void do_close();

private:
	boost::asio::io_service& io_service_;
	tcp::socket socket_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;
	Doorlock * doorlock;
	bool isrun = false;

	char * ipaddress;
	char * port;
};

float getTemp(Doorlock *status, CDht* dht);
void running(char* ip, char *port);

