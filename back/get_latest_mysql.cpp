#include <stdlib.h>
#include <iostream>
#include <string>
#include <boost/python.hpp>

#include <mysql_driver.h>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

char const* get_latest(std::string feedId)
try {
  sql::Driver *driver;
  sql::Connection *con;
  // sql::Statement *stmt;
  sql::PreparedStatement *prpstmt;
  sql::ResultSet *res;

  /* Create a connection */
  driver = get_driver_instance();

  // MySQL IP address and your username
  con = driver->connect("tcp://db:3306", "user", "password");
  /* Connect to the MySQL test database */
  con->setSchema("archive"); //your db name

  // stmt = con->createStatement();
  // res = stmt->executeQuery("SELECT * from feeds where alias=?;");
  prpstmt = con->prepareStatement("SELECT id, content FROM archive WHERE id IN (SELECT archive_id FROM `latest` WHERE feed_id IN (SELECT id FROM feeds WHERE alias = ?))  LIMIT 1;");
  prpstmt->setString(1, feedId);
  // prpstmt->set
  res = prpstmt->executeQuery();

  string result;

  while (res->next()) {
    /* Access column data by alias or column name */
    // field in db with actual 'content'
    result = res->getString("content");
    return result.c_str();
  }
  con->close();
  delete res;
  delete prpstmt;
  delete con;

} catch (sql::SQLException &e) {
  cerr << "# ERR: SQLException in " << __FILE__;
  cerr << "(" << __FUNCTION__ << ") on line "
     << __LINE__ << endl;
  cerr << "# ERR: " << e.what();
  cerr << " (MySQL error code: " << e.getErrorCode();
  cerr << ", SQLState: " << e.getSQLState() << " )" << endl;
}