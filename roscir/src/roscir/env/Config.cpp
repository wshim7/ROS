#include "Config.h"
#include <sstream>
#include <ros/ros.h>
#include <ros/package.h>

using namespace std;

/**********************************************************************/
/*                                                                    */
/*  Class name      : CConfig.h                                       */
/*                                                                    */
/*  Description     : ȯ�������� ����ִ� config XML ������ �Ľ��Ͽ�  */
/*                    �� Param�� ���� Value ���� �о�� �� �ִ�.      */
/*                                                                    */
/*  Methods         :                                                 */
/*                                                                    */
/**********************************************************************/
/*                        ���� History                                */
/*                                                                    */
/*      DATE           AUTHOR                    DESCRIPTION          */
/*   ----------   ----------------   ------------------------------   */
/*   2005/05/26    JH. KIM           Initial Release                  */
/*                                                                    */
/**********************************************************************/


//const char* CConfig::CONFIG_FILE_NAME = "C:\\home\\silvermate-win\\system\\config\\config.xml";
const char* CConfig::CONFIG_FILE_NAME = "C:\\work\\cir\\config\\config.xml";
CConfig::CConfig(void)
{
	string pkgpath = ros::package::getPath("roscir");
	stringstream ss;
	ss<<pkgpath<<"/config/config.xml";
	ROS_INFO("config load from file[%s]", ss.str().c_str());
	this->xmlDocument = new TiXmlDocument( ss.str() );
	bool loadSuccess = this->xmlDocument->LoadFile();

	if ( loadSuccess )
	{
		
		this->rootElement = this->xmlDocument->RootElement();
	}
	else {
		cout << "[CConfig] : Could not open file (" << ss.str() << ")"<< endl;
	}
}

CConfig::~CConfig(void)
{
	delete this->xmlDocument;
}
/**********************************************************************/
/*                                                                    */
/*  Method Name     : getInstance()                                   */
/*                                                                    */
/*  Description     : get Sole Instance                               */
/*                                                                    */
/*  Return Value    : CConfig* - Sole Instance                        */
/*                                                                    */
/**********************************************************************/
CConfig* CConfig::getInstance()
{
	static CConfig thisInstance;
	return &thisInstance;
}

/**********************************************************************/
/*                                                                    */
/*  Method Name     : getParamValue                                   */
/*                                                                    */
/*  Description     : config ���Ͽ��� param�� �ش��ϴ� �κ���         */
/*                    ���� �����´�.                                  */
/*                                                                    */
/*  Parameters      : char *paramName - paramName                     */
/*                                                                    */
/*  Return Value    : char* - text value                              */
/*                                                                    */
/**********************************************************************/
const char* CConfig::getParamValue( const char *paramName )
{
	TiXmlNode* paramNode = NULL;
	const char* paramValue = NULL;


	while ( paramNode = this->rootElement->IterateChildren( "param", paramNode ) )
	{
		//if ( paramNode->Type() == paramNode->ELEMENT )
		if ( paramNode->Type() == paramNode->TINYXML_ELEMENT )
		{
			const char* currParamName = paramNode->ToElement()->Attribute( "name" );

			if ( strcmp( currParamName, paramName ) == 0 )
			{
				paramValue = paramNode->ToElement()->Attribute( "value" );
				//cout << "[CConfig::getParamValue] : "<< paramName << " = [" << paramValue << "]" << endl;

				return paramValue;
			}
		}
	}

	return "";
}


/**********************************************************************/
/*                                                                    */
/*  Method Name     : getParamValueInt                                */
/*                                                                    */
/*  Description     : config ���Ͽ��� param�� �ش��ϴ� �κ���         */
/*                    �������� �����´�.                              */
/*                                                                    */
/*  Parameters      : char *paramName - paramName                     */
/*                                                                    */
/*  Return Value    : int - ������                                    */
/*                                                                    */
/**********************************************************************/
int CConfig::getParamValueInt( const char *paramName )
{
	const char* paramValue = getParamValue( paramName );

	if ( paramValue == NULL )
		return -1;
	else
		return atoi( paramValue );
}


/**********************************************************************/
/*                                                                    */
/*  Method Name     : getParamValueDouble                             */
/*                                                                    */
/*  Description     : config ���Ͽ��� param�� �ش��ϴ� �κ���         */
/*                    �Ǽ����� �����´�.                              */
/*                                                                    */
/*  Parameters      : char *paramName - paramName                     */
/*                                                                    */
/*  Return Value    : double - �Ǽ���                                 */
/*                                                                    */
/**********************************************************************/
double CConfig::getParamValueDouble( const char *paramName )
{
	const char* paramValue = getParamValue( paramName );

	if ( paramValue == NULL )
		return -1;
	else
		return atof( paramValue );
}

/*
int main() {
	CConfig* config = CConfig::getInstance();
	
	const char* clientDevType = config->getParamValue("CLIENT_DEVICE_TYPE");
	cout<<clientDevType<<endl;

	cout<<"ROBOT_MONITOR_COM_PORT "<<config->getParamValue("ROBOT_MONITOR_COM_PORT")<<endl;

	return -1;
}
*/
