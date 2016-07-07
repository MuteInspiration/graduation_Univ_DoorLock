/*
 * CNet.cpp
 *
 *  Created on: 2016. 6. 7.
 *      Author: Mute
 */

#include "CNet.h"




void CNet::write(const chat_message& msg)
{
	// 메세지 전송
	io_service_.post(boost::bind(&CNet::do_write, this, msg));
}

void CNet::close()
{
	io_service_.post(boost::bind(&CNet::do_close, this));
}

void CNet::handle_connect(const boost::system::error_code& error)
{
	if (!error)
	{
		isrun = true;
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), chat_message::header_length),
			boost::bind(&CNet::handle_read, this,
					boost::asio::placeholders::error));
	} else {
		isrun = false;
		cout << "Failed to Connnect, Retry Connect" << endl;
		delay(2000);
		running(ipaddress, port);

	}
}
void CNet::handle_read(const boost::system::error_code& error)
{
	if (!error && read_msg_.decode_header())
	{
		if (!strncmp(read_msg_.getData(), "open door", 9))
		{
			cout << "Successfully receive from Middle Server, Message : open door\n";
			doorlock->OpenDoor();

			char line[chat_message::max_body_length + 1];
			chat_message msg;
			strcpy(line, "door opened");
			msg.body_length(strlen(line));
			memcpy(msg.body(), line, msg.body_length());  // msg.body()에 line을 msg.body_length()만큼 복사
			msg.encode_header();
			write(msg);
		}

		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
			boost::bind(&CNet::handle_read, this,
				boost::asio::placeholders::error));
	}
	else
	{
		isrun = false;
		cout << "Failed to Connnect, Retry Connect" << endl;
		delay(2000);
		running(ipaddress, port);
	}
}


void CNet::do_write(chat_message msg)
{
	bool write_in_progress = !write_msgs_.empty();
	write_msgs_.push_back(msg);
	if (!write_in_progress)
	{
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().data(),
				write_msgs_.front().length()),
			boost::bind(&CNet::handle_write, this,
				boost::asio::placeholders::error));
	}
}


void CNet::handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			write_msgs_.pop_front();
			if (!write_msgs_.empty())
			{
				boost::asio::async_write(socket_,
					boost::asio::buffer(write_msgs_.front().data(),
						write_msgs_.front().length()),
					boost::bind(&CNet::handle_write, this,
						boost::asio::placeholders::error));
			}
		}
		else
		{
			isrun = false;
			cout << "Failed to Connnect, Retry Connect" << endl;
			delay(2000);
			running(ipaddress, port);
		}
	}

void CNet::do_close()
{
	socket_.close();
}


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

		if(avg > 0)
			return avg;
		else
			return getTemp(status, dht);
	}
}

void running(char *ip , char *port)
{
	try{
		Doorlock dl;
		CDht dht;

		boost::asio::io_service io_service;
		// 입력 받은 host을 resolving한다.
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(ip, port);
		tcp::resolver::iterator iterator = resolver.resolve(query);


		CNet c(io_service, iterator, &dl);

		boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

		char line[chat_message::max_body_length + 1];


		while (1)
		{

			float temp = getTemp(&dl, &dht);
				cout << "Temper is now : " << temp << "\n";
				if(c.isRun() == true)
				{
					// 여기서 온도 체킹후 전송합니다 warning
					if(temp >= 45)
					{
						dl.OpenDoor();
						cout << "Warning\n\a";
						chat_message msg;
						strcpy(line, "temper warning");
						msg.body_length(strlen(line));
						memcpy(msg.body(), line, msg.body_length());  // msg.body()에 line을 msg.body_length()만큼 복사
						msg.encode_header();
						c.write(msg);
					}
				}

			delay(2000);
		}


		c.close();
		t.join();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

}
