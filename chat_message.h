#pragma once


#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

class chat_message
{
public:
	enum { header_length = 8 };
	enum { max_body_length = 512 };

	chat_message()
		: body_length_(0)
	{
	}

	const char* data() const
	{
		return data_;
	}

	char* data()
	{
		return data_;
	}

	size_t length() const
	{
		return header_length + body_length_;
	}

	const char* body() const
	{
		return data_;
	}

	char* body()
	{
		memset(data_, '\0', max_body_length);
		return data_;
	}

	char *getData()
	{
		return data_;
	}

	size_t body_length() const
	{
		return body_length_;
	}

	void body_length(size_t new_length)
	{
		body_length_ = new_length;
		if (body_length_ > max_body_length)
			body_length_ = max_body_length;
	}

	bool decode_header()
	{
		using namespace std; // For strncat and atoi.
		char header[header_length + 1] = "";
		memset(header, '\0', header_length + 1);

		strncat(header, data_, header_length);
		body_length_ = strlen(header);

		strcpy(data_, header);
		if (body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}
		return true;
	}

	void encode_header()
	{
		using namespace std; // For sprintf and memcpy.
		char header[header_length + 1] = "";	// header[5] 에 아무것도 안넣음.
		sprintf(header, "%4d", static_cast<int>(body_length_));
		memcpy(header, data_,  header_length);
	}

private:
	char data_[header_length + max_body_length];
	size_t body_length_;
};

#endif // CHAT_MESSAGE_HPP
