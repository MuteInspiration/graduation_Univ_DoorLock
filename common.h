#pragma once

// Need to lboost-system OK
// MySql++ 어캐쓰는건가
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
