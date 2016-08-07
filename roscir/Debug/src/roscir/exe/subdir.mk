################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/roscir/exe/main.cpp 

OBJS += \
./src/roscir/exe/main.o 

CPP_DEPS += \
./src/roscir/exe/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/roscir/exe/%.o: ../src/roscir/exe/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


