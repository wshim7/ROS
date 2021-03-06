#ifndef __MERO_LED_DRIVER_H__
#define __MERO_LED_DRIVER_H__

#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <string.h>
#include <reactive/mero/MeroDefinition.h>
#include <reactive/mero/utility/MeroFunctionFactory.h>
#include <reactive/mero/driver/MeroLEDTouchConnector.h>

using namespace std;

namespace reactive {
	namespace mero {
		namespace driver {
			class MeroLEDDriver {

			private :
				unsigned char _current_led_command;
				unsigned char _current_led_data[MERO_LED_DATA_PACKET_SIZE];
				MeroFunctionFactory* utility;

//				mutable		CRITICAL_SECTION	comunicate;
				static pthread_mutex_t __comunicate_mutex;

				MeroLEDTouchConnector* connector;

			public :
				MeroLEDDriver();
				virtual ~MeroLEDDriver();

				static MeroLEDDriver* getInstance();

				void setLEDCommandPacket( unsigned char* buffer);
				void addLEDCommandPacket( unsigned char* buffer, const int startIndex);

				int parseAndSetLEDDataPacket(int dataPacketSize, unsigned char* dataPacket);
				int parseAndSetLEDDataPacket(int dataPacketSize, unsigned char* dataPacket, const int startIndex);

				void setLEDValue(unsigned char id, unsigned char red, unsigned char green, unsigned char blue);
				bool isLEDPacket(unsigned char* buffer, const int startIndex);

				void updateMeroLED();
			};
		}
	}
}

#endif /* __MERO_LED_DRIVER_H__ */
