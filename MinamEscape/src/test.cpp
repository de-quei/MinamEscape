/*#include <mysql_driver.h>
#include <mysql_connection.h>

using namespace sql;
using namespace std;

int main() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "username", "password");

    // 데이터베이스 선택
    con->setSchema("database_name");

    // 쿼리 실행
    Statement* stmt = con->createStatement();
    ResultSet* res = stmt->executeQuery("SELECT * FROM table_name");

    while (res->next()) {
        cout << "Column1: " << res->getString(1) << endl;
        cout << "Column2: " << res->getString(2) << endl;
    }

    delete res;
    delete stmt;
    delete con;

    return 0;
}*/
