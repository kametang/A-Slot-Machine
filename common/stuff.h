/**
 * common/stuff.h - Stuff structure & function declaration (Version: 0.1.0)
 *
 * Copyright (C) 2013 Ching-Tang, Chang
 * Copyright (C) 2013 A Slot Machine
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#ifndef _ASM_STUFF_
#define _ASM_STUFF_

// Constant Defination
#define STUFF_SLOT_SIZE 100

// Stuff Status Defination
#define STUFF_EMPTY     0
#define STUFF_LESS      1
#define STUFF_NORMAL    2

#define STUFF_LESS_EDGE 10

// Stuff Structure
typedef struct
{
    char name[50];
    unsigned char amount;
    unsigned char status;
    unsigned char price;
}STUFF;

// Stuff relative Functions
int stuffInit(STUFF *stuff, char name[], unsigned char price);
int stuffStatus(STUFF *stuff);
int stuffBuy(STUFF *stuff, unsigned char num);
#endif
