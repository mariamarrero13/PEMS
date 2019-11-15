/*
 * IRBlaster.c
 *
 *  Created on: Nov 3, 2019
 *      Author: diego
 */

/* For usleep() */
#include "IRBlaster.h"
#include <unistd.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/PWM.h>
#include <ti/drivers/Timer.h>
/* Driver configuration */
#include "ti_drivers_config.h"
//Our timer to count Between pulses
Timer_Handle timer0;
Timer_Params params;
PWM_Handle pwm1 ;

int ARRAY_ON [49]=  {1,0,1,1, 0,0,1,0, 0,1,0,0, 1,1,0,1, 0,0,0,1, 1,1,1,1, 1,1,1,0, 0,0,0,0, 0,1,1,1, 0,0,0,0, 1,0,0,0, 1,1,1,1, 0  };

int ARRAY_OFF [49]= {1,0,1,1, 0,0,1,0, 0,1,0,0, 1,1,0,1, 0,1,1,1, 1,0,1,1, 1,0,0,0, 0,1,0,0, 1,1,1,0, 0,0,0,0, 0,0,0,1, 1,1,1,1, 0  };

int j;
int i;
//Timer Function To stop PWM PIN from Transmitting


//Our timer to count Between pulses



//SAMSUNG PROTOCOL START METHOD
void COMENZAR(PWM_Handle pwm1)
{

    //Start Signal
    Timer_setPeriod(timer0,Timer_PERIOD_US,4500);
    PWM_start(pwm1);

    Timer_start(timer0);
    PWM_stop(pwm1);

    Timer_start(timer0);


}

//SAMSUNG PROTOCOL TO PRINT LOGIC 1 in IR
void UNO(PWM_Handle pwm1)
{
    Timer_setPeriod(timer0,Timer_PERIOD_US,560);
    PWM_start(pwm1);

    Timer_start(timer0);
    PWM_stop(pwm1);


    Timer_setPeriod(timer0,Timer_PERIOD_US,1690);
    Timer_start(timer0);


}

//SAMSUNG PROTOCOL TO PRINT LOGIC 0 IN IR
void ZERO(PWM_Handle pwm1)
{
    Timer_setPeriod(timer0,Timer_PERIOD_US,560);
    PWM_start(pwm1);
    //Zero Signal

    Timer_start(timer0);

    PWM_stop(pwm1);

    Timer_start(timer0);
}

void IR_Init(){
    Timer_init();

    Timer_Params_init(&params);
    params.period = 4500;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_ONESHOT_BLOCKING;
    params.timerCallback = timerCallback;

    timer0 = Timer_open(CONFIG_TIMER_0, &params);

    /* Period and duty in microseconds */
    uint16_t   pwmPeriod = 38000;
    uint16_t   duty = 0;


    PWM_Params paramsPWM;

    /* Call driver init functions. */
    PWM_init();

    PWM_Params_init(&paramsPWM);
    paramsPWM.dutyUnits = PWM_DUTY_FRACTION;
    paramsPWM.dutyValue = duty;
    paramsPWM.periodUnits = PWM_PERIOD_HZ;
    paramsPWM.periodValue = pwmPeriod;
    pwm1 = PWM_open(CONFIG_PWM_0, &paramsPWM);

    PWM_setDuty(pwm1,(PWM_DUTY_FRACTION_MAX/2));
}

void turn_AC_ON()
{
    for(j=0;j<2;j++)
    {
        COMENZAR(pwm1);

        for(i=0;i<49;i++)
        {
            if(ARRAY_ON[i]==1)
                UNO(pwm1);
            else
                ZERO(pwm1);
        }
        usleep(4200);
    }
}

void turn_AC_OFF()
{
    for(j=0;j<2;j++)
    {
        COMENZAR(pwm1);

        for(i=0;i<49;i++)
        {
            if(ARRAY_OFF[i]==1)
                UNO(pwm1);
            else
                ZERO(pwm1);
        }
        usleep(4200);
    }
}

void timerCallback(Timer_Handle myHandle)
{
    PWM_stop(pwm1);
}
