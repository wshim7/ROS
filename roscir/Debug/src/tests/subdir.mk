################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tests/FRITester.cpp \
../src/tests/LED_tester.cpp \
../src/tests/LedTester.cpp \
../src/tests/Listener.cpp \
../src/tests/LogTester.cpp \
../src/tests/MeroTester.cpp \
../src/tests/Touch_tester.cpp \
../src/tests/abcd.cpp \
../src/tests/arm_tester.cpp \
../src/tests/battery_tester.cpp \
../src/tests/behavior_loop.cpp \
../src/tests/behavior_tester.cpp \
../src/tests/gyro_tester.cpp \
../src/tests/pantilt_tester.cpp \
../src/tests/rollbend_tester.cpp \
../src/tests/wheel_tester.cpp 

OBJS += \
./src/tests/FRITester.o \
./src/tests/LED_tester.o \
./src/tests/LedTester.o \
./src/tests/Listener.o \
./src/tests/LogTester.o \
./src/tests/MeroTester.o \
./src/tests/Touch_tester.o \
./src/tests/abcd.o \
./src/tests/arm_tester.o \
./src/tests/battery_tester.o \
./src/tests/behavior_loop.o \
./src/tests/behavior_tester.o \
./src/tests/gyro_tester.o \
./src/tests/pantilt_tester.o \
./src/tests/rollbend_tester.o \
./src/tests/wheel_tester.o 

CPP_DEPS += \
./src/tests/FRITester.d \
./src/tests/LED_tester.d \
./src/tests/LedTester.d \
./src/tests/Listener.d \
./src/tests/LogTester.d \
./src/tests/MeroTester.d \
./src/tests/Touch_tester.d \
./src/tests/abcd.d \
./src/tests/arm_tester.d \
./src/tests/battery_tester.d \
./src/tests/behavior_loop.d \
./src/tests/behavior_tester.d \
./src/tests/gyro_tester.d \
./src/tests/pantilt_tester.d \
./src/tests/rollbend_tester.d \
./src/tests/wheel_tester.d 


# Each subdirectory must supply rules for building sources it contributes
src/tests/%.o: ../src/tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


