################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/roscir/util/getch.cpp 

OBJS += \
./src/roscir/util/getch.o 

CPP_DEPS += \
./src/roscir/util/getch.d 


# Each subdirectory must supply rules for building sources it contributes
src/roscir/util/%.o: ../src/roscir/util/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


