################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/model/atomic_lane.cc \
../src/model/atomic_station.cc \
../src/model/critical_lane.cc \
../src/model/lane.cc \
../src/model/lock_lane.cc \
../src/model/lock_station.cc \
../src/model/solution_result.cc \
../src/model/station.cc 

OBJS += \
./src/model/atomic_lane.o \
./src/model/atomic_station.o \
./src/model/critical_lane.o \
./src/model/lane.o \
./src/model/lock_lane.o \
./src/model/lock_station.o \
./src/model/solution_result.o \
./src/model/station.o 

CC_DEPS += \
./src/model/atomic_lane.d \
./src/model/atomic_station.d \
./src/model/critical_lane.d \
./src/model/lane.d \
./src/model/lock_lane.d \
./src/model/lock_station.d \
./src/model/solution_result.d \
./src/model/station.d 


# Each subdirectory must supply rules for building sources it contributes
src/model/%.o: ../src/model/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g -Wall -Wextra -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


