#ifndef __HTTPSYNC_H__
#define __HTTPSYNC_H__

#include <curl/curl.h>
#include <string>


class HTTPSync {
	
	public:

		HTTPSync();
		~HTTPSync();

		void setShipID(std::string shipID);
		void setShipPWD(std::string shipPWD);
		void setServerURL(std::string URL);

		std::string getSetup();
		std::string getConfig();
		std::string getRoute();

		std::string pushLogs(std::string logs);

	private:

		CURL *curl;
		CURLcode res;

		std::string shipID;
		std::string shipPWD;
		std::string serverURL;

		std::string serve(std::string serverCall);
};

#endif