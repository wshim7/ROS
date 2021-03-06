#ifndef __EROBOT_PSD_CORE_H__
#define __EROBOT_PSD_CORE_H__

#include <reactive/erobot/utility/ERobotFunctionFactory.h>
#include <reactive/erobot/ERobotDefinition.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;
using namespace reactive::erobot::core;

namespace reactive {
	namespace erobot {
		namespace core {
			class EPSDCore {

			private :
				unsigned short	_this_psd_data[EROBOT_PSD_DATACOUNT];

			public :
				EPSDCore();
				virtual ~EPSDCore();

				void getPSDCommandPacket(unsigned char command, unsigned char* buffer);
				void addPSDCommandPacket(unsigned char command, unsigned char* buffer, const int startIndex);

				int parseAndSetPSDDataPacket(int dataPacketSize, unsigned char* dataPacket);
				int parseAndSetPSDDataPacket(int dataPacketSize, unsigned char* dataPacket, const int startIndex);

				void getPSDValue(unsigned short *data, int nDataSize);
				bool isPSDPacket(unsigned char* buffer, const int startIndex);
			};
		}
	}
}

#endif /* __EROBOT_PSD_CORE_H__ */
