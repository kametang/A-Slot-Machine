/**
 * common/coin.c - Coin relative functions implement (Version: 0.1.0)
 *
 * Copyright (C) 2013 Ching-Tang, Chang
 * Copyright (C) 2013 A Slot Machine
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#include "coin.h"

int coinInit(COIN *coin, unsigned char type, unsigned char amount)
{
    coin->coinType = type;
    coin->amount = amount;
    coinUpdateStatus(coin);
    return 0;
}

int coinUpdateStatus(COIN *coin)
{
    if(coin->amount < COIN_SLOT_SIZE){
        coin->status = COIN_NORMAL;
        return coin->status;
    }else if(coin->amount == COIN_SLOT_SIZE){
        coin->status = COIN_FULL;
        return coin->status;
    }else
        return -1;
}


int coinGetStatus(COIN *coin)
{
    return coin->status;
}

int coinSloting(COIN *coin)
{
    if(coin->status == COIN_FULL)
        return -1;
    coin->amount++;
    coinUpdateStatus(coin);

    return coin->status;
}

int coinRefund(COIN *coin, unsigned char num)
{
    coin->amount -= num;
    coinUpdateStatus(coin);
    return 0;
}
