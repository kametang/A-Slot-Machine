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
#define STUFF_SLOT_SIZE 20

// Stuff Status Defination
#define STUFF_EMPTY     0
#define STUFF_NORMAL    1

// Stuff Structure
typedef struct _STUFF
{
    unsigned char amount;
    unsigned char status;
    unsigned char price;
}STUFF;

// Stuff relative Functions
int stuffInit(STUFF *stuff, unsigned char amount, unsigned char price);
int stuffUpdateStatus(STUFF *stuff);
int stuffGetStatus(STUFF *stuff);
int stuffGetPrice(STUFF *stuff);
int stuffBuy(STUFF *stuff);
#endif
