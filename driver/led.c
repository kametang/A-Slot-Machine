#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "led.h"

const static char order[4] = { 0, 2, 1, 3};
static LED_MAP tmp;

int LED_Init()
{
    return open(LED_DEVICE, O_RDONLY);
}

void LED_MAP_Create(LED_MAP *map, const u16 *pattern)
{
    int i;
    for(i = 0; i < 8; i++)
        map->map[i] = pattern[i];
}

void LED_Operation(int ledfd, int id, char operation)
{
    ioctl(ledfd, operation, &order[id]);
}

void LED_MAP_Display(int ledfd, LED_MAP *map)
{
    ioctl(ledfd, LED_8X8, map);
}

void LED_MAP_RollDown(int ledfd, LED_MAP *map)
{
    u16 identify = 0x80;
    int i, k;
    for(i = 0; i < 8; i++)
        tmp.map[i] = 0x00;
    tmp.d = 10;

    for(i = 0; i < 8; i++){
        if(i == 7)
            tmp.d = 30;
        identify >>= 1;
        for(k = 0; k < 8; k++){
            tmp.map[k] <<= 1;
            tmp.map[k] |= (identify & map->map[k])?0x01:0x00;
        }
        ioctl(ledfd, LED_8X8, &tmp);
    }
    LED_MAP_Clean(ledfd);
}

void LED_MAP_Clean(int ledfd)
{
    int i;
    for(i = 0; i < 8; i++)
        tmp.map[i] = 0x00;
    tmp.d = 1;
    ioctl(ledfd, LED_8X8, &tmp);
}
