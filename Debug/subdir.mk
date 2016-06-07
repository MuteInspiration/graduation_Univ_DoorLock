################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CNet.cpp \
../Dht.cpp \
../Doorlock.cpp \
../main.cpp 

OBJS += \
./CNet.o \
./Dht.o \
./Doorlock.o \
./main.o 

CPP_DEPS += \
./CNet.d \
./Dht.d \
./Doorlock.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"E:\SysGCC\arm-linux-gnueabihf\sysroot\usr\include" -I"E:\SysGCC\arm-linux-gnueabihf\sysroot\usr\local\include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


