################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
PEMS-master/%.obj: ../PEMS-master/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/diego/Documents/UNI/MICRO_2/Lab/WIFI/httpget_CC3220S_LAUNCHXL_tirtos_ccs2" --include_path="C:/Users/diego/Documents/UNI/MICRO_2/Lab/WIFI/httpget_CC3220S_LAUNCHXL_tirtos_ccs2/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_3_30_01_02/source/ti/posix/ccs" --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="PEMS-master/$(basename $(<F)).d_raw" --include_path="C:/Users/diego/Documents/UNI/MICRO_2/Lab/WIFI/httpget_CC3220S_LAUNCHXL_tirtos_ccs2/Debug/syscfg" --obj_directory="PEMS-master" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-316037023:
	@$(MAKE) --no-print-directory -Onone -f PEMS-master/subdir_rules.mk build-316037023-inproc

build-316037023-inproc: ../PEMS-master/empty.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs910/ccs/utils/sysconfig/sysconfig_cli.bat" -s "C:/ti/simplelink_cc32xx_sdk_3_30_01_02/.metadata/product.json" -o "syscfg" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-316037023 ../PEMS-master/empty.syscfg
syscfg/ti_drivers_config.h: build-316037023
syscfg/syscfg_c.rov.xs: build-316037023
syscfg/: build-316037023

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/diego/Documents/UNI/MICRO_2/Lab/WIFI/httpget_CC3220S_LAUNCHXL_tirtos_ccs2" --include_path="C:/Users/diego/Documents/UNI/MICRO_2/Lab/WIFI/httpget_CC3220S_LAUNCHXL_tirtos_ccs2/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_3_30_01_02/source/ti/posix/ccs" --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/diego/Documents/UNI/MICRO_2/Lab/WIFI/httpget_CC3220S_LAUNCHXL_tirtos_ccs2/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


