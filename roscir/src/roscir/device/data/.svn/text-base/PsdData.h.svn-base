#ifndef __ROSCIR_DATA_PSD_H__
#define __ROSCIR_DATA_PSD_H__

#include <iostream>
#include <string>
#include <roscir/device/CirApi.h>

using namespace std;

class CIRAPI CPSDData {
public:
	static const int __NUMBER_OF_MAX_DATA = 6;
private:
	int numberOfData;
	unsigned short data[__NUMBER_OF_MAX_DATA];

public:
	CPSDData();
	CPSDData(unsigned short* data, int numberOfData);
	virtual ~CPSDData();
	unsigned short* getData();
	const int& getNumberOfData() const;
	void print();

	void setData(unsigned short* data, int numberOfData);

};

#endif /* __ROSCIR_DATA_PSD_H__ */