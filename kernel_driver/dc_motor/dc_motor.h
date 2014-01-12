#ifndef DCM_DRV_H
#define DCM_DRV_H

#define SPEED_NORMAL 10
#define SPEED_HIGH 30
#define SPEED_OFF 0

#define AC97_IO_DATA    0x5a
#define AC97_IO_DIR 0x5c

typedef struct _STEP_PARAM{
    unsigned int clockwise;
    unsigned int speed;
}STEP_PARAM;


#endif
