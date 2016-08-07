#ifndef __MERO_FUNCTION_FACTORY_H__
#define __MERO_FUNCTION_FACTORY_H__

#include <reactive/mero/MeroDefinition.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

namespace reactive {
	namespace mero {
		namespace driver {
			class MeroFunctionFactory {
			
			private :
				MeroFunctionFactory();
				virtual ~MeroFunctionFactory();
			
			public :
				static MeroFunctionFactory* getInstance();
				
				void intTo2Bytes(int n, unsigned char * bp);
				void intToByte(int n, unsigned char * bp);
				int byte2Int(unsigned char *bp, int len);

				string intToString( int intNumber );
				int StringToInt( string str );

				void byte2Short(unsigned char *bp, int len, short *data);

				unsigned char getChecksum(unsigned char* packet, int packet_len);
				unsigned char getChecksumWithNoOffset(unsigned char* packet, int packet_len);
				unsigned char getChecksumWithStartIndex(unsigned char* packet, int packet_len, int startIndex);

				int getReadPacketSize(unsigned char nCommand);

			};
		}
	}
}

#endif /* __Mero_FUNCTION_FACTORY_H__ */
