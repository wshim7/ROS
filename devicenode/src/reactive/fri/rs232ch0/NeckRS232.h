#ifndef __NeckRS232__
#define __NeckRS232__

#include "FRI_RS232.h"
class NeckRS232
{
public:
	NeckRS232(void);
	~NeckRS232(void);

	int sendMessageToNeck(struct Fri_Neck_Cmdfifo *p_FriPantiltCmdfifo);
	
	// 1:pantilt, 2:rollbend
	void getNeckPosition(int id, double& ang1, double &ang2);

	// 1 : 
	
	double MotorPos[4];
	
	double readMotorPosition( int motorID );

	void writeGetMotorEncoder( int motorID );

	int setMotorCompliance( int option );

	static NeckRS232* getInstance();

	static const int RECEIVE_TIMEOUT = 500;
private:

	static NeckRS232* thisInstance;

	string TTY_NECK ; 
	static const int BAUD_RATE_NECK	=115200;
	static const int SND_BUFFER_NECK_SIZE = 50;

	unsigned char rs232_snd_data[SND_BUFFER_NECK_SIZE];

	struct   Fri_Neckencoder_Shmdata *p_FriNeckencoderShmdata;

	int send_motorCmdPacket_move2motorsync(struct Fri_Neck_Cmdfifo *p_FriNeckCmdfifo);
	int send_motorCmdPacket_movemotor(struct Fri_Neck_Cmdfifo *p_FriPantiltCmdfifo);

	FRI_RS232 serial;
	double m_encoderSacle;
	int sleepTime;
	int elsTime;

//	CRITICAL_SECTION  critSecPanRoll;
	static pthread_mutex_t __motor_mutex;
};

#endif

