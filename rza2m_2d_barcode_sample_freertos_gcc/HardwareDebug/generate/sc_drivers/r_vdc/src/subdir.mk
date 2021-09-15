################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../generate/sc_drivers/r_vdc/src/r_spea.c \
../generate/sc_drivers/r_vdc/src/r_spea_check_parameter.c \
../generate/sc_drivers/r_vdc/src/r_spea_register.c \
../generate/sc_drivers/r_vdc/src/r_spea_register_address.c \
../generate/sc_drivers/r_vdc/src/r_vdc.c \
../generate/sc_drivers/r_vdc/src/r_vdc_check_parameter.c \
../generate/sc_drivers/r_vdc/src/r_vdc_interrupt.c \
../generate/sc_drivers/r_vdc/src/r_vdc_register.c \
../generate/sc_drivers/r_vdc/src/r_vdc_register_address.c \
../generate/sc_drivers/r_vdc/src/r_vdc_shared_param.c 

C_DEPS += \
./generate/sc_drivers/r_vdc/src/r_spea.d \
./generate/sc_drivers/r_vdc/src/r_spea_check_parameter.d \
./generate/sc_drivers/r_vdc/src/r_spea_register.d \
./generate/sc_drivers/r_vdc/src/r_spea_register_address.d \
./generate/sc_drivers/r_vdc/src/r_vdc.d \
./generate/sc_drivers/r_vdc/src/r_vdc_check_parameter.d \
./generate/sc_drivers/r_vdc/src/r_vdc_interrupt.d \
./generate/sc_drivers/r_vdc/src/r_vdc_register.d \
./generate/sc_drivers/r_vdc/src/r_vdc_register_address.d \
./generate/sc_drivers/r_vdc/src/r_vdc_shared_param.d 

OBJS += \
./generate/sc_drivers/r_vdc/src/r_spea.o \
./generate/sc_drivers/r_vdc/src/r_spea_check_parameter.o \
./generate/sc_drivers/r_vdc/src/r_spea_register.o \
./generate/sc_drivers/r_vdc/src/r_spea_register_address.o \
./generate/sc_drivers/r_vdc/src/r_vdc.o \
./generate/sc_drivers/r_vdc/src/r_vdc_check_parameter.o \
./generate/sc_drivers/r_vdc/src/r_vdc_interrupt.o \
./generate/sc_drivers/r_vdc/src/r_vdc_register.o \
./generate/sc_drivers/r_vdc/src/r_vdc_register_address.o \
./generate/sc_drivers/r_vdc/src/r_vdc_shared_param.o 


# Each subdirectory must supply rules for building sources it contributes
generate/sc_drivers/r_vdc/src/%.o: ../generate/sc_drivers/r_vdc/src/%.c
	$(file > $@.in,-mcpu=cortex-a9 -march=armv7-a -marm -mlittle-endian -mfloat-abi=hard -mfpu=neon -mno-unaligned-access -Og -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wmaybe-uninitialized -Wstack-usage=100 -g3 -DNO_ICONV -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/FreeRTOS/include" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/FreeRTOS/include/private" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/FreeRTOS/portable/GCC/ARM_CA9_RZA2M" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/compiler/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/configuration" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/config_files" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/system/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/renesas/application/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/zxing_lib" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/zxing_lib/zxing" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_riic/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_rvapi/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_mipi/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_ceu/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_vdc/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_ostm/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_scifa/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/system/iodefine" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_stb/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_gpio/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/os_abstraction/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_intc/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_cache/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_cbuffer/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_mmu/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_cpg/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_drp/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_drp/src" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_drp/drp_lib" -fabi-version=0 -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo 'arm-none-eabi-gcc -mcpu=cortex-a9 -march=armv7-a -marm -mlittle-endian -mfloat-abi=hard -mfpu=neon -mno-unaligned-access -Og -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wmaybe-uninitialized -Wstack-usage=100 -g3 -DNO_ICONV -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/FreeRTOS/include" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/FreeRTOS/include/private" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/FreeRTOS/portable/GCC/ARM_CA9_RZA2M" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/compiler/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/configuration" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/config_files" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/system/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/renesas/application/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/zxing_lib" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/zxing_lib/zxing" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_riic/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_rvapi/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_mipi/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_ceu/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_vdc/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_ostm/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_scifa/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/system/iodefine" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_stb/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_gpio/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/os_abstraction/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_intc/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_cache/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_cbuffer/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_mmu/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_cpg/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_drp/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_drp/src" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_drp/drp_lib" -fabi-version=0 -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"'

	@arm-none-eabi-gcc @"$@.in"

