#include "DB.h"



DB::DB()
{
	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST,
		DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);

	
}


DB::~DB()
{
}
