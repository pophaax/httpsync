
#include "HTTPSync.h"



size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
 ((std::string*)stream)->append((char*)ptr, 0, size*count);
 return size*count;
}



HTTPSync::HTTPSync(DBHandler *db) : m_dbHandler(db)
{
  m_running = true;
  curl = curl_easy_init();
}

HTTPSync::~HTTPSync() {
 curl_easy_cleanup(curl);
}


/* --------------------- taken from sailingrobot ------------------------ */


void HTTPSync::run()
{
 std::cout << "HTTPSync thread started." << std::endl;
 m_logger.info("HTTPSync thread started.");
 setupHTTPSync();
 // updateState();
 pushWaypoints();

 while(isRunning())
 {
   syncServer();
  //  std::this_thread::sleep_for(
  //    std::chrono::milliseconds(1000));
 }

 std::cout << "HTTPSync thread exited." << std::endl;
 m_logger.info("HTTPSync thread exited.");
}

void HTTPSync::setupHTTPSync() {
 try {
   setShipID( m_dbHandler->retriveCell("server", "1", "boat_id") );
   setShipPWD( m_dbHandler->retriveCell("server", "1", "boat_pwd") );
   setServerURL( m_dbHandler->retriveCell("server", "1", "srv_addr") );
 } catch (const char * error) {
   m_logger.error("SailingRobot::setupHTTPSync() failed");
 }
 m_logger.info("setupHTTPSync() done");
}

void HTTPSync::syncServer() {
 try {
   m_dbHandler->getWaypoints();
   // can fetch server response from pushLog
   pushData(m_dbHandler->getLogs(), "pushAllLogs");

   // clearing the datalogs after push.
   m_dbHandler->clearDatalogTables();
 } catch (const char * error) {
    m_logger.error("Error in HTTPSync::syncserver");
 }
}

void HTTPSync::updateState() {
 try {
   std::string setup = getSetup();
   bool stateChanged = false;
   if (m_dbHandler->revChanged("cfg_rev", setup) ) {
     m_dbHandler->updateTable("configs", getConfig());
     stateChanged = true;
     m_logger.info("config state updated");
   }
   if (m_dbHandler->revChanged("rte_rev", setup) ) {
     m_dbHandler->updateTable("waypoints", getRoute());
     stateChanged = true;
     m_logger.info("route state updated");
   }
   if (stateChanged)  {
     m_dbHandler->updateTable("state", getSetup());
   }
 } catch (const char * error) {
   m_logger.error(error);
 }
}

void HTTPSync::pushWaypoints() {
 int rows = 0;
 try {
   rows = m_dbHandler->getRows("waypoints");
 } catch(const char * error) {
   m_logger.error("Error in HTTPSync::pushWaypoints when fetching rows");
 }
 for (auto i = 0; i < rows; ++i) {
   try {
     pushData(m_dbHandler->getWaypoints(), "pushWaypoints");
   } catch(const char* error) {
     m_logger.error("Error in HTTPSync::pushWaypoints when pushing data");
   }
 }

}

void HTTPSync::setShipID(std::string ID) {
  shipID = ID;
}

void HTTPSync::setShipPWD(std::string PWD) {
  shipPWD = PWD;
}

void HTTPSync::setServerURL(std::string URL) {
  serverURL = URL;
}

std::string HTTPSync::getSetup() {
  return serve("/?serv=getSetup&id="+shipID+"&pwd="+shipPWD);
}

std::string HTTPSync::getConfig() {
  return serve("/?serv=getConfig&id="+shipID+"&pwd="+shipPWD);
}

std::string HTTPSync::getRoute() {
  return serve("/?serv=getRoute&id="+shipID+"&pwd="+shipPWD);
}

std::string HTTPSync::getConfigs(std::string config) {
  return serve("/?serv=get" + config + "&id="+shipID+"&pwd="+shipPWD);
}

std::string HTTPSync::pushData(std::string data, std::string call) {
  return serve("/?serv=" + call + "&id="+shipID+"&pwd="+shipPWD+"&data="+data);
}

std::string HTTPSync::serve(std::string serverCall) {
 std::string response = "";
 std::string url = serverURL + serverCall;
 // std::cout << url << std::endl;
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
     throw ( std::string("HTTPSync::serve(): ") + curl_easy_strerror(res) ).c_str();
 }

 return response;
}

bool HTTPSync::isRunning()
{
 bool running;
 m_mutex.lock();
 running = m_running;
 m_mutex.unlock();
 return running;
}

void HTTPSync::close()
{
 m_mutex.lock();
 m_running = false;
 m_mutex.unlock();
}
