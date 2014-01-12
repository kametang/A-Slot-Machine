#include <stdio.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include <driver/led.h>
#include <driver/dc_motor.h>

#include <common/coin.h>
#include <common/stuff.h>

#define msgShow(s) ({SetWindowText(msgbox, s); UpdateWindow(msgbox, TRUE);})
#define moneyUpdate() ({sprintf(buf, "%d", money); msgShow(buf);})
#define stuffSoldout(w) ({SetWindowText(w, soldout); redText(w); })
#define enableWindow(w) ({EnableWindow(w, TRUE); SetNullFocus(hMainWnd);})
#define disableWindow(w) ({EnableWindow(w, FALSE); SetNullFocus(hMainWnd);})
#define redText(w) ({SetWindowElementColorEx(w, FGC_CONTROL_NORMAL, COLOR_red); UpdateWindow(w, TRUE);})
#define errorMsg(s) ({msgShow(s); sleep(2); moneyUpdate();})

// Defination
typedef enum{
    MSGBOX=1, BTN_REFUND,
    BTN_S1, BTN_S2, BTN_S3, STA_S1, STA_S2, STA_S3,
    BTN_C50, BTN_C10, BTN_C5, BTN_C1//, STA_C50, STA_C10, STA_C5, STA_C1
}OBJ_ID;

// resource
BITMAP pic_stuff1, pic_stuff2, pic_stuff3;
BITMAP pic_bk;

HWND hMainWnd;

// Object in Window
HWND msgbox;    // Top Area for show message
HWND btn_stuff1, btn_stuff2, btn_stuff3;    // Stuff Buy Button
HWND status_stuff1, status_stuff2, status_stuff3;   // Is Stuff Sold out
HWND btn_refund;    // Refund coin
HWND btn_coin50, btn_coin10, btn_coin5, btn_coin1;  // Coin Button

HDC p1, p2, p3;

int money = 0;
char buf[128] = {0};

COIN coin50, coin10, coin5, coin1;
STUFF stuff1, stuff2, stuff3;
#define priceLabel1 "$18"
#define priceLabel2 "$15"
#define priceLabel3 "$22"
#define soldout "Sold Out"

LED_MAP map;
u16 pattern[8] = {0x38, 0x6C, 0x7C, 0x44, 0x44, 0x44, 0x6C, 0x38};
int ledfd;
int dcmfd;

static void refundAction()
{
    int c50, c10, c5, c1, m;

    if(money == 0)
        return;
    DCM_High(dcmfd);
    m = money;
    c50 = money/50;
    if(c50 > 0){
        coinRefund(&coin50, c50);
        enableWindow(btn_coin50);
    }
    money %= 50;
    c10 = money/10;
    if(c10 > 0){
        coinRefund(&coin10, c10);
        enableWindow(btn_coin10);
    }
    money %= 10;
    c5 = money/5;
    if(c5 > 0){
        coinRefund(&coin5, c5);
        enableWindow(btn_coin5);
    }
    money %= 5;
    c1 = money;
    if(c1 > 0){
        coinRefund(&coin1, c1);
        enableWindow(btn_coin1);
    }
    money = 0;
    sprintf(buf, "(Refund) $50:%d    $10:%d    $5:%d    $1:%d    Total:$%d", c50, c10, c5, c1, m);
    msgShow(buf);
    disableWindow(btn_refund);
    DCM_Off(dcmfd);
}

