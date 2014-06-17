#include "HTTPSync.h"
#include "JSON.h"
#include <iostream>

using namespace std;

// Compile with this:
// g++ -lcurl client.cpp httpconnection.cpp JSONBlock.cpp JSONArray.cpp JSONData.cpp
int main() {

	HTTPConnection conn;
	conn.setShipID("SHIP_ID");
	conn.setShipPWD("PASSWORD");
	conn.setServerURL("SERVER_URL");
	cout << "---------------------------------------------------------" << endl;
	cout << conn.getConfig() << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << conn.getRoute() << endl;
	cout << "---------------------------------------------------------" << endl;
	
	JSONData data1;
	data1.add("id",1);
	data1.add("gps_time","2014-06-06 11:11:11");
	data1.add("gps_lat",60.3231);
	data1.add("gps_lon",20.0011);
	data1.add("gps_spd",30);
	data1.add("gps_head",30);
	data1.add("gps_sat",30);
	data1.add("sc_cmd",6000);
	data1.add("rc_cmd",6000);
	data1.add("ss_pos",6000);
	data1.add("rs_pos",6000);
	data1.add("cc_dtw",80);
	data1.add("cc_btw",60);
	data1.add("cc_cts",130);
	data1.add("cc_tack",0);
	data1.add("ws_dir",280);
	data1.add("ws_spd",3);
	data1.add("ws_tmp",25);
	data1.add("cfg_rev","cfg0001");
	data1.add("rte_rev","rte0001");
	data1.add("wpt_cur",3);
	data1.add("wpt_rev","wpt0001");

	JSONData data2;
	data2.add("id",2);
	data2.add("gps_time","2014-06-06 12:12:12");
	data2.add("gps_lat",60.3231);
	data2.add("gps_lon",20.0011);
	data2.add("gps_spd",30);
	data2.add("gps_head",30);
	data2.add("gps_sat",30);
	data2.add("sc_cmd",7000);
	data2.add("rc_cmd",5000);
	data2.add("ss_pos",5000);
	data2.add("rs_pos",7000);
	data2.add("cc_dtw",50);
	data2.add("cc_btw",70);
	data2.add("cc_cts",150);
	data2.add("cc_tack",1);
	data2.add("ws_dir",310);
	data2.add("ws_spd",4);
	data2.add("ws_tmp",26);
	data2.add("cfg_rev","cfg0002");
	data2.add("rte_rev","rte0002");
	data2.add("wpt_cur",4);
	data2.add("wpt_rev","wpt0002");

	JSONData data3;
	data3.add("id",1);
	data3.add("gps_time","2014-06-06 11:11:11");
	data3.add("type","error");
	data3.add("msg","msg1");
	data3.add("log_id",1);

	JSONData data4;
	data4.add("id",2);
	data4.add("gps_time","2014-06-06 12:12:12");
	data4.add("type","warning");
	data4.add("msg","msg2");
	data4.add("log_id",2);

	JSONBlock blck1; blck1.add(&data1);
	JSONBlock blck2; blck2.add(&data2);
	JSONBlock blck3; blck3.add(&data3);
	JSONBlock blck4; blck4.add(&data4);
	
	JSONArray logs;
	logs.setName("datalogs");
	logs.add(blck1);
	logs.add(blck2);

	JSONArray messages;
	messages.setName("messages");
	messages.add(blck3);
	messages.add(blck4);

	JSONBlock main;
	main.add(&logs);
	main.add(&messages);

	cout << conn.pushLogs(main.toString()) << endl;
	cout << "---------------------------------------------------------" << endl;
}