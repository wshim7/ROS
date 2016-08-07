################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/roscir/device/data/ArmData.cpp \
../src/roscir/device/data/BatteryData.cpp \
../src/roscir/device/data/GyroData.cpp \
../src/roscir/device/data/PanTiltPosition.cpp \
../src/roscir/device/data/PsdData.cpp \
../src/roscir/device/data/RollBendPosition.cpp \
../src/roscir/device/data/TouchButtonData.cpp \
../src/roscir/device/data/UltrasonicData.cpp \
../src/roscir/device/data/WheelEncoderData.cpp 

OBJS += \
./src/roscir/device/data/ArmData.o \
./src/roscir/device/data/BatteryData.o \
./src/roscir/device/data/GyroData.o \
./src/roscir/device/data/PanTiltPosition.o \
./src/roscir/device/data/PsdData.o \
./src/roscir/device/data/RollBendPosition.o \
./src/roscir/device/data/TouchButtonData.o \
./src/roscir/device/data/UltrasonicData.o \
./src/roscir/device/data/WheelEncoderData.o 

CPP_DEPS += \
./src/roscir/device/data/ArmData.d \
./src/roscir/device/data/BatteryData.d \
./src/roscir/device/data/GyroData.d \
./src/roscir/device/data/PanTiltPosition.d \
./src/roscir/device/data/PsdData.d \
./src/roscir/device/data/RollBendPosition.d \
./src/roscir/device/data/TouchButtonData.d \
./src/roscir/device/data/UltrasonicData.d \
./src/roscir/device/data/WheelEncoderData.d 


# Each subdirectory must supply rules for building sources it contributes
src/roscir/device/data/%.o: ../src/roscir/device/data/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


