#pragma once
#include <iostream>
#include <string>
#include <roscir/device/CirApi.h>
#include <tinyxml.h>

using namespace std;

class CIRAPI CConfig
{
private :
	static const char* CONFIG_FILE_NAME;

	TiXmlDocument* xmlDocument;
	TiXmlElement* rootElement;

	CConfig();

public :
	~CConfig();
	static CConfig* getInstance();

	const char* getParamValue( const char* paramName );
	int getParamValueInt( const char* paramName );
	double getParamValueDouble( const char* paramName );
};
