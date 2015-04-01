################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../flowersExamples.cpp \
../flowersStudent.cpp \
../flowersTest.cpp 

OBJS += \
./flowersExamples.o \
./flowersStudent.o \
./flowersTest.o 

CPP_DEPS += \
./flowersExamples.d \
./flowersStudent.d \
./flowersTest.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


