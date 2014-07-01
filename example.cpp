#include "HTTPSync.h"
#include <iostream>

using namespace std;

int main() {

	HTTPSync conn;
	conn.setShipID("SHIP_ID");
	conn.setShipPWD("PASSWORD");
	conn.setServerURL("SERVER_URL");
	cout << "---------------------------------------------------------" << endl;
	cout << conn.getSetup() << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << conn.getConfig() << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << conn.getRoute() << endl;
	cout << "---------------------------------------------------------" << endl;
}

