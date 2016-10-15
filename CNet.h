/*
���� Boost.Asio Ȯ�忡 ���� �����̴�. ���� ������ ������, �ǹ������� ����� �ϴ� ���� �ƴ�����, 
�� �ٸ� Ȯ���� ���� ��������μ�, �ǿ����� ����� �����Ѵ�.

Boost.Asio�� ���ο� �� ���� �۾��� �߰��ϱ� ���ؼ���, 3���� Ŭ������ �����ؾ� �Ѵ�.

- ���ο� I/O object �� ��Ÿ����, boost::asio::basic_io_object �� ��ӹ��� ��. ���ο� Ȯ���� ����ϴ� �����ڵ��� �� I/O object ���� ����ϰ� �ȴ�.

- boost::asio::io_service::service �� ��ӹ޾�, ���񽺸� ��ǥ�ϴ� Ŭ����. I/O service�� ��ϵż�,
I/O object �κ��� ���ٵǾ�����.  service �� I/O object �� ������ �߿��ѵ�,  
I/O service �� ���� �ν��Ͻ� �� �־��� �ð��� ���� �ϳ����� ����������, �ټ��� I/O object ���� �ϳ��� ���񽺿� �����Ѵ�.

- �ƹ��͵� ��ӹ��� �ʴ� ���� ������ ���� Ŭ����. 
I/O service���� ���� �ϳ��� ���� �ν��Ͻ����� �����ϹǷ�, ���񽺴� ��� I/O object�� ���� ���� Ŭ������ �ν��Ͻ��� �� �� �����Ѵ�.

��� I/O object Ŭ������ ���� ���ø� Ŭ������ �����ȴ�. �׸��� �� I/O object�� ���� Ư���� ���ߵ� ���񽺿� �Բ� �ν��Ͻ�ȭ �ȴ�.
�ν��Ͻ� �� ������ �θ� Ŭ������ boost::asio::basic_io_object �� ���ؼ� I/O service�� �ڵ������� ��ϵȴ�.
������ �̹� ��ϵ� ��쿡�� ���� ���� �ʱ� ������, I/O object�� ���� ���Ǵ� ���񽺵��� I/O service���� �ѹ��� ��ϵȴ�.

I/O object �ȿ��� �ش� ���񽺴� 'service' ������ ���ؼ� ������ �� �ִµ�, �Ϲ������� ���񽺷� �޼��� ȣ���� ������ �ϱ� ���ؼ� �ʿ��ϴ�.

���񽺵��� ��� I/O object �� �����͵��� ������ �ʿ䰡 �ֱ� ������, 'service'�� �̿��ؼ� ��� I/O object�� ���� �ν��Ͻ��� �ڵ����� �����ȴ�. 
�� ���� �θ� Ŭ���� boost::asio::basic_io_object�� �������� �����ϴ�.
���� ���� ����(service implementation)�� ��� �޼��� ȣ�� ��, ù ��° ���ڷ� ���޵Ǵµ� �̸� ���� ���񽺴� � I/O object�� ȣ���ߴ��� �� �� �ִ�. 
���� ������ 'implementation' �Ӽ����� ���� �����ϴ�.

�Ϲ�������, I/O object �� ���� �����ϴ�.
������ ��ġ �� ���� ������ ������ �θ� Ŭ���� boost::asio::basic_io_object�� ���� ����ȴ�.
�޼��� ȣ���� ���� I/O object�� ���� ������ ���ڷ� �ؼ�, �ش� ���񽺷� �ܼ��� ������ �ȴ�.

*/

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
			// �񵿱� ����
			boost::asio::async_connect(socket_, endpoint_iterator,
				boost::bind(&CNet::handle_connect, this,
					boost::asio::placeholders::error));

			doorlock = dl;

			Eratosthenes(numbers, 10000);
			addPrime(primes, numbers);
			 p = getRandomePrime(primes);
			 q = getRandomePrime(primes);

			 while (p != q)
				  q = getRandomePrime(primes);

			  N = p * q;
			  euler = (p - 1) * (q - 1);

			  e = getE(N);
			  d = getD(e, euler);
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
	long N, e, d, N, euler;
	int p, q;
	vector<int> numbers;
	vector<int> primes;
};

float getTemp(Doorlock *status, CDht* dht);
void running(char* ip, char *port);


void Eratosthenes(vector <int> &numbers, int number);
void addPrime(vector <int> &prime, vector <int> &number);
unsigned getRandomePrime(vector <int> &prime);

// ���μҸ� ���ض� 
long getE(const unsigned &euler);
long long getD(const unsigned& e, const unsigned& euler);
long GCD(unsigned u, unsigned v);


vector<unsigned long long>& encryption(char* str, const long &N, const long &e);
vector<char>* decryption(vector<unsigned long long> & v, const long long &d, const long &N);
