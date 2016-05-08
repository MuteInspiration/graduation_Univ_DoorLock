#pragma once

#include "common.h"
#include <mysql/mysql.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "rasproot"
#define DB_NAME "test"
#define CHOP(x) x[strlen(x) - 1] = ' '

class DB
{
private:
	MYSQL *connection, conn;	// 연결 설정을 위한 변수
	MYSQL_ROW row;	// db로 부터 받는 데이터
	MYSQL_RES *res;	// 사용자가 볼수 있도록 가동된 데이터

	char qbuf[160];	// 쿼리를 위한 버퍼

	const char* HOST = "localhost";
	const char* USER;
	const char* PASS;
	const char* DATABASE;

public:
	DB();
	~DB();
};

