/*
 * ofwriter.cpp
 *
 *  Created on: Sep 26, 2014
 *      Author: cir
 */




/*
 * ofxreader.cpp
 *
 *  Created on: 2013. 5. 25.
 *      Author: root
 */

#include <ros/ros.h>

#include "ofSerial.h"
#include <stdio.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <sstream>

//void writePacket(ofSerial& serial) {
//	Protocol p;
//	memset(&p, 0, sizeof(p));
//	char buffer[1024];
//	int wdsize = 0;
//	int index = 0;
//
//	stringstream ss;
//	for(int i = 0; i < 10; i++) {
//		ss<<"1234567890";
//	}
//	ss<<"@@";
//
//	strcpy(buffer, ss.str().c_str());
//
//	for(int i = 0; i < 100; i++) {
////		sprintf(buffer, "hello world@");
////		wdsize = serial.writeBytes((unsigned char*)buffer, strlen(buffer));
////		printf("index(%d) rdsize(%d) sentence: %s\n", index++,  wdsize, buffer);
//		printf("try send %d\n", i);
//		p.reserved++;
//		int wdsize = serial.writeBytes((unsigned char*)buffer, strlen(buffer));
//		printf("index :  %d , wdsize : %d\n", i, wdsize);
////		int rdsize = serial.readBytes((unsigned char*)&p, sizeof(p));
////		printf(" read bytes : %d\n", rdsize);
//		//boost::this_thread::sleep(boost::posix_time::milliseconds(100));
//		//serial.flush(false, true);
//	}
//}
//
//void writeLongPacket(ofSerial& serial) {
//
//	int DATA_COUNT = 100;
//
//	long data[DATA_COUNT];
//	char buffer[1024];
//	int wdsize = 0;
//
//	for(int i=0 ; i<DATA_COUNT ; i++) {
//		data[i] = i+1;
//	}
//	memcpy(buffer,&data,sizeof(long)*DATA_COUNT);
//
//	for(int i = 0; i < 100; i++) {
//		printf("try send %d\n", i);
//		wdsize = serial.writeBytes((unsigned char*)buffer, sizeof(long)*DATA_COUNT );
//		printf("index :  %d , wdsize : %d\n", i, wdsize);
//	}
//}

void resetConn(ofSerial& serial) {
//	serial.flush(true,false);
}

void writeTestPacket(ofSerial& serial) {
	printf("\n\n !!! test start !!! \n\n");
	int readPacketSize				= 23;  // wheel encoder
	int sendPacketSize				= 17;  // wheel + wheel encoder

	unsigned char* sendPacket		= new unsigned char[sendPacketSize];
	unsigned char* receivePacket	= new unsigned char[readPacketSize];

	memset(sendPacket, 0x00, sendPacketSize);
	memset(receivePacket, 0x00, readPacketSize);

	sendPacket[0] = 0x03;
	sendPacket[1] = 0xf3;
	sendPacket[2] = 0xf3;
	sendPacket[3] = 0x0e;
	sendPacket[4] = 0x0e;

	sendPacket[5] = 0x03;
	sendPacket[6] = 0xf3;
	sendPacket[7] = 0xf3;
	sendPacket[8] = 0x01;
	sendPacket[9] = 0x00;
	sendPacket[10] = 0x00;
	sendPacket[11] = 0x00;
	sendPacket[12] = 0x00;
	sendPacket[13] = 0x00;
	sendPacket[14] = 0x00;
	sendPacket[15] = 0x00;
	sendPacket[16] = 0x00;

	int loopcnt = 0;

	while(true) {

		for(int i=0 ; i<20 ; i++) {
			printf("====================================================\n");
			sendPacket[11] = 0x00;
			sendPacket[12] = 0x20;
			int wdsize = serial.writeBytes((unsigned char*)sendPacket, sizeof(unsigned char)*sendPacketSize );
			printf("write size : %d \n" , wdsize);

			int rdsize = serial.readBytes(receivePacket,readPacketSize);
			printf("read size : %d \n" , rdsize);
			if(rdsize == readPacketSize) {
				printf(" read success!! \n");
			} else {
				printf(" -----> fail \n");
				resetConn(serial);
			}
			ros::Duration(0.15).sleep();
		}

		for(int i=0 ; i<20 ; i++) {
			printf("====================================================\n");
			sendPacket[11] = 0x80;
			sendPacket[12] = 0x14;
			int wdsize = serial.writeBytes((unsigned char*)sendPacket, sizeof(unsigned char)*sendPacketSize );
			printf("write size : %d \n" , wdsize);

			int rdsize = serial.readBytes(receivePacket,readPacketSize);
			printf("read size : %d \n" , rdsize);
			if(rdsize == readPacketSize) {
				printf(" read success!! \n");
			} else {
				printf(" -----> fail \n");
				resetConn(serial);
			}
			ros::Duration(0.15).sleep();
		}
		printf("\n\n loop count : %d \n\n",loopcnt++ );

	}
}

int main(int argc, char **argv) {

	ros::Time::init();
	ofSerial serial;

//	if(argc < 2) {
//		return printf("input number\n");
//	}
//	stringstream ss;
//	ss<<"/dev/ttyMP"<<argv[1];
//
//	printf("set serial : %s\n", ss.str().c_str());

	string device = "/dev/ttyMP0";
	serial.setup(device.c_str(), 115200);
	serial.flush(true, true);
//	boost::thread thread1 = boost::thread(boost::bind(&writeLongPacket,serial));

	printf("set serial finish!! size : %d  \n", sizeof(unsigned char));
//	thread1.join();
//	writePacket(serial);
//	writeLongPacket(serial);
	writeTestPacket(serial);

	sleep(3);

}



