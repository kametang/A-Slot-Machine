/**
 * common/stuff.c - stuff relative functions implement (Version: 0.1.0)
 *
 * Copyright (C) 2013 Ching-Tang, Chang
 * Copyright (C) 2013 A Slot Machine
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include "stuff.h"
#include <string.h>

int stuffInit(STUFF *stuff, char name[], unsigned char price)
{
    strcpy(stuff->name, name);
    stuff->amount = STUFF_SLOT_SIZE;
    stuff->status = STUFF_NORMAL;
    stuff->price = price;
    return 0;
}

int stuffStatus(STUFF *stuff)
{
    if(stuff->amount > STUFF_LESS_EDGE)
        stuff->status = STUFF_NORMAL;
    else if(stuff->amount <= STUFF_EDGE)
        stuff->stauts = STUFF_LESS;
    else if(stuff->amount == 0)
        stuff->stauts = STUFF_EMPTY;
    
    return stuff->status;
}

int stuffBuy(STUFF *stuff, unsigned char num)
{
    if(stuff->amount < num)
        return -1;      // Not Enough
    else{
        stuff->amount -= num;
        stuffStatus(stuff);
    }
    return 0;
}
