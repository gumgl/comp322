################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../gardensStudent.cpp \
../gardensTest.cpp \
../imageMagickTest.cpp 

OBJS += \
./gardensStudent.o \
./gardensTest.o \
./imageMagickTest.o 

CPP_DEPS += \
./gardensStudent.d \
./gardensTest.d \
./imageMagickTest.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


