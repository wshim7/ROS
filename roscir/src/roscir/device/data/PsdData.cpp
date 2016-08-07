#include "PsdData.h"
#include <stdio.h>

CPSDData::CPSDData() {
	for(int i =0; i < __NUMBER_OF_MAX_DATA; i++) {
		data[i] = 0;
	}
	this->numberOfData = __NUMBER_OF_MAX_DATA;
}

CPSDData::CPSDData(unsigned short* sdata, int dataCount) {
	this->numberOfData = dataCount;
	for(int i =0; i < __NUMBER_OF_MAX_DATA; i++) {
		this->data[i] = data[i];
	}
}

CPSDData::~CPSDData() {

}

void CPSDData::setData(unsigned short* data, int numberOfData) {
	this->numberOfData = numberOfData;
	for(int i =0; i < __NUMBER_OF_MAX_DATA; i++) {
		this->data[i] = data[i];
	}
}

unsigned short* CPSDData::getData() {
	return this->data;
}

const int& CPSDData::getNumberOfData()  const {
	return numberOfData;
}

void CPSDData::print() {
	for(int i = 0;  i < getNumberOfData(); i++) {
		//cout<<"data["<<i<<"]="<<getData()[i]<<" , ";
		printf("%04d ", data[i]);
	}
	cout<<endl;
}
