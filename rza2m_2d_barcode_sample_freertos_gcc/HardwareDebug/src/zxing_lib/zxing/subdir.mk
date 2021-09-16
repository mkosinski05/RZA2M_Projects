################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/zxing_lib/zxing/BarcodeFormat.cpp \
../src/zxing_lib/zxing/Binarizer.cpp \
../src/zxing_lib/zxing/BinaryBitmap.cpp \
../src/zxing_lib/zxing/ChecksumException.cpp \
../src/zxing_lib/zxing/DecodeHints.cpp \
../src/zxing_lib/zxing/Exception.cpp \
../src/zxing_lib/zxing/FormatException.cpp \
../src/zxing_lib/zxing/InvertedLuminanceSource.cpp \
../src/zxing_lib/zxing/LuminanceSource.cpp \
../src/zxing_lib/zxing/MultiFormatReader.cpp \
../src/zxing_lib/zxing/Reader.cpp \
../src/zxing_lib/zxing/Result.cpp \
../src/zxing_lib/zxing/ResultIO.cpp \
../src/zxing_lib/zxing/ResultPoint.cpp \
../src/zxing_lib/zxing/ResultPointCallback.cpp 

OBJS += \
./src/zxing_lib/zxing/BarcodeFormat.o \
./src/zxing_lib/zxing/Binarizer.o \
./src/zxing_lib/zxing/BinaryBitmap.o \
./src/zxing_lib/zxing/ChecksumException.o \
./src/zxing_lib/zxing/DecodeHints.o \
./src/zxing_lib/zxing/Exception.o \
./src/zxing_lib/zxing/FormatException.o \
./src/zxing_lib/zxing/InvertedLuminanceSource.o \
./src/zxing_lib/zxing/LuminanceSource.o \
./src/zxing_lib/zxing/MultiFormatReader.o \
./src/zxing_lib/zxing/Reader.o \
./src/zxing_lib/zxing/Result.o \
./src/zxing_lib/zxing/ResultIO.o \
./src/zxing_lib/zxing/ResultPoint.o \
./src/zxing_lib/zxing/ResultPointCallback.o 

CPP_DEPS += \
./src/zxing_lib/zxing/BarcodeFormat.d \
./src/zxing_lib/zxing/Binarizer.d \
./src/zxing_lib/zxing/BinaryBitmap.d \
./src/zxing_lib/zxing/ChecksumException.d \
./src/zxing_lib/zxing/DecodeHints.d \
./src/zxing_lib/zxing/Exception.d \
./src/zxing_lib/zxing/FormatException.d \
./src/zxing_lib/zxing/InvertedLuminanceSource.d \
./src/zxing_lib/zxing/LuminanceSource.d \
./src/zxing_lib/zxing/MultiFormatReader.d \
./src/zxing_lib/zxing/Reader.d \
./src/zxing_lib/zxing/Result.d \
./src/zxing_lib/zxing/ResultIO.d \
./src/zxing_lib/zxing/ResultPoint.d \
./src/zxing_lib/zxing/ResultPointCallback.d 


# Each subdirectory must supply rules for building sources it contributes
src/zxing_lib/zxing/%.o: ../src/zxing_lib/zxing/%.cpp
	$(file > $@.in,-mcpu=cortex-a9 -march=armv7-a -marm -mlittle-endian -mfloat-abi=hard -mfpu=neon -mno-unaligned-access -Og -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -Wmaybe-uninitialized -Wstack-usage=100 -g3 -DNO_ICONV -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/FreeRTOS/include" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/FreeRTOS/include/private" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/FreeRTOS/portable/GCC/ARM_CA9_RZA2M" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/compiler/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/configuration" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/config_files" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/system/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/renesas/application/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/zxing_lib" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/zxing_lib/zxing" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_riic/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_rvapi/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_mipi/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_ceu/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_vdc/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_ostm/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_scifa/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/system/iodefine" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_stb/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_gpio/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/os_abstraction/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_intc/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_cache/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_cbuffer/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_mmu/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_cpg/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_drp/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_drp/src" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_drp/drp_lib" -fabi-version=0 -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo 'arm-none-eabi-gcc -mcpu=cortex-a9 -march=armv7-a -marm -mlittle-endian -mfloat-abi=hard -mfpu=neon -mno-unaligned-access -Og -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -Wmaybe-uninitialized -Wstack-usage=100 -g3 -DNO_ICONV -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/FreeRTOS/include" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/FreeRTOS/include/private" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/FreeRTOS/portable/GCC/ARM_CA9_RZA2M" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/compiler/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/configuration" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/config_files" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/system/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/renesas/application/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/zxing_lib" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/src/zxing_lib/zxing" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_riic/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_rvapi/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_mipi/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_ceu/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_vdc/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_ostm/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_scifa/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/system/iodefine" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_stb/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_gpio/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/os_abstraction/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_intc/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_cache/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_cbuffer/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_mmu/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/drivers/r_cpg/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_drp/inc" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_drp/src" -I"/home/zkmike/workspace/RZA2M/rza2m_2d_barcode_sample_freertos_gcc/generate/sc_drivers/r_drp/drp_lib" -fabi-version=0 -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"'

	@arm-none-eabi-gcc @"$@.in"

