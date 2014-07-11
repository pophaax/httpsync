#include "HTTPSync.h"



size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}

HTTPSync::HTTPSync() {
	curl = curl_easy_init();
}

HTTPSync::~HTTPSync() {
	curl_easy_cleanup(curl);
}

void HTTPSync::setShipID(string ID) {
	shipID = ID;
}

void HTTPSync::setShipPWD(string PWD) {
	shipPWD = PWD;
}

void HTTPSync::setServerURL(string URL) {
	serverURL = URL;
}

string HTTPSync::getSetup() {
	return serve("/?serv=getSetup&id="+shipID+"&pwd="+shipPWD);
}

string HTTPSync::getConfig() {
	return serve("/?serv=getConfig&id="+shipID+"&pwd="+shipPWD);
}

string HTTPSync::getRoute() {
	return serve("/?serv=getRoute&id="+shipID+"&pwd="+shipPWD);
}

string HTTPSync::pushLogs(string logs) {
	//string URL = serverURL + serverCall;
	return serve("/?serv=pushLogs&id="+shipID+"&pwd="+shipPWD+"&data="+logs);
}

string HTTPSync::serve(string serverCall) {
	string response = "";
	string url = serverURL + serverCall;
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		//curl_easy_setopt(curl, CURLOPT_POST, 1);
   		//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, serverCall.c_str());
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);
		/* Check for errors */ 
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	}

	return response;
}
