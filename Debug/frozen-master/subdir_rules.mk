################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
frozen-master/%.obj: ../frozen-master/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/diego/Documents/UNI/MICRO_2/Lab/WIFI/httpget_CC3220S_LAUNCHXL_tirtos_ccs" --include_path="C:/Users/diego/Documents/UNI/MICRO_2/Lab/WIFI/httpget_CC3220S_LAUNCHXL_tirtos_ccs/Debug" --include_path="C:/ti/simplelink_cc32xx_sdk_3_30_01_02/source/ti/posix/ccs" --include_path="C:/ti/ccs910/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/include" -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="frozen-master/$(basename $(<F)).d_raw" --include_path="C:/Users/diego/Documents/UNI/MICRO_2/Lab/WIFI/httpget_CC3220S_LAUNCHXL_tirtos_ccs/Debug/syscfg" --obj_directory="frozen-master" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


