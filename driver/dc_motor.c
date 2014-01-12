#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "dc_motor.h"

int DCM_Init()
{
    return open(DCM_DEVICE, O_RDONLY);
}

void DCM_Normal(int dcmfd)
{
    ioctl(dcmfd, SPEED_NORMAL, NULL);
}

void DCM_High(int dcmfd)
{
    ioctl(dcmfd, SPEED_HIGH, NULL);
}

void DCM_Off(int dcmfd)
{
    ioctl(dcmfd, SPEED_OFF, NULL);
}
