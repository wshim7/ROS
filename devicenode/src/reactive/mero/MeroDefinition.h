/*
 * MeroDefinition.h
 *
 *  Created on: 2014. 1. 14.
 *      Author: msyoo
 */

#ifndef _MERODEFINITION_H_
#define _MERODEFINITION_H_

//#define RETURN_SUCCESS					1
//#define RETURN_FAILED					-1
//
//
//#define MAX_2BYTE_INT						32767
//#define MAX_3BYTE_INT						8388607
//
//#define MERO_TYPE_TOUCHBUTTON						0x03
//
//#define MERO_LED_DATA_PACKET_SIZE			10


#pragma pack(push,1)

typedef struct MERO_COMMON_HEADER_PACKET {
	unsigned char	id;				// 1byte
	unsigned short	sub_id;			// 2byte
	unsigned char	command;		// 1byte
} MERO_COMMON_HEADER_PACKET;

typedef struct MERO_SENSOR_HEADER_PACKET {
	unsigned char	id;				// 1byte
	unsigned char	sub_id;			// 1byte
	unsigned char	command;		// 1byte
} MERO_SENSOR_HEADER_PACKET;

#pragma pack(pop)

#define MERO_COMMON_HEADER_PACKET_SIZE	4
//#define MERO_SENSOR_HEADER_PACKET_SIZE	3
#define MERO_CHECKSUM_PACKET_SIZE			1
#define MERO_LED_DATA_PACKET_SIZE			6

/*
 *
 *		ERobot constand
 *
 */
#define MERO_SERIAL_BAUDRATE			115200


#define MERO_TOUCH_DATACOUNT			2

#define RETURN_SUCCESS					1
#define RETURN_FAILED					-1

/*
 *
 *		Device ID
 *
 */

#define MERO_DEVICE_TOUCHBUTTON_ID			0x06
#define MERO_DEVICE_LED_ID					0x06

/*
 *
 *		Device sub ID
 *
 */

#define MERO_DEVICE_TOUCHBUTTON_SUB_ID_1		0xF6
#define MERO_DEVICE_TOUCHBUTTON_SUB_ID_2		0xF6
#define MERO_DEVICE_LED_SUB_ID_1				0xF6
#define MERO_DEVICE_LED_SUB_ID_2				0xF6

/*
 *
 *		Device Command
 *
 */


#define MERO_COMMAND_TOUCHBUTTON_GET_DATA						0xF1
#define MERO_COMMAND_TOUCHBUTTON_DETECTING_ERROR				0x0E


/*
 *
 *		Function Factory
 *
 */
#define MAX_2BYTE_INT						32767
#define MAX_3BYTE_INT						8388607


#define RET_CHECKSUM_ERROR  -2
#define RET_NO_READ_ERROR	 -3

#define DEFAULT_SLEEP 10
#define DEFAULT_BUF_SIZE 36


#define MERO_TYPE_TOUCHBUTTON						0x03


#endif /* _MERODEFINITION_H_ */