static void buyStuff(HWND hWnd, int id, int nc, DWORD add_data)
{
    if(nc == BN_CLICKED){
        switch(id){
            case BTN_S1:
                if(stuffGetStatus(&stuff1) == STUFF_EMPTY){
                    errorMsg("This stuff is sold out.");
                    break;
                }
                if(money < stuffGetPrice(&stuff1)){
                    errorMsg("You don't slot enough.");
                    break;
                }
                money -= stuffGetPrice(&stuff1);
                moneyUpdate();
                stuffBuy(&stuff1);
                DCM_High(dcmfd);
                LED_MAP_RollDown(ledfd, &map);
                if(stuffGetStatus(&stuff1) == STUFF_EMPTY){
                    stuffSoldout(status_stuff1);
                    disableWindow(btn_stuff1);
                }
                refundAction();
                break;
            case BTN_S2:
                if(stuffGetStatus(&stuff2) == STUFF_EMPTY){
                    errorMsg("This stuff is sold out.");
                    break;
                }
                if(money < stuffGetPrice(&stuff2)){
                    errorMsg("You don't slot enough.");
                    break;
                }
                money -= stuffGetPrice(&stuff2);
                moneyUpdate();
                stuffBuy(&stuff2);
                DCM_High(dcmfd);
                LED_MAP_RollDown(ledfd, &map);
                if(stuffGetStatus(&stuff2) == STUFF_EMPTY)
                    stuffSoldout(status_stuff2);
                refundAction();
                break;
            case BTN_S3:
                if(stuffGetStatus(&stuff3) == STUFF_EMPTY){
                    errorMsg("This stuff is sold out.");
                    break;
                }
                if(money < stuffGetPrice(&stuff3)){
                    errorMsg("You don't slot enough.");
                    break;
                }
                money -= stuffGetPrice(&stuff3);
                moneyUpdate();
                stuffBuy(&stuff3);
                DCM_High(dcmfd);
                LED_MAP_RollDown(ledfd, &map);
                if(stuffGetStatus(&stuff3) == STUFF_EMPTY)
                    stuffSoldout(status_stuff3);
                refundAction();
                break;
        }
    }
}
static void refundCoin(HWND hWnd, int id, int nc, DWORD add_data)
{
    if(nc == BN_CLICKED)
        refundAction();
}
static void coinAction(HWND hWnd, int id, int nc, DWORD add_data)
{
    HDC t;
    if(nc == BN_CLICKED){
        switch(id){
            case BTN_C50:
                if(coinGetStatus(&coin50) == COIN_FULL){
                    errorMsg("You can't slot $50's slot, due to full slot.");
                    break;
                }
                coinSloting(&coin50);
                money += 50;
                moneyUpdate();
                if(coinGetStatus(&coin50) == COIN_FULL)
                    disableWindow(hWnd);
                break;
            case BTN_C10:
                if(coinGetStatus(&coin10) == COIN_FULL){
                    errorMsg("You can't slot $10's slot, due to full slot.");
                    break;
                }
                coinSloting(&coin10);
                money += 10;
                moneyUpdate();
                if(coinGetStatus(&coin10) == COIN_FULL)
                    disableWindow(hWnd);
                break;
            case BTN_C5:
                if(coinGetStatus(&coin5) == COIN_FULL){
                    errorMsg("You can't slot $5's slot, due to full slot.");
                    break;
                }
                coinSloting(&coin5);
                money += 5;
                moneyUpdate();
                if(coinGetStatus(&coin5) == COIN_FULL)
                    disableWindow(hWnd);
                break;
            case BTN_C1:
                if(coinGetStatus(&coin1) == COIN_FULL){
                    errorMsg("You can't slot $1's slot, due to full slot.");
                    break;
                }
                coinSloting(&coin1);
                money += 1;
                moneyUpdate();
                if(coinGetStatus(&coin1) == COIN_FULL)
                    disableWindow(hWnd);
                break;
        }
        if(money > 0)
            enableWindow(btn_refund);
    }
}

