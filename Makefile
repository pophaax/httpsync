#######################################################
#
#    Aland Sailing Robot
#    ===========================================
#    HTTP Connection
#    -------------------------------------------
#
#######################################################

CC = g++
FLAGS = -Wall -pedantic -Werror
LIBS = -lcurl

SOURCES_HTTP = HTTPSync.cpp
HEADERS_HTTP = HTTPSync.h
FILE_HTTP = HTTPSync.o

HEADERS = $(HEADERS_HTTP)
SOURCES = $(SOURCES_HTTP)

all : $(FILE_HTTP)

$(FILE_HTTP) : $(SOURCES_HTTP) $(HEADERS_HTTP)
	$(CC) $(SOURCES_HTTP) $(FLAGS) $(LIBS) -c -o $(FILE_HTTP)

example : $(SOURCES) $(HEADERS) example.cpp
	$(CC) $(SOURCES) example.cpp $(FLAGS) $(LIBS) -o example
