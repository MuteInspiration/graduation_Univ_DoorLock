#pragma once

// Need to lboost-system OK
// MySql++ ��ĳ���°ǰ�
#include <wiringPi.h>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>

#include <deque>
#include <thread>
#include <boost/asio.hpp>

using namespace std;

#define DHT_PIN 5		// GPIO5
#define RELAY_PIN 4		// GPIO4
#define DECT_PIN 8		// GPIO6
