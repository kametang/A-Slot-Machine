/**
 * object/coin/header.h - coin object define (Version: 0.1.0)
 *
 * Copyright (C) 2013 Ching-Tang, Chang
 * Copyright (C) 2013 A Slot Machine
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#ifndef _A_SLOT_MACHINE_COIN_
#define _A_SLOT_MACHINE_COIN_

#define SLOT_EMPTY  0   // 0%
#define SLOT_LESS   1   // 10%
#define SLOT_NORMAL 2   // 10~90%
#define SLOT_MUCH   3   // 90%
#define SLOT_FULL   4   // 100%

struct coin
{
    unsigned short SLOT_FLAG;
    unsigned short amount;
};

#endif
