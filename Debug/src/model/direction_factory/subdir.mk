################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/model/direction_factory/always_up.cc \
../src/model/direction_factory/random.cc 

OBJS += \
./src/model/direction_factory/always_up.o \
./src/model/direction_factory/random.o 

CC_DEPS += \
./src/model/direction_factory/always_up.d \
./src/model/direction_factory/random.d 


# Each subdirectory must supply rules for building sources it contributes
src/model/direction_factory/%.o: ../src/model/direction_factory/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g -Wall -Wextra -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


