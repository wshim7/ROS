#ifndef _RT_FRI_NECK_H_
#define _RT_FRI_NECK_H_

struct Fri_Neck_Cmdfifo{
	int 	cmd;
	unsigned int	motorID[2];
	unsigned int 	speed[2];
	unsigned int 	position[2];
};

struct Fri_Neck_Reportfifo{
	int		status;
};

struct Fri_Neckencoder_Shmdata{

	long data[4];

};

#define FRI_NECK_CMDFIFO_CMD_MOVEMOTOR			1
#define FRI_NECK_CMDFIFO_CMD_MOVE2MOTORSYNC		2
#define FRI_NECK_CMDFIFO_CMD_GETSTATUS			3

#endif
