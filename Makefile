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

SOURCES_JSON = JSONBlock.cpp JSONArray.cpp JSONData.cpp
HEADERS_JSON = JSONBlock.h JSONArray.h JSONData.h IEncoder.h
FILE_JSON = JSON.o

SOURCES_HTTP = HTTPConnection.cpp
HEADERS_HTTP = HTTPConnection.h
FILE_HTTP = HTTP.o

HEADERS = $(HEADERS_JSON) $(HEADERS_HTTP)
SOURCES = $(SOURCES_JSON) $(SOURCES_HTTP)

all : $(FILE_JSON) $(FILE_HTTP)

$(FILE_JSON) : $(SOURCES_JSON) $(HEADERS_JSON)
	$(CC) $(SOURCES_JSON) $(FLAGS) $(LIBS) -c -o $(FILE_JSON)

$(FILE_HTTP) : $(SOURCES_HTTP) $(HEADERS_HTTP)
	$(CC) $(SOURCES_HTTP) $(FLAGS) $(LIBS) -c -o $(FILE_HTTP)

example : $(SOURCES) $(HEADERS) example.cpp
	$(CC) $(SOURCES) example.cpp $(FLAGS) $(LIBS) -o example
