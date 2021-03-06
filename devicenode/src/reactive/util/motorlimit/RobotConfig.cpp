#include "RobotConfig.h"
#include <ros/ros.h>
#include <ros/package.h>
#include <boost/filesystem.hpp>

CRobotConfig::CRobotConfig(map<string, double> &limits)
{
	this->m_Limits = &limits;
	
}

CRobotConfig::~CRobotConfig(void)
{
}



int CRobotConfig::loadConfig(string robotType, string partName)
{
	int ret =0;

	string pkgpath = ros::package::getPath("devicenode");
		stringstream confpath;
		ROS_INFO("pkgpath: %s\n", pkgpath.c_str());
		confpath<<pkgpath<<"/config/robotlimitconfig.xml";
		boost::filesystem::path p(confpath.str());
		if(!boost::filesystem::exists(p)) {
			ROS_ERROR("Not exist robotlimitconfig.xml file in [%s]", confpath.str().c_str());
			ROS_INFO("Loaded %s Default Values!", robotType.c_str());
			return 0;
		}

	const string filePath = confpath.str();

	if(configXML.loadFile(filePath)){
		ROS_INFO("Loaded %s Robot Limit Configuration Values!!", robotType.c_str());
		readXmlValue(configXML,robotType, partName );
		ret =1;
	}else{
		ROS_ERROR("XML Load error Loaded %s Default Values!", robotType.c_str());
		ret =0;
	}

	return ret;
}

void CRobotConfig::readXmlValue( XmlSettings &configXML, string robotName, string partsType )
{
	int numConfigTags = configXML.getNumTags("config:robot");

	if(numConfigTags>0){
		configXML.pushTag("config", numConfigTags - 1);

		int numRobotTags = configXML.getNumTags("robot");

		if(numRobotTags>0){
			for ( int i = 0 ; i < numRobotTags ; i++)
			{
				string robotType = configXML.getAttribute("robot", "type", "NO_Robot", i);
				if(robotType == robotName){

					configXML.pushTag("robot",i);

					int numpartsTags = configXML.getNumTags("parts");

					for(int j=0; j<numpartsTags; j++){
						string partsName = configXML.getAttribute("parts", "name", "NO_Name", j);
						if(partsName == partsType){
							configXML.pushTag("parts",j);
							int numDeviceTags =configXML.getNumTags("device");

							for(int k=0; k<numDeviceTags; k++){
								string deviceName = configXML.getAttribute("device", "name", "NO_Device_Name", k);
								double deviceValue;
								if(robotType =="FRI" && partsName =="headface"){
									deviceValue = configXML.getAttribute("device", "value", 90.0, k);
									m_Limits->insert( map< string, double >::value_type(deviceName, deviceValue));
								}else{
									deviceValue = configXML.getAttribute("device", "value", 0.0, k);
									m_Limits->insert( map< string, double >::value_type(deviceName, deviceValue));
								}
								
							}
							configXML.popTag();
						}
					}
					configXML.popTag();
				}
			}
		}
		configXML.popTag();
	}
}




