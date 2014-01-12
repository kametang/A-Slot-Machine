#ifndef ASM_DC_MOTOR
#define ASM_DC_MOTOR

#define SPEED_NORMAL 10
#define SPEED_HIGH 30
#define SPEED_OFF 0

#define AC97_IO_DATA    0x5a
#define AC97_IO_DIR 0x5c

typedef struct _STEP_PARAM{
    unsigned int clockwise;
    unsigned int speed;
}STEP_PARAM;

#define DCM_DEVICE "/dev/dcm"
int DCM_Init();
void DCM_Normal(int dcmfd);
void DCM_High(int dcmfd);
void DCM_Off(int dcmfd);
#endif
