/**
 * common/coin.h - coin structure & function declaration (Version: 0.1.0)
 *
 * Copyright (C) 2013 Ching-Tang, Chang
 * Copyright (C) 2013 A Slot Machine
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#ifndef _ASM_COIN_
#define _ASM_COIN_

// Constant Defiantion
#define COIN_SLOT_SIZE 100

// COIN SLOT Status
#define COIN_FULL 0
#define COIN_NORMAL 1

// Coin Type
#define COIN_1  0
#define COIN_5  1
#define COIN_10 2
#define COIN_50 3

/*
    Coin Structure
 */
typedef struct _COIN{
    unsigned char coinType;
    unsigned char amount;
    unsigned char status;
}COIN;

// Coin relative functions
int coinInit(COIN *coin, unsigned char type, unsigned char amount);
int coinUpdateStatus(COIN *coin);
int coinGetStatus(COIN *coin);
int coinSloting(COIN *coin);
int coinRefund(COIN *coin, unsigned char num);

#endif
