################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/roscir/env/Config.cpp 

OBJS += \
./src/roscir/env/Config.o 

CPP_DEPS += \
./src/roscir/env/Config.d 


# Each subdirectory must supply rules for building sources it contributes
src/roscir/env/%.o: ../src/roscir/env/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


