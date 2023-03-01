#include "SqlConnect.hpp"

#include <iostream>
#include <sstream>

using namespace std;

SqlConnect::SqlConnect()
	: connection(nullptr)
        , mysql()
        , result(nullptr)
        , query_state(0)
{
	open();
}

SqlConnect::~SqlConnect()
{
	if(connection != nullptr)
	{
		mysql_close(&mysql);
	}
}

bool SqlConnect::open()
{
	bool status = true;
	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql,
                                                                    HOST.c_str(),
                                                                    USER.c_str(),
                                                                    PASSWD.c_str(),
                                                                    DB.c_str(),
                                                                    0,0,0); 
	if (connection == NULL) {
		cout << mysql_error(&mysql) << "\n";
 		status = false;
 	}
	return status;}

bool SqlConnect::write(time_t const time,
			   int millisecond,                           int pulseData,
                           int ecgData,
                           int pulsePerSecond,
                           int bloodOxygen,
                           int maxEcgAmplitude)
{
	char buff[20];
        strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&time));
	string timeBuffer(buff);

	stringstream query;
	query << "INSERT INTO " << TABLE;
	query << " SET dateTime='" << timeBuffer << "', ";
	query << "millisecond='" << millisecond << "', ";
	query << "PulseAmp='" << pulseData << "', ";
	query << "EcgAmp='" << ecgData << "', ";
	query << "PulseAverage='" << pulsePerSecond << "', ";
	query << "OxygenAverage='" << bloodOxygen << "', ";
	query << "EcgMaxAmp='" << maxEcgAmplitude << "' ";

	query_state = mysql_query(connection, query.str().c_str());
        result = mysql_store_result(connection);

	if(result != NULL)
	{
		return true;
	}
	return false;
}

unsigned long SqlConnect::getTableSize()
{
	unsigned long rowCount = 0;
	std::string query = "SELECT COUNT(*) FROM " + TABLE;
	query_state = mysql_query(connection, query.c_str());
        result = mysql_store_result(connection);
	if(result != NULL)
	{
		while ( ( row = mysql_fetch_row(result)) != NULL ) {
			rowCount = atoi(row[0]);
		}
	}
	return rowCount;
}

bool SqlConnect::createTable()
{
	stringstream query;
	query << "CREATE TABLE " << TABLE << " ( "
		   << "`id` int(10) unsigned NOT NULL AUTO_INCREMENT, "
		   << "`dateTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00', "
		   << "`millisecond` int(10) unsigned NOT NULL DEFAULT '0', "
		   << "`PulseAmp` int(11) NOT NULL DEFAULT '0', "
		   << "`EcgAmp` int(11) NOT NULL DEFAULT '0', "
		   << "`PulseAverage` int(10) unsigned NOT NULL DEFAULT '0', "
		   << "`OxygenAverage` int(10) unsigned NOT NULL DEFAULT '0', "
		   << "`EcgMaxAmp` int(11) NOT NULL DEFAULT '0', "
		   << "PRIMARY KEY (`id`) "
		   << ") ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=latin1";

	query_state = mysql_query(connection, query.str().c_str());
        result = mysql_store_result(connection);
	if(result != NULL)
	{
		return true;
	}
	return false;
}

bool SqlConnect::deleteTableIfExist()
{
	std::string query = "DROP TABLE IF EXISTS " + TABLE;
	query_state = mysql_query(connection, query.c_str());
        result = mysql_store_result(connection);
	if(result != NULL)
	{
		return true;
	}
	return false;
}
