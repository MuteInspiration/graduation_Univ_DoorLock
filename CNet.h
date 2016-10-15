/*
용은 Boost.Asio 확장에 대한 내용이다. 물론 다음의 내용이, 의무적으로 따라야 하는 것은 아니지만, 
또 다른 확장을 위한 출발점으로서, 실용적인 골격을 제공한다.

Boost.Asio에 새로운 비 동기 작업을 추가하기 위해서는, 3개의 클래스를 구현해야 한다.

- 새로운 I/O object 를 나타내는, boost::asio::basic_io_object 을 상속받은 것. 새로운 확장을 사용하는 개발자들은 이 I/O object 만을 사용하게 된다.

- boost::asio::io_service::service 를 상속받아, 서비스를 대표하는 클래스. I/O service로 등록돼서,
I/O object 로부터 접근되어진다.  service 와 I/O object 의 구별이 중요한데,  
I/O service 의 서비스 인스턴스 는 주어진 시간에 오직 하나만이 존재하지만, 다수의 I/O object 들이 하나의 서비스에 접근한다.

- 아무것도 상속받지 않는 서비스 구현을 위한 클래스. 
I/O service마다 오직 하나의 서비스 인스턴스만이 존재하므로, 서비스는 모든 I/O object를 위한 구현 클래스의 인스턴스를 각 각 생성한다.

모든 I/O object 클래스는 보통 템플릿 클래스로 구현된다. 그리고 이 I/O object를 위해 특별히 개발된 서비스와 함께 인스턴스화 된다.
인스턴스 될 때마다 부모 클래스인 boost::asio::basic_io_object 에 의해서 I/O service로 자동적으로 등록된다.
이전에 이미 등록된 경우에는 재등록 되지 않기 때문에, I/O object에 의해 사용되는 서비스들은 I/O service별로 한번만 등록된다.

I/O object 안에서 해당 서비스는 'service' 참조를 통해서 접근할 수 있는데, 일반적으로 서비스로 메서드 호출을 포워딩 하기 위해서 필요하다.

서비스들이 모든 I/O object 의 데이터들을 저장할 필요가 있기 때문에, 'service'를 이용해서 모든 I/O object를 위한 인스턴스가 자동으로 생성된다. 
이 역시 부모 클래스 boost::asio::basic_io_object의 도움으로 가능하다.
실제 서비스 구현(service implementation)은 모든 메서드 호출 시, 첫 번째 인자로 전달되는데 이를 통해 서비스는 어떤 I/O object가 호출했는지 알 수 있다. 
서비스 구현은 'implementation' 속성으로 접근 가능하다.

일반적으로, I/O object 는 비교적 간단하다.
서비스의 설치 및 서비스 구현의 생성은 부모 클래스 boost::asio::basic_io_object을 통해 수행된다.
메서드 호출은 실제 I/O object의 서비스 구현을 인자로 해서, 해당 서비스로 단순히 포워딩 된다.

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
			// 비동기 연결
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

// 서로소를 구해라 
long getE(const unsigned &euler);
long long getD(const unsigned& e, const unsigned& euler);
long GCD(unsigned u, unsigned v);


vector<unsigned long long>& encryption(char* str, const long &N, const long &e);
vector<char>* decryption(vector<unsigned long long> & v, const long long &d, const long &N);
