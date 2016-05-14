################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Dht.cpp \
../Doorlock.cpp \
../Net.cpp \
../main.cpp 

OBJS += \
./Dht.o \
./Doorlock.o \
./Net.o \
./main.o 

CPP_DEPS += \
./Dht.d \
./Doorlock.d \
./Net.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"E:\SysGCC\arm-linux-gnueabihf\sysroot\usr\include" -I"E:\SysGCC\arm-linux-gnueabihf\sysroot\usr\local\include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


