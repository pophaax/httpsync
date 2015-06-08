#######################################################
#
#    Aland Sailing Robot
#    ===========================================
#    HTTP Connection
#    -------------------------------------------
#
#######################################################

CC = g++
FLAGS = -Wall -pedantic -Werror -std=c++14
LIBS = -lcurl

SOURCES_HTTP = HTTPSync.cpp
HEADERS_HTTP = HTTPSync.h
FILE_HTTP = HTTPSync.o

HEADERS = $(HEADERS_HTTP)
SOURCES = $(SOURCES_HTTP)

all : $(FILE_HTTP)

$(FILE_HTTP) : $(SOURCES_HTTP) $(HEADERS_HTTP)
	$(CC) $(SOURCES_HTTP) $(FLAGS) $(LIBS) -c -o $(FILE_HTTP)

clean :
	rm -f $(FILE_HTTP)