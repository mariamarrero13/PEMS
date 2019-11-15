################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../CC3220S_LAUNCHXL_TIRTOS.cmd 

SYSCFG_SRCS += \
../empty.syscfg 

C_SRCS += \
../IRBlaster.c \
../MHZ16.c \
../PEMS.c \
../dht22.c \
./syscfg/ti_drivers_net_wifi_config.c \
./syscfg/ti_drivers_config.c \
../httpget.c \
../lcd.c \
../main_post.c \
../main_tirtos.c \
../platform.c 

GEN_FILES += \
./syscfg/ti_drivers_net_wifi_config.c \
./syscfg/ti_drivers_config.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./IRBlaster.d \
./MHZ16.d \
./PEMS.d \
./dht22.d \
./syscfg/ti_drivers_net_wifi_config.d \
./syscfg/ti_drivers_config.d \
./httpget.d \
./lcd.d \
./main_post.d \
./main_tirtos.d \
./platform.d 

OBJS += \
./IRBlaster.obj \
./MHZ16.obj \
./PEMS.obj \
./dht22.obj \
./syscfg/ti_drivers_net_wifi_config.obj \
./syscfg/ti_drivers_config.obj \
./httpget.obj \
./lcd.obj \
./main_post.obj \
./main_tirtos.obj \
./platform.obj 

GEN_MISC_FILES += \
./syscfg/ti_drivers_config.h \
./syscfg/syscfg_c.rov.xs 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"IRBlaster.obj" \
"MHZ16.obj" \
"PEMS.obj" \
"dht22.obj" \
"syscfg\ti_drivers_net_wifi_config.obj" \
"syscfg\ti_drivers_config.obj" \
"httpget.obj" \
"lcd.obj" \
"main_post.obj" \
"main_tirtos.obj" \
"platform.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\ti_drivers_config.h" \
"syscfg\syscfg_c.rov.xs" 

C_DEPS__QUOTED += \
"IRBlaster.d" \
"MHZ16.d" \
"PEMS.d" \
"dht22.d" \
"syscfg\ti_drivers_net_wifi_config.d" \
"syscfg\ti_drivers_config.d" \
"httpget.d" \
"lcd.d" \
"main_post.d" \
"main_tirtos.d" \
"platform.d" 

GEN_FILES__QUOTED += \
"syscfg\ti_drivers_net_wifi_config.c" \
"syscfg\ti_drivers_config.c" 

C_SRCS__QUOTED += \
"../IRBlaster.c" \
"../MHZ16.c" \
"../PEMS.c" \
"../dht22.c" \
"./syscfg/ti_drivers_net_wifi_config.c" \
"./syscfg/ti_drivers_config.c" \
"../httpget.c" \
"../lcd.c" \
"../main_post.c" \
"../main_tirtos.c" \
"../platform.c" 

SYSCFG_SRCS__QUOTED += \
"../empty.syscfg" 


