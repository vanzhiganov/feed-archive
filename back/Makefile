# location of the Python header files
PYTHON_VERSION = 3.11
PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)

# location of the Boost Python include files and library
BOOST_INC = /usr/include/boost/
BOOST_LIB = /usr/lib/

MYSQL_INC = /usr/include/mysql-cppconn-8/jdbc/

MYSQL_CONCPP_DIR = /usr
LDLIBS = $(MYSQL_CONCPP_DIR)/lib64/libmysqlcppconn8-static.a -lssl -lcrypto -lpthread
CPPFLAGS = -DSTATIC_CONCPP -I $(MYSQL_CONCPP_DIR)/include
CXXFLAGS = -std=c++17

#compile mesh classes
TARGET = gateway_back
COTARGET = get_latest_mysql

.PHONY: all clean

all: $(TARGET).so

clean:
	rm -rf *.o;
	rm $(TARGET).so

# (!!!) breaked the string for good formatting @ askubuntu
# important: linking against boost.python, python and connector/c++
# order might be crucial: had to place -lmysqlcppconn at the end
$(TARGET).so: $(TARGET).o $(COTARGET).o
	g++ -shared -Wl,--export-dynamic $(TARGET).o $(COTARGET).o \
	-L$(BOOST_LIB) -lboost_python311 \
	-L/usr/lib/python$(PYTHON_VERSION)/config \
	-lpython$(PYTHON_VERSION) -o $(TARGET).so -lmysqlcppconn
# 	-I${MYSQL_INC} -I${CPPCONN_INC} \

# (!!!) breaked the string for good formatting @ askubuntu
# important: boost and python includes
$(TARGET).o: $(TARGET).cpp $(COTARGET).cpp
	g++ $(CXXFLAGS) \
	-I$(MYSQL_INC) \
	-I$(PYTHON_INCLUDE) \
	-I$(BOOST_INC) -fPIC -c \
	-lmysqlcppconn8 \
	$(TARGET).cpp $(COTARGET).cpp
