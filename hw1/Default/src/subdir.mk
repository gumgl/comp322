################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/continuedGrading.cpp \
../src/continuedSolution.cpp \
../src/continuedStudent.cpp \
../src/continuedTest.cpp 

OBJS += \
./src/continuedGrading.o \
./src/continuedSolution.o \
./src/continuedStudent.o \
./src/continuedTest.o 

CPP_DEPS += \
./src/continuedGrading.d \
./src/continuedSolution.d \
./src/continuedStudent.d \
./src/continuedTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


