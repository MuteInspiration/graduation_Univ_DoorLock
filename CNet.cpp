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
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), chat_message::header_length),
			boost::bind(&CNet::handle_read, this,
					boost::asio::placeholders::error));
	}
}
void CNet::handle_read(const boost::system::error_code& error)
{
	if (!error && read_msg_.decode_header())
	{
		//	이 read_msg_.getData에서 가져온값이 opendoor면 문을 연다.
		//std::cout.write(read_msg_.getData(), read_msg_.body_length());
		//std::cout << "\n";

		if (!strncmp(read_msg_.getData(), "dooropen", read_msg_.body_length()))
		{
			doorlock->OpenDoor();
		}

		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
			boost::bind(&CNet::handle_read, this,
				boost::asio::placeholders::error));
	}
	else
	{
		do_close();
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
			do_close();
		}
	}

void CNet::do_close()
{
	socket_.close();
}
