#include "HTTPSync.h"
#include <iostream>


int main() {

	HTTPSync conn;
	conn.setShipID("SHIP_ID");
	conn.setShipPWD("PASSWORD");
	conn.setServerURL("SERVER_URL");
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << conn.getSetup() << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << conn.getConfig() << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << conn.getRoute() << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
}

