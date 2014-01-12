/**
 * common/stuff.c - stuff relative functions implement (Version: 0.1.0)
 *
 * Copyright (C) 2013 Ching-Tang, Chang
 * Copyright (C) 2013 A Slot Machine
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include "stuff.h"

int stuffInit(STUFF *stuff, unsigned char amount, unsigned char price)
{
    stuff->amount = amount;
    stuff->price = price;
    stuffUpdateStatus(stuff);
    return 0;
}

int stuffUpdateStatus(STUFF *stuff)
{
    if(stuff->amount > 0){
        stuff->status = STUFF_NORMAL;
        return stuff->status;
    }else if(stuff->amount == 0){
        stuff->status = STUFF_EMPTY;
        return stuff->status;
    }
    return stuff->status;
}

int stuffGetStatus(STUFF *stuff)
{
    return stuff->status;
}

int stuffGetPrice(STUFF *stuff)
{
    return stuff->price;
}

int stuffBuy(STUFF *stuff)
{
    if(stuff->status == STUFF_EMPTY)
        return -1;
    stuff->amount--;
    stuffUpdateStatus(stuff);
    return 0;
}
