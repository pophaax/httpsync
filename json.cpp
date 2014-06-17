#include "JSONBlock.h"
#include "JSONArray.h"
#include "JSONData.h"
#include <iostream>

using namespace std;


int main() {

	string example = "{\"logs\":[{\"id\":1,\"logtime\":\"2014-06-06%2611:11:11\",\"sc_command\":6000,\"rc_command\":6000,\"cc_dtw\":30,\"cc_btw\":90,\"cc_cts\":180,\"cc_tack\":0,\"ws_buffersize\":30,\"ws_sensormodel\":\"CV7\",\"ws_direction\":225,\"ws_speed\":5,\"ws_temperature\":25,\"rs_position\":6000,\"ss_position\":6000,\"gps_timestamp\":\"Fri%26June%2606%2611:11:11%262014\",\"gps_latitude\":60.3231,\"gps_longitude\":20.0011,\"gps_altitude\":30,\"gps_speed\":30,\"gps_heading\":30,\"gps_mode\":30,\"gps_satellites\":30},{\"id\":2,\"logtime\":\"2014-06-06%2612:12:12\",\"sc_command\":7000,\"rc_command\":5000,\"cc_dtw\":50,\"cc_btw\":70,\"cc_cts\":150,\"cc_tack\":1,\"ws_buffersize\":30,\"ws_sensormodel\":\"CV7\",\"ws_direction\":310,\"ws_speed\":4,\"ws_temperature\":26,\"rs_position\":7000,\"ss_position\":5000,\"gps_timestamp\":\"Fri%26June%2606%2612:12:12%262014\",\"gps_latitude\":60.3231,\"gps_longitude\":20.0011,\"gps_altitude\":30,\"gps_speed\":30,\"gps_heading\":30,\"gps_mode\":30,\"gps_satellites\":30}],\"messages\":[{\"id\":1,\"logtime\":\"2014-06-06%2611:11:11\",\"error\":\"test\"},{\"id\":2,\"logtime\":\"2014-06-06%2612:12:12\",\"error\":\"test2\"}]}";
	
	JSONData data1;
	data1.add("id",1);
	data1.add("logtime","2014-06-06 11:11:11");
	data1.add("sc_command",6000);
	data1.add("rc_command",6000);
	data1.add("cc_dtw",30);
	data1.add("cc_btw",90);
	data1.add("cc_cts",180);
	data1.add("cc_tack",0);
	data1.add("ws_buffersize",30);
	data1.add("ws_sensormodel","CV7");
	data1.add("ws_direction",225);
	data1.add("ws_speed",5);
	data1.add("ws_temperature",25);
	data1.add("rs_position",6000);
	data1.add("ss_position",6000);
	data1.add("gps_timestamp","Fri June 06 11:11:11 2014");
	data1.add("gps_latitude",60.3231);
	data1.add("gps_longitude",20.0011);
	data1.add("gps_altitude",30);
	data1.add("gps_speed",30);
	data1.add("gps_heading",30);
	data1.add("gps_mode",30);
	data1.add("gps_satellites",30);

	JSONData data2;
	data2.add("id",2);
	data2.add("logtime","2014-06-06 12:12:12");
	data2.add("sc_command",7000);
	data2.add("rc_command",5000);
	data2.add("cc_dtw",50);
	data2.add("cc_btw",70);
	data2.add("cc_cts",150);
	data2.add("cc_tack",1);
	data2.add("ws_buffersize",30);
	data2.add("ws_sensormodel","CV7");
	data2.add("ws_direction",310);
	data2.add("ws_speed",4);
	data2.add("ws_temperature",26);
	data2.add("rs_position",7000);
	data2.add("ss_position",5000);
	data2.add("gps_timestamp","Fri June 06 12:12:12 2014");
	data2.add("gps_latitude",60.3231);
	data2.add("gps_longitude",20.0011);
	data2.add("gps_altitude",30);
	data2.add("gps_speed",30);
	data2.add("gps_heading",30);
	data2.add("gps_mode",30);
	data2.add("gps_satellites",30);

	JSONData data3;
	data3.add("id",1);
	data3.add("logtime","2014-06-06 11:11:11");
	data3.add("error","test");

	JSONData data4;
	data4.add("id",2);
	data4.add("logtime","2014-06-06 12:12:12");
	data4.add("error","test2");

	JSONBlock blck1; blck1.add(&data1);
	JSONBlock blck2; blck2.add(&data2);
	JSONBlock blck3; blck3.add(&data3);
	JSONBlock blck4; blck4.add(&data4);
	
	JSONArray logs;
	logs.setName("logs");
	logs.add(blck1);
	logs.add(blck2);

	JSONArray messages;
	messages.setName("messages");
	messages.add(blck3);
	messages.add(blck4);

	JSONBlock main;
	main.add(&logs);
	main.add(&messages);

	cout << endl << endl << example << endl;
	cout << endl << endl << main.toString() << endl;

	string result = "failed";
	if(example.compare(main.toString())==0) {
		result = "success";
	}
	cout << endl << endl << result << endl;

/*
"{
	logs : [
		{
			id : 1,
			logtime : 2014-06-06%2611:11:11,
			sc_command : 6000,
			rc_command : 6000,
			cc_dtw : 30,
			cc_btw : 90,
			cc_cts : 180,
			cc_tack : 0,
			ws_buffersize : 30,
			ws_sensormodel : CV7,
			ws_direction : 225,
			ws_speed : 5,
			ws_temperature : 25,
			rs_position : 6000,
			ss_position : 6000,
			gps_timestamp : Fri%26June%2606%2611:11:11%262014,
			gps_latitude : 60.3231,
			gps_longitude : 20.0011,
			gps_altitude : 30,
			gps_speed : 30,
			gps_heading : 30,
			gps_mode : 30,
			gps_satellites : 30
		},{
			id : 2,
			logtime : 2014-06-06%2612:12:12,
			sc_command : 7000,
			rc_command : 5000,
			cc_dtw : 50,
			cc_btw : 70,
			cc_cts : 150,
			cc_tack : 1,
			ws_buffersize : 30,
			ws_sensormodel : CV7,
			ws_direction : 310,
			ws_speed : 4,
			ws_temperature : 26,
			rs_position : 7000,
			ss_position : 5000,
			gps_timestamp : Fri%26June%2606%2612:12:12%262014,
			gps_latitude : 60.3231,
			gps_longitude : 20.0011,
			gps_altitude : 30,
			gps_speed : 30,
			gps_heading : 30,
			gps_mode : 30,
			gps_satellites : 30
		}
	]
	messages : [
		{
			id : 1,
			logtime : 2014-06-06%2611:11:11,
			error : test
		},{
			id : 2,
			logtime : 2014-06-06%2612:12:12,
			error : test2
		}
	]
}";
*/
}