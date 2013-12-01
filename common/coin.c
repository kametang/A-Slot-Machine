/**
 * common/coin.c - Coin relative functions implement (Version: 0.1.0)
 *
 * Copyright (C) 2013 Ching-Tang, Chang
 * Copyright (C) 2013 A Slot Machine
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
int coinInit(COIN_SLOT *coinslot)
{
    unsigned char i;
    for(i = 0; i < 4; i++){
        coinslot[i]->coinType = i;
        coinslot[i]->amount = COIN_SLOT_SIZE / 2;
        coinslot[i]->stauts = COIN_NORMAL;
        coinslot[i]->remain = COIN_SLOT_SIZE - coinslot[i]->amount;
    }

    return 0;
}


int coinStatus(COIN *coin)
{
    if(coin->amount == 0)
        coin->stauts = COIN_EMPTY;
    else if(coin->amount <= COIN_LESS_EDGE)
        coin->status = COIN_LESS;
    else if(coin->amount == 100)
        coin->status = COIN_FULL;
    else if(coin->amount >= COIN_MUCH_EDGE)
        coin->status = COIN_MUCH;
    else
        coin->status = COIN_NORMAL;

    return coin->status;
}

int coinSloting(COIN *coin, unsigned char num)
{
    if(num > coin->remain)
        return -1;
    coin->amount += num;
    coin->remain -= num;
    coinstatus(coin);

    return 0;
}
