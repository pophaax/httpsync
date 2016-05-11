
#include "HTTPSync.h"



size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
    ((std::string*)stream)->append((char*)ptr, 0, size*count);
    return size*count;
}



HTTPSync::HTTPSync(DBHandler *db,int delay) : m_dbHandler(db) {
    m_running = true;
    curl = curl_easy_init();
    m_delay = delay;
}

HTTPSync::~HTTPSync() {
    curl_easy_cleanup(curl);
}


/* --------------------- taken from sailingrobot ------------------------ */


void HTTPSync::run() {
    std::cout << "HTTPSync thread started." << std::endl;
    m_logger.info("HTTPSync thread started.");
    setupHTTPSync();
    // updateState();
    // pushConfigs();
    pushWaypoints();

    while(isRunning())
    {
        //updateConfigs();
        syncServer();
        std::this_thread::sleep_for(std::chrono::milliseconds(m_delay));
    }

    std::cout << "HTTPSync thread exited." << std::endl;
    m_logger.info("HTTPSync thread exited.");
}

void HTTPSync::setupHTTPSync() {
    try {
        setShipID( m_dbHandler->retrieveCell("server", "1", "boat_id") );
        setShipPWD( m_dbHandler->retrieveCell("server", "1", "boat_pwd") );
        setServerURL( m_dbHandler->retrieveCell("server", "1", "srv_addr") );
    } catch (const char * error) {
        m_logger.error("SailingRobot::setupHTTPSync() failed");
    }
    m_logger.info("setupHTTPSync() done");
}

void HTTPSync::syncServer() {
    try {
        // can fetch server response from pushLog
        pushData(m_dbHandler->getLogs(), "pushAllLogs");

        // clearing the datalogs after push.
        m_dbHandler->clearDatalogTables();
    } catch (const char * error) {
        //  m_logger.error("Error in HTTPSync::syncserver");
        //  m_logger.error(std::string(error));
    }
}

void HTTPSync::pushWaypoints() {
   try {
     pushData(m_dbHandler->getWaypoints(), "pushWaypoints");
   } catch(const char* error) {
     m_logger.error("Error in HTTPSync::pushWaypoints ");
   }
}

void HTTPSync::pushConfigs() {
    try {
        pushData(m_dbHandler->getConfigs(), "pushConfigs");
        m_logger.info("Configs pushed to server");
    } catch(const char* error) {
        m_logger.error("Error in HTTPSync::pushWaypoints ");
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


std::string HTTPSync::getConfigs(std::string config) {
    return serve("/?serv=get" + config + "&id=" + shipID + "&pwd=" + shipPWD);
}

std::string HTTPSync::pushData(std::string data, std::string call) {
    return serve("/?serv=" + call + "&id="+shipID+"&pwd="+shipPWD+"&data="+data);
}

bool HTTPSync::checkIfNewConfig() {
    if (serve("/?serv=checkIfNewConfigs&id=" + shipID + "&pwd=" + shipPWD) == "1")
        return true;

    return false;
}

void HTTPSync::updateConfigs() {
    // std::cout << checkIfNewConfig() << std::endl;
    if(checkIfNewConfig()) {
        std::string configs = getConfigs("AllConfigs");
        m_dbHandler->updateConfigs(configs);
        m_dbHandler->updateTable("state", "configsUpdated", "1","1");
        pushConfigs();
    }
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

bool HTTPSync::isRunning() {
    bool running;
    m_mutex.lock();
    running = m_running;
    m_mutex.unlock();
    return running;
}

void HTTPSync::close() {
    m_mutex.lock();
    m_running = false;
    m_mutex.unlock();
}
