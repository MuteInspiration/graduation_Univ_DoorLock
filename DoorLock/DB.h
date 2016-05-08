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
	MYSQL *connection, conn;	// ���� ������ ���� ����
	MYSQL_ROW row;	// db�� ���� �޴� ������
	MYSQL_RES *res;	// ����ڰ� ���� �ֵ��� ������ ������

	char qbuf[160];	// ������ ���� ����

	const char* HOST = "localhost";
	const char* USER;
	const char* PASS;
	const char* DATABASE;

public:
	DB();
	~DB();
};

