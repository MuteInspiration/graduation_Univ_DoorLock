#pragma once

#include "common.h"
#include <mysql++.h>

class DB
{

private:
	const char* HOST = "localhost";
	const char* USER;
	const char* PASS;
	const char* DATABASE;

public:
	DB();
	~DB();
};

