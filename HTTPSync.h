#ifndef __HTTPSYNC_H__
#define __HTTPSYNC_H__

#include "../dbhandler/DBHandler.h"
#include "../logger/Logger.h"
#include "models/SystemStateModel.h"

#include <chrono>
#include <thread>
#include <curl/curl.h>
#include <string>
#include <mutex>


class HTTPSync {

	public:

		HTTPSync(DBHandler *db,int delay);
		~HTTPSync();

		void run();
		void setupHTTPSync();
		void syncServer();
		void updateState();
		void pushWaypoints();

		void setShipID(std::string shipID);
		void setShipPWD(std::string shipPWD);
		void setServerURL(std::string URL);

		std::string getSetup();
		std::string getConfig();
		std::string getRoute();

		std::string pushData(std::string data, std::string call);
		std::string getConfigs(std::string config);
		void updateConfigs();
		bool checkIfNewConfig();

	private:

		CURL *curl;
		CURLcode res;

		std::string shipID;
		std::string shipPWD;
		std::string serverURL;
		bool m_running;
		Logger m_logger;
		std::mutex m_mutex;
		int m_delay;

		DBHandler *m_dbHandler;

		std::string serve(std::string serverCall);

		bool isRunning();
		void close();
};

#endif
