/*
 * lcd.c
 *```
 *  Created on: Sep 19, 2019
 *      Author: maria
 */
#include "lcd.h"
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "ti_drivers_config.h"
#include <ti/drivers/GPIO.h>

void lcd_init_4bit(uint_least8_t pD7, uint_least8_t pD6, uint_least8_t pD5, uint_least8_t pD4, uint_least8_t pRs, uint_least8_t pE)
{
    D7 = pD7;
    D6 = pD6;
    D5 = pD5;
    D4 = pD4;
    Rs = pRs;
    E  = pE;
    GPIO_setConfig(D7, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW); //D7    p18
    GPIO_setConfig(D6, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW); //D6    p08
    GPIO_setConfig(D5, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW); //D5    p07
    GPIO_setConfig(D4, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW); //D4    p06
    GPIO_setConfig(Rs, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW); //RS    p21
    GPIO_setConfig(E, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW); //E     p15

    // Power-up delay
    usleep(40000);

    //Initialization
    lcd_byte(FunctionReset);
    usleep(50);

    lcd_command(FunctionSet);
    usleep(50);

    lcd_command(FunctionSet);
    usleep(50);

    lcd_command(Display_off);
    usleep(50);

    lcd_command(Clear);
    usleep(1600);

    lcd_command(lcd_EntryMode);
    usleep(50);

    lcd_command(Display_on);
    usleep(50);

}


void lcd_string(uint8_t word[])
{
    volatile int i = 0;
    while (word[i] != 0)
    {
        lcd_character(word[i]);
        i++;
        usleep(40);
    }
}

void lcd_character(uint8_t character)
{
    GPIO_write(Rs, 1);               // Data Register

    lcd_byte(character);                                // write the data
    lcd_byte(character<<4);
}

void lcd_command(uint8_t command)
{
    GPIO_write(Rs, 0);              // Instruction Register

    lcd_byte(command);                         // write the instruction
    lcd_byte(command << 4);                         // write the instruction
}

void lcd_byte(uint8_t byte)
{
    GPIO_write(D7,(unsigned int)(1 & (byte >> 7 )));
    GPIO_write(D6,(unsigned int)(1 & (byte >> 6 )));
    GPIO_write(D5,(unsigned int)(1 & (byte >> 5 )));
    GPIO_write(D4,(unsigned int)(1 & (byte >> 4 )));

    // write the data
    usleep(.50);
    GPIO_write(E,1);
    usleep(.50);
    GPIO_write(E,0);
    usleep(.5);
}
