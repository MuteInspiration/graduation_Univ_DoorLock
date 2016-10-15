/*
 * CNet.cpp
 *
 *  Created on: 2016. 6. 7.
 *      Author: Mute
 */

#include "CNet.h"



// write(io_service에 등록) -> do_write -> handle_write
void CNet::write(const chat_message& msg)
{
	// 메세지 전송
	io_service_.post(boost::bind(&CNet::do_write, this, msg));
}

// close(io_service에 등록) -> do_close
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
		if (!strncmp(decryption(read_msg_.getData(), ), "open door", 9))
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
						encryption(line, N, e);
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


unsigned long long powMod(int x, int p, int m)
{
	unsigned long long result = 1;

	while (p)
	{
		if (p & 1)
		{
			result = (result * x) % m;
		}

		p = int(p / 2);
		x = fmod(pow(x, 2), m);
	}

	return result;
}



void Eratosthenes(vector <int> &numbers, int number)
{
	int minNumber = sqrt(number);    // minNumber보다 작은 소수 p의 배수를 지워 나간다. 

	numbers[0] = 0;
	numbers[1] = 0;
	for (int i = 2; i <= minNumber; i++)
	{
		if (numbers[i] != 0)
		{
			// 작은 소수 p를 배제
			// 현재 p인 2의 배수들을 배제한다.
			for (int j = i; j <= minNumber; j += i)
			{
				if (j + i > minNumber)
					break;
				numbers[j + i] = 0;
			}

		}
	}
}
void addPrime(vector <int> &prime, vector <int> &number)
{
	for (int i = sqrt(10000) * 2 / 3; i < sqrt(10000); i++)
	{
		if (number[i] != 0)
			prime.push_back(number[i]);
	}
} // 소수가 아닌수는 배제
unsigned getRandomePrime(vector <int> &prime)
{
	auto current = chrono::system_clock::now();
	auto duration = current.time_since_epoch();
	auto millis = chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	mt19937_64 getMt(millis);
	uniform_int_distribution<__int64> uniformDist(0, prime.size() - 1);

	return prime[uniformDist(getMt)];
}

// 서로소를 구해라 
long getE(const unsigned &euler)
{
	//  서로소란 두수의 공약수가 1만이 존재하는 수 즉, 최대 공약수가 1인수

	for (unsigned i = 3; i < euler - 1; i++)
	{
		if (GCD(i, 192) == 1)
			return i;
	}

	return -1;

}
long long getD(const unsigned& e, const unsigned& euler)
{
	unsigned long long retD = 1;
	do
	{
		retD++;
	} while (((retD * e) % euler) != 1);

	return retD;
}
long GCD(unsigned u, unsigned v)
{
	if (v > u)
	{
		unsigned temp = u;

		u = v;
		v = temp;
	}

	auto s1 = 1;
	auto s2 = 0;
	auto t1 = 0;
	auto t2 = 1;
	auto tmp = u;

	while (v)
	{
		auto q = floor(u / v);
		auto r = floor(u % v);
		auto s = s1 - q * s2;
		auto t = t1 - q * t2;

		u = v;
		v = r;
		s1 = s2;
		s2 = s;
		t1 = t2;
		t2 = t;
	}

	if (t1 < 0)
		t1 += tmp;

	return t1;
}


vector<unsigned long long>& encryption(char* str, const long &N, const long &e)
{
	int len = strlen(str);
	vector<unsigned long long>* c = new vector<unsigned long long>;

	cout << " Encryption \n";
	for (int i = 0; i < len; i++)
	{
		double t = powMod((double)str[i], e, N);
		cout << t << endl;

		c->push_back(t);
	}



	return *c;
}
vector<char>* decryption(vector<unsigned long long> &c, const long long &d, const long &N)
{
	int size = c.size() - 1;
	vector<char>* str;
	for (int i = 0; i < size; i++)
	{
		str->push_back(powMod(c[i], d, N));
	}

	return str;
}