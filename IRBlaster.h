/*
 * IR_HEADER.h
 *
 *  Created on: Nov 3, 2019
 *      Author: diego
 */
#include <stddef.h>
#include <unistd.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/PWM.h>
#include <ti/drivers/Timer.h>
/* Driver configuration */
#include "ti_drivers_config.h"
/* Driver Header files */
#ifndef IR_HEADER_H_
#define IR_HEADER_H_

void timerCallback(Timer_Handle myHandle);

void IR_Init();
void COMENZAR(PWM_Handle pwm1);
void UNO(PWM_Handle pwm1);
void ZERO(PWM_Handle pwm1);
void turn_AC_ON();
void turn_AC_OFF();
void timerCallback(Timer_Handle myHandle);
#endif /* IR_HEADER_H_ */
