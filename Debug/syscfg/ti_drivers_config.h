/*
 *  ======== ti_drivers_config.h ========
 *  Configured TI-Drivers module declarations
 *
 *  DO NOT EDIT - This file is generated for the CC3220S_LAUNCHXL
 *  by the SysConfig tool.
 */
#ifndef ti_drivers_config_h
#define ti_drivers_config_h

#define CONFIG_SYSCONFIG_PREVIEW

#define CONFIG_CC3220S_LAUNCHXL

#ifndef DeviceFamily_CC3220
#define DeviceFamily_CC3220
#endif

#include <ti/devices/DeviceFamily.h>

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif


/*
 *  ======== Capture ========
 */

/* P03 */
#define TEMP_CAPTURE                0


/*
 *  ======== Crypto ========
 */

#define CONFIG_Crypto_0             0

/*
 *  ======== GPIO ========
 */

/* P63 */
#define D_7                         0
/* P53 */
#define D_6                         1
/* P64 */
#define D_5                         2
/* P50 */
#define D_4                         3
/* P18 */
#define LCD_E                       4
/* P02 */
#define LCD_Rs                      5
/* P04 */
#define Relay1                      6
/* P62 */
#define Relay2                      7
/* P06 */
#define UP                          8
/* P61 */
#define DOWN                        9
/* P15 */
#define ENTER                       10
/* P05 */
#define Temp_pin                    11

/* LEDs are active high */
#define CONFIG_GPIO_LED_ON  (1)
#define CONFIG_GPIO_LED_OFF (0)

#define CONFIG_LED_ON  (CONFIG_GPIO_LED_ON)
#define CONFIG_LED_OFF (CONFIG_GPIO_LED_OFF)


/*
 *  ======== PWM ========
 */

/* P1 */
#define CONFIG_PWM_0                0


/*
 *  ======== SPI ========
 */

#define CONFIG_NWP_SPI               0



/*
 *  ======== Timer ========
 */

#define CONFIG_TIMER_0              0
#define Reading_Timer               1

/*
 *  ======== UART ========
 */

/*
 *  TX: P07
 *  RX: P08
 */
#define UART_CO2                    0


/*
 *  ======== Board_init ========
 *  Perform all required TI-Drivers initialization
 *
 *  This function should be called once at a point before any use of
 *  TI-Drivers.
 */
extern void Board_init(void);

/*
 *  ======== Board_initGeneral ========
 *  (deprecated)
 *
 *  Board_initGeneral() is defined purely for backward compatibility.
 *
 *  All new code should use Board_init() to do any required TI-Drivers
 *  initialization _and_ use <Driver>_init() for only where specific drivers
 *  are explicitly referenced by the application.  <Driver>_init() functions
 *  are idempotent.
 */
#define Board_initGeneral Board_init

#ifdef __cplusplus
}
#endif

#endif /* include guard */
