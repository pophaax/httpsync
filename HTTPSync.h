#ifndef __HTTPSYNC_H__
#define __HTTPSYNC_H__

#include <stdio.h>
#include <curl/curl.h>
#include <string>
#include <iostream>

using namespace std;



class HTTPSync {
	
	public:

		HTTPSync();
		~HTTPSync();

		void setShipID(string shipID);
		void setShipPWD(string shipPWD);
		void setServerURL(string URL);

		string checkUpdates();

		string getConfig();
		string getRoute();

		string pushLogs(string logs);

	private:

		CURL *curl;
		CURLcode res;

		string shipID;
		string shipPWD;
		string serverURL;

		string serve(string serverCall);
};

#endif