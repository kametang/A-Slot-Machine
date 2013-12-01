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
#define COIN_EMPTY 0
#define COIN_LESS 1
#define COIN_NORMAL 2
#define COIN_MUCH 3
#define COIN_FULL 4

// COIN Status EDGE
#define COIN_LESS_EDGE 10
#define COIN_MUCH_EDGE 90

// COIN Color Status
// @TODO: color defination from MiniGUI parameter
#define COIN_EMPTY_COLOR
#define COIN_LESS_COLOR
#define COIN_NORMAL_COLOR
#define COIN_MUCH_COLOR
#define COIN_FULL_COLOR

// Coin Type
#define COIN_1  0
#define COIN_5  1
#define COIN_10 2
#define COIN_50 3

/*
    Coin Structure
 */
typedef struct
{
    unsigned char coinType;
    unsigned char amount;
    unsigned char status;
    unsigned char remain;
}COIN;

/*
    Coin Slot Structure
 */
typedef struct
{
    COIN coinSlot[4];
}COIN_SLOT;

/*
    New slot structure
 */
typedef struct
{
    unsigned char coin1;
    unsigned char coin5;
    unsigned char coin10;
    unsigned char coin50;
}NEW_SLOT;

// Coin relative functions
int coinInit(COIN_SLOT *coinslot);
int coinStatus(COIN *coin);
int coinSloting(COIN *coin, unsigned char num);

#endif
