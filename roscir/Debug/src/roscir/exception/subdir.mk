################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/roscir/exception/ArrayOutOfBoundException.cpp \
../src/roscir/exception/ConnectException.cpp \
../src/roscir/exception/Exception.cpp \
../src/roscir/exception/FileNotFoundException.cpp \
../src/roscir/exception/IOException.cpp \
../src/roscir/exception/NoSuchElementException.cpp \
../src/roscir/exception/NullPointerException.cpp \
../src/roscir/exception/NumberFormatException.cpp \
../src/roscir/exception/ParseException.cpp \
../src/roscir/exception/TimeoutException.cpp 

OBJS += \
./src/roscir/exception/ArrayOutOfBoundException.o \
./src/roscir/exception/ConnectException.o \
./src/roscir/exception/Exception.o \
./src/roscir/exception/FileNotFoundException.o \
./src/roscir/exception/IOException.o \
./src/roscir/exception/NoSuchElementException.o \
./src/roscir/exception/NullPointerException.o \
./src/roscir/exception/NumberFormatException.o \
./src/roscir/exception/ParseException.o \
./src/roscir/exception/TimeoutException.o 

CPP_DEPS += \
./src/roscir/exception/ArrayOutOfBoundException.d \
./src/roscir/exception/ConnectException.d \
./src/roscir/exception/Exception.d \
./src/roscir/exception/FileNotFoundException.d \
./src/roscir/exception/IOException.d \
./src/roscir/exception/NoSuchElementException.d \
./src/roscir/exception/NullPointerException.d \
./src/roscir/exception/NumberFormatException.d \
./src/roscir/exception/ParseException.d \
./src/roscir/exception/TimeoutException.d 


# Each subdirectory must supply rules for building sources it contributes
src/roscir/exception/%.o: ../src/roscir/exception/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


