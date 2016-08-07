################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/roscir/device/client/CArmClient.cpp \
../src/roscir/device/client/CBatteryClient.cpp \
../src/roscir/device/client/CGyroClient.cpp \
../src/roscir/device/client/CHeadFaceClient.cpp \
../src/roscir/device/client/CLightEmittingDiodeClient.cpp \
../src/roscir/device/client/CPanTiltClient.cpp \
../src/roscir/device/client/CPsdClient.cpp \
../src/roscir/device/client/CRollBendClient.cpp \
../src/roscir/device/client/CTouchButtonClient.cpp \
../src/roscir/device/client/CUltraClient.cpp \
../src/roscir/device/client/CWheelClient.cpp \
../src/roscir/device/client/CWheelEncoderClient.cpp \
../src/roscir/device/client/DeviceClient.cpp 

OBJS += \
./src/roscir/device/client/CArmClient.o \
./src/roscir/device/client/CBatteryClient.o \
./src/roscir/device/client/CGyroClient.o \
./src/roscir/device/client/CHeadFaceClient.o \
./src/roscir/device/client/CLightEmittingDiodeClient.o \
./src/roscir/device/client/CPanTiltClient.o \
./src/roscir/device/client/CPsdClient.o \
./src/roscir/device/client/CRollBendClient.o \
./src/roscir/device/client/CTouchButtonClient.o \
./src/roscir/device/client/CUltraClient.o \
./src/roscir/device/client/CWheelClient.o \
./src/roscir/device/client/CWheelEncoderClient.o \
./src/roscir/device/client/DeviceClient.o 

CPP_DEPS += \
./src/roscir/device/client/CArmClient.d \
./src/roscir/device/client/CBatteryClient.d \
./src/roscir/device/client/CGyroClient.d \
./src/roscir/device/client/CHeadFaceClient.d \
./src/roscir/device/client/CLightEmittingDiodeClient.d \
./src/roscir/device/client/CPanTiltClient.d \
./src/roscir/device/client/CPsdClient.d \
./src/roscir/device/client/CRollBendClient.d \
./src/roscir/device/client/CTouchButtonClient.d \
./src/roscir/device/client/CUltraClient.d \
./src/roscir/device/client/CWheelClient.d \
./src/roscir/device/client/CWheelEncoderClient.d \
./src/roscir/device/client/DeviceClient.d 


# Each subdirectory must supply rules for building sources it contributes
src/roscir/device/client/%.o: ../src/roscir/device/client/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


