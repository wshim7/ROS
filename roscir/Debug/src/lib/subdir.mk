################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/lib/roscir.cpp \
../src/lib/roscirwin.cpp 

OBJS += \
./src/lib/roscir.o \
./src/lib/roscirwin.o 

CPP_DEPS += \
./src/lib/roscir.d \
./src/lib/roscirwin.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/%.o: ../src/lib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


