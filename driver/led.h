// ------------------------------------------------------------------------------------------
// File:            driver/led.h
// Description:     LED header defination
// Version:         0.1.0
// Author:          Ching-Tang, Chang <km-work@tth.twbbs.org>
// 
// Copyright (C) 2013 project_name
// ------------------------------------------------------------------------------------------
#ifndef ASM_LED_H
#define ASM_LED_H

#define LED_ON      0
#define LED_OFF     1
#define LED_8X8     2
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct _LED_PARAM{
    unsigned int num;
}LED_PARAM;

typedef struct _KEY_PARAM{
    unsigned int state;
}KEY_PARAM;

typedef struct _LED_MAP{
    u16 map[8];
    u32 d;
}LED_MAP;

#define LED_DEVICE "/dev/led"

int LED_Init();
void LED_Operation(int ledfd, int id, char operation);
void LED_MAP_Create(LED_MAP *map, const u16 *pattern);
void LED_MAP_Display(int ledfd, LED_MAP *map);
void LED_MAP_RollDown(int ledfd, LED_MAP *map);
void LED_MAP_Clean(int ledfd);
#endif
