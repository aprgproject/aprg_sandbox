#include <mysql/mysql.h>

#include <ctime>
#include <string>

class SqlConnect {
public:
    SqlConnect();
    ~SqlConnect();

    bool createTable();
    bool deleteTableIfExist();
    bool write(
        time_t const time, int millisecond, int pulseData, int ecgData, int pulsePerSecond, int bloodOxygen,
        int maxEcgAmplitude);
    unsigned long getTableSize();

private:
    MYSQL *connection;
    MYSQL mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    int query_state;

    const std::string HOST = "localhost";
    const std::string USER = "MuscleControl";
    const std::string PASSWD = "muscles";
    const std::string DB = "HeartTee";
    const std::string TABLE = "HeartInfo";

    bool open();
};
