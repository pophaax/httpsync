#include "HTTPSync.h"
#include "JSON.h"
#include <iostream>

using namespace std;

// Compile with this:
// g++ -lcurl client.cpp httpconnection.cpp JSONBlock.cpp JSONArray.cpp JSONData.cpp
int main() {

	HTTPSync conn;
	conn.setShipID("SHIP_ID");
	conn.setShipPWD("PASSWORD");
	conn.setServerURL("SERVER_URL");
	cout << "---------------------------------------------------------" << endl;
	cout << conn.getConfig() << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << conn.getRoute() << endl;
	cout << "---------------------------------------------------------" << endl;
	
	JSONArray logs;
	logs.setName("datalogs");
	
	JSONArray messages;
	messages.setName("messages");
	

	for(int i = 0; i < 2; i++) {
		JSONData data;				//Create data object and insert data
		data.add("id",1);
		data.add("gps_time","2014-06-06 11:11:11");
		data.add("gps_lat",60.3231);
		data.add("gps_lon",20.0011);
		data.add("gps_spd",30);
		data.add("gps_head",30);
		data.add("gps_sat",30);
		data.add("sc_cmd",6000);
		data.add("rc_cmd",6000);
		data.add("ss_pos",6000);
		data.add("rs_pos",6000);
		data.add("cc_dtw",80);
		data.add("cc_btw",60);
		data.add("cc_cts",130);
		data.add("cc_tack",0);
		data.add("ws_dir",280);
		data.add("ws_spd",3);
		data.add("ws_tmp",25);
		data.add("cfg_rev","cfg0001");
		data.add("rte_rev","rte0001");
		data.add("wpt_cur",3);
		data.add("wpt_rev","wpt0001");
		JSONBlock blck;				//Create block object and insert data object
		blck.add(data.toString());
		logs.add(blck.toString());	//Insert data block into array
	}

	for(int i = 0; i < 2; i++) {
		JSONData data;
		data.add("id",1);
		data.add("gps_time","2014-06-06 11:11:11");
		data.add("type","error");
		data.add("msg","msg1");
		data.add("log_id",1);
		JSONBlock blck; 
		blck.add(data.toString());
		messages.add(blck.toString());
	}

	JSONBlock main;					//Insert arrays in another block before sending
	main.add(logs.toString());
	main.add(messages.toString());

	cout << conn.pushLogs(main.toString()) << endl;
	cout << "---------------------------------------------------------" << endl;
}