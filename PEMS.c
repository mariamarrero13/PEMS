#include <unistd.h>
#include <ctype.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/Capture.h>
#include <ti/drivers/Timer.h>
#include "ti_drivers_config.h"
#include "lcd.h"
#include "IRBlaster.h"
#include "MHZ16.h"
#include "dht22.h"
/*
 * PIN MAPING
 * LCD: 63,53,64,50,02,18
 * Rotary: 06,21,15
 * CO2: 07,08
 * Relay: 61,62
 * IR LED: 01
 * DHT22: 03,05
 */

//methods

void cursor_moveto(uint8_t y, uint8_t x);
void thresholdMax(uint8_t i);
void thresholdMin(uint8_t i);
void relayOne();
void relayTwo();

//variables
Timer_Handle timer;
Timer_Params params;

UART_Handle CO2uart;
UART_Params CO2params;

Capture_Handle captHandle;
Capture_Params captParams;

uint8_t buffer[];
uint8_t edit = 0;
uint8_t screen = 0;
uint8_t c_pos = 0;
uint8_t cursor = 0;
uint8_t s_text [5][4][20] = {{"Last Reading","Temp","Hum", "CO2"},
                             {" Temp Config"," Hum Config"," CO2 Config", " Exit"},
                             {"Temp Config"," Min"," Max", " Exit"},
                             {"Humi Config"," Min"," Max", " Exit"},
                             {"CO2 Config"," Min"," Max", " Exit"}};
uint32_t finaldata[3];
uint16_t seconds = 0;
// limits variable
uint16_t maxT = 75;
uint16_t minT = 65;
uint16_t maxH = 95;
uint16_t minH = 60;
uint16_t maxC = 1200;
uint16_t minC = 400;

//weather variables
uint16_t Temp = 100.0;
uint16_t Hum = 89.7;
uint16_t CO = 0.0;

// Device Status
uint8_t T = 0;
uint8_t H = 0;
uint8_t C = 0;

//Relay variables (flags)
uint8_t R1 = 0;
uint8_t R2 = 0;

//Encoder flags
uint8_t flag = 1;
uint8_t olda = 0;
uint8_t oldb = 0;
uint8_t newa = 0;
uint8_t newb = 0;
uint8_t lookup_index =0;

//****Update text Module****//
void update_text(){
    if(screen == 0) lcd_command(Display_on_nc);
    else lcd_command(Display_on);
    lcd_command(Clear);
    cursor = 0;
    cursor_moveto(0, 0);
    lcd_string(s_text[screen][0]);
    cursor_moveto(1, 0);
    lcd_string(s_text[screen][1]);
    cursor_moveto(2, 0);
    lcd_string(s_text[screen][2]);
    cursor_moveto(3, 0);
    lcd_string(s_text[screen][3]);
    if(screen ==2 || screen ==3 || screen ==4){
        cursor_moveto(1, 0);
        cursor =1 ;
    }
    else {
        cursor_moveto(0, 0);
        cursor = 0;
    }
}

//****cursor Module****//
void cursor_moveto(uint8_t y, uint8_t x){
    switch(y){
    case 0:
        lcd_command(lcd_SetCursor|lcd_LineOne+x);
        break;
    case 1:
        lcd_command(lcd_SetCursor|lcd_LineTwo+x);
        break;
    case 2:
        lcd_command(lcd_SetCursor|lcd_LineThree+x);
        break;
    case 3:
        lcd_command(lcd_SetCursor|lcd_LineFour+x);
        break;
    }
}

//****Update val Module****//
void update_values(){
    switch(screen){
    case 0:
        cursor_moveto(1, 12);
        sprintf(buffer, "%03d F",Temp);
        lcd_string(buffer);

        cursor_moveto(2, 12);
        sprintf(buffer, "%03d",Hum);
        lcd_string(buffer);
        lcd_string(" %");

        cursor_moveto(3,12);
        sprintf(buffer, "%03d PPM",CO);
        lcd_string(buffer);

        cursor_moveto(0,0);
        cursor = 4;
        break;
    case 2:
        cursor_moveto(1, 14);
        sprintf(buffer, "%03d F",minT);
        lcd_string(buffer);

        cursor_moveto(2,14);
        sprintf(buffer, "%03d F",maxT);
        lcd_string(buffer);

        if(edit) cursor_moveto(cursor,19);
        else cursor_moveto(cursor, 0);
        break;
    case 3:
        cursor_moveto(1, 14);
        sprintf(buffer, "%03d",minH);
        lcd_string(buffer);
        lcd_string(" %");

        cursor_moveto(2,14);
        sprintf(buffer, "%03d",maxH);
        lcd_string(buffer);
        lcd_string(" %");

        if(edit) cursor_moveto(cursor,19);
        else cursor_moveto(cursor, 0);
        break;
    case 4:
        cursor_moveto(1, 13);
        sprintf(buffer, "%03d PPM",minC);
        lcd_string(buffer);

        cursor_moveto(2,13);
        sprintf(buffer, "%03d PPM",maxC);
        lcd_string(buffer);

        if(edit) cursor_moveto(cursor,19);
        else cursor_moveto(cursor, 0);
        break;
    }

}

/*****ROTARY SUBSTITUTE*****/

void up_arrows(){ //uint_least8_t index
    if (screen == 1 && cursor != 0) //selecting a config
        cursor_moveto(--cursor, 0);
    else if (screen == 2 || screen ==3 || screen==4){
        if(edit) //editing a value
        {
            if(cursor == 1)
                thresholdMin(1);
            else if (cursor ==2)
                thresholdMax(1);
        }
        else // just moving around screen
        {
            if (cursor != 1) cursor_moveto(--cursor, 0);
        }
    }

}

void down_arrows(){ //uint_least8_t index
    if (screen == 1 && cursor != 3)  //selecting a config
        cursor_moveto(++cursor, 0);
    else if (screen == 2 || screen ==3 || screen==4){
        if(edit) //editing a value
        {
            if(cursor == 1)
                thresholdMin(2);
            else if (cursor ==2)
                thresholdMax(2);
        }
        else // just moving around screen
        {
            if (cursor != 3) cursor_moveto(++cursor, 0);
        }
    }

}


//****SW ISR Module****//
void enter(){ //uint_least8_t index
    if(screen == 0){
        screen = 1;
        update_text();
    }
    else if(screen == 1){
        switch(cursor){
        case 0:
            screen = 2;
            update_text();
            update_values();
            break;
        case 1:
            screen = 3;
            update_text();
            update_values();
            break;
        case 2:
            screen = 4;
            update_text();
            update_values();
            break;
        case 3:
            screen = 0;
            update_text();
            update_values();
            break;
        }
    }
    else if(screen == 2||screen ==3 ||screen ==4){
        switch(cursor){
        case 1:
            if(edit == 0){
                edit = 1;
                cursor_moveto(cursor, 19);
            }
            else{
                edit = 0;
                cursor_moveto(cursor, 0);
            }
            break;
        case 2:
            if(edit == 0){
                edit = 1;
                cursor_moveto(cursor, 19);
            }
            else{
                edit = 0;
                cursor_moveto(cursor, 0);
            }
            break;
        case 3:
            screen = 1;
            update_text();
            break;
        }
    }
}
void execute_reading(){
    Timer_stop(timer);
    Timer_close(timer);

    lcd_command(Clear);
    lcd_string("Sensing...");
    lcd_command(lcd_SetCursor|lcd_LineTwo);
    lcd_string("CO2");
    CO = readMHZ16();
    lcd_command(lcd_SetCursor|lcd_LineThree);
    lcd_string("Temp and Humidity");
    initCapture(captHandle);
//    do
//    {
        sleep(2);
        DHT_read(finaldata);
        Temp = finaldata[2];
        Hum = finaldata[0];
//    }
//    while (Hum == 0);
    lcd_command(lcd_SetCursor|lcd_LineFour);
    lcd_string("Done!");
    restartCapture();
    sleep(2);
    lcd_command(Clear);
    lcd_string("Posting to DB...");
    mainPost((int)Temp,(int)Hum, (int)CO);
    lcd_string("Done");
    sleep(2);
    update_text();
    update_values();
    if (Temp <= minT && T){
        turn_AC_OFF();
        T = 0;
    }
    if (Temp >= maxT && T ==0){
        turn_AC_ON();
        T = 1;
    }
    if(Hum <=minH && H==0){
        GPIO_write(Relay2, 0);
        H = 1;
    }
    if(Hum >=maxH && H){
        GPIO_write(Relay2, 1);
        H = 0;
    }
    if(CO >= maxC && C==0){
        GPIO_write(Relay2, 0);
        C = 1;
    }
    if(CO <= minC  && C){
        GPIO_write(Relay2, 1);
        C = 0;
    }
    timer = Timer_open(Reading_Timer, &params);
    Timer_start(timer);
}

//****Timer CallBack ******//
void timer_callback(Timer_Handle myHandle){ //Timer_Handle myHandle
    seconds ++;
}
//****Main Module****//
void *mainThread(void *arg0){
    GPIO_init();
    Timer_init();
    UART_init();
    Capture_init();

    IR_Init();
    UART_CO2_init(CO2uart,CO2params);
    DHT_begin(Temp_pin);

    GPIO_setConfig(Relay1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(Relay2, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);


    lcd_init_4bit(D_7, D_6, D_5, D_4, LCD_Rs, LCD_E);
    lcd_init_4bit(D_7, D_6, D_5, D_4, LCD_Rs, LCD_E);

    Timer_Params_init(&params);
    params.period = 1;
    params.periodUnits = Timer_PERIOD_HZ;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timer_callback;
    timer = Timer_open(Reading_Timer, &params);

    lcd_command(Clear);
    lcd_string("Testing Systems: ");
    lcd_command(lcd_SetCursor|lcd_LineTwo);
    //         testing AC and relays
    sleep(1);
    lcd_string("AC OFF ");
    turn_AC_OFF();
    sleep(5);
    lcd_string("-> AC ON");
    turn_AC_ON();
    lcd_command(lcd_SetCursor|lcd_LineThree);
    lcd_string("Relay ON");
    sleep(1);
    GPIO_write(Relay1, 0);
    GPIO_write(Relay2, 0);
    sleep(1);
    lcd_string("-> Relay OFF");
    GPIO_write(Relay1, 1);
    GPIO_write(Relay2, 1);
    sleep(2);
    Timer_start(timer);
    execute_reading();

    while(1)
    {
        if(seconds == 60){
            seconds =0;
            execute_reading();

        }
        if(GPIO_read(ENTER)){
            while(GPIO_read(ENTER)){}
            enter();
        }
        if(GPIO_read(UP)){
            while(GPIO_read(UP)){}
            up_arrows();
        }
        if(GPIO_read(DOWN)!=0){
            while(GPIO_read(DOWN)!=0){}
            down_arrows();
        }
    }
    return (NULL);
}

//****Thresholds Module****//
void thresholdMax(uint8_t i){
    //add update value where necessary
    if(screen == 2){
        if(i == 1 && maxT != 100 && minT<maxT-1){
            maxT++;
            update_values();
        }
        else if (i == 2 && maxT != 0 && minT<maxT-1){
            maxT--;
            update_values();
        }
    }
    else if(screen == 3){
        if(i == 1 && maxH != 101 && minH<maxH-1){
            maxH++;
            update_values();
        }
        else if (i == 2 && maxH !=0 && minH<maxH-1){
            maxH--;
            update_values();
        }
    }
    else if(screen == 4){
        if(i == 1 && maxC != 10000 && minC<maxC-1){
            maxC++;
            update_values();
        }
        else if (i == 2 && maxC != 0 && minC<maxC-1){
            maxC--;
            update_values();
        }
    }
}

void thresholdMin(uint8_t i){
    //add update value where necessary
    if(screen == 2){
        if(i == 1 && minT!=100 && minT<maxT-1){
            minT++;
            update_values();
        }
        else if (i == 2 && minT != 0 && minT<maxT-1)  {
            minT--;
            update_values();
        }
    }
    else if(screen == 3){
        if(i == 1 && minH != 100 && minH<maxH-1){
            minH++;
            update_values();
        }
        else if (i == 2 && minH !=0&& minH<maxH-1){
            minH--;
            update_values();
        }
    }
    else if(screen == 4){
        if(i == 1 && minC != 10000 && minC<maxC-1){
            minC++;
            update_values();
        }
        else if (i == 2 && minC !=0 && minC<maxC-1){
            minC--;
            update_values();
        }
    }
}

//****Relay Module****//
void relayOne(){
    if(R1 == 0 && Temp == 1){
        GPIO_write(Relay1, 0);
    }
    else{
        GPIO_write(Relay1, 1);
    }
}

void relayTwo(){
    if(R2 == 0 && Hum == 1){
        GPIO_write(Relay2, 0);
    }
    else{
        GPIO_write(Relay2, 1);
    }
}