static int MainHandler(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    int id   = LOWORD(lParam);
    int code = HIWORD(lParam);

    switch (message) {
        case MSG_CREATE:
            FillBoxWithBitmap(HDC_SCREEN, 0, 20, 480, 272, &pic_bk);
            // Initial Objects
            msgbox = CreateWindow(CTRL_STATIC, "It's sloting time!", 
                                  WS_CHILD | WS_VISIBLE | SS_RIGHT | WS_BORDER,
                                  MSGBOX, 10, 10, 460, 20, hWnd, 0);
            LoadBitmap(p1, &pic_stuff1, "./img/stuff1.bmp");
            btn_stuff1 = CreateWindow(CTRL_BUTTON, "Stuff1",
                                      WS_CHILD | BS_PUSHBUTTON | BS_BITMAP | BS_NOTIFY | WS_VISIBLE,
                                      BTN_S1, 10, 40, 100, 100, hWnd, (DWORD)&pic_stuff1);
            LoadBitmap(p2, &pic_stuff2, "./img/stuff2.bmp");
            btn_stuff2 = CreateWindow(CTRL_BUTTON, "Stuff2",
                                      WS_CHILD | BS_PUSHBUTTON | BS_BITMAP | BS_NOTIFY | WS_VISIBLE,
                                      BTN_S2, 190, 40, 100, 100, hWnd, (DWORD)&pic_stuff2);
            LoadBitmap(p3, &pic_stuff3, "./img/stuff3.bmp");
            btn_stuff3 = CreateWindow(CTRL_BUTTON, "Stuff3",
                                      WS_CHILD | BS_PUSHBUTTON | BS_BITMAP | BS_NOTIFY | WS_VISIBLE,
                                      BTN_S3, 370, 40, 100, 100, hWnd, (DWORD)&pic_stuff3);
            SetNotificationCallback(btn_stuff1, buyStuff);
            SetNotificationCallback(btn_stuff2, buyStuff);
            SetNotificationCallback(btn_stuff3, buyStuff);
            status_stuff1 = CreateWindow(CTRL_STATIC, priceLabel1,
                                         WS_CHILD | SS_CENTER | WS_VISIBLE,
                                         STA_S1, 10, 150, 100, 20, hWnd, 0);
            status_stuff2 = CreateWindow(CTRL_STATIC, priceLabel2,
                                         WS_CHILD | SS_CENTER | WS_VISIBLE,
                                         STA_S2, 190, 150, 100, 20, hWnd, 0);
            status_stuff3 = CreateWindow(CTRL_STATIC, priceLabel3,
                                         WS_CHILD | SS_CENTER | WS_VISIBLE,
                                         STA_S3, 370, 150, 100, 20, hWnd, 0);
            btn_refund = CreateWindow(CTRL_BUTTON, "Refund Coin",
                                      WS_CHILD | BS_PUSHBUTTON | BS_NOTIFY | WS_VISIBLE,
                                      BTN_REFUND, 10, 180, 100, 40, hWnd, 0);
            SetNotificationCallback(btn_refund, refundCoin);
            EnableWindow(btn_refund, FALSE);
            btn_coin50 = CreateWindow(CTRL_BUTTON, "50",
                                      WS_CHILD | BS_PUSHBUTTON | BS_NOTIFY | WS_VISIBLE,
                                      BTN_C50, 180, 180, 40, 40, hWnd, 0);
            btn_coin10 = CreateWindow(CTRL_BUTTON, "10",
                                      WS_CHILD | BS_PUSHBUTTON | BS_NOTIFY | WS_VISIBLE,
                                      BTN_C10, 260, 180, 40, 40, hWnd, 0);
            btn_coin5 = CreateWindow(CTRL_BUTTON, "5",
                                      WS_CHILD | BS_PUSHBUTTON | BS_NOTIFY | WS_VISIBLE,
                                      BTN_C5, 340, 180, 40, 40, hWnd, 0);
            btn_coin1 = CreateWindow(CTRL_BUTTON, "1",
                                      WS_CHILD | BS_PUSHBUTTON | BS_NOTIFY | WS_VISIBLE,
                                      BTN_C1, 420, 180, 40, 40, hWnd, 0);
            SetNotificationCallback(btn_coin50, coinAction);
            SetNotificationCallback(btn_coin10, coinAction);
            SetNotificationCallback(btn_coin5, coinAction);
            SetNotificationCallback(btn_coin1, coinAction);
            return 0;
        case MSG_ERASEBKGND:
            return 0;
        case MSG_TIMER:
            break;
        case MSG_PAINT:
            hdc = BeginPaint(hWnd);
            EndPaint(hWnd, hdc);
            return 0;
        case MSG_KEYDOWN:
            return 0;
        case MSG_CLOSE:
            DestroyMainWindow(hWnd);
            PostQuitMessage(hWnd);
            return 0;
    }

    return DefaultMainWinProc(hWnd, message, wParam, lParam);
}

int MiniGUIMain (int argc, const char* argv[])
{
    MSG Msg;
    MAINWINCREATE CreateInfo;

    ledfd = LED_Init();
    dcmfd = DCM_Init();
    coinInit(&coin50, COIN_50, 99);
    coinInit(&coin10, COIN_10, 50);
    coinInit(&coin5, COIN_5, 50);
    coinInit(&coin1, COIN_1, 50);
    stuffInit(&stuff1, 1, 18);
    stuffInit(&stuff2, 10, 15);
    stuffInit(&stuff3, 10, 22);
    LED_MAP_Create(&map, pattern);

    LoadBitmap(HDC_SCREEN, &pic_bk, "./img/bk.bmp");

    JoinLayer(NULL , "ASM" , 0 , 0);

    CreateInfo.dwStyle = WS_VISIBLE | WS_BORDER | WS_CAPTION;
    CreateInfo.dwExStyle = WS_EX_NONE;
    CreateInfo.spCaption = "A Slot Machine - Simulator";
    CreateInfo.hMenu = 0;
    CreateInfo.hCursor = GetSystemCursor(0);
    CreateInfo.hIcon = 0;
    CreateInfo.MainWindowProc = MainHandler;
    CreateInfo.lx = 0;
    CreateInfo.ty = 0;
    CreateInfo.rx = 480;//g_rcScr.right;
    CreateInfo.by = 272;//g_rcScr.bottom;
    CreateInfo.iBkColor = COLOR_lightwhite;
    CreateInfo.dwAddData = 0;
    CreateInfo.hHosting = HWND_DESKTOP;
    
    hMainWnd = CreateMainWindow (&CreateInfo);
    
    if (hMainWnd == HWND_INVALID)
        return -1;

    ShowWindow(hMainWnd, SW_SHOWNORMAL);

    while (GetMessage(&Msg, hMainWnd)) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    MainWindowThreadCleanup (hMainWnd);

    return 0;
}
#ifndef _LITE_VERSION
#include <minigui/dti.c>
#endif

