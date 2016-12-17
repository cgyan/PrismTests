################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector/DefaultVector.cpp \
../src/Vector/VectorSizeFiveCapacityTen.cpp 

OBJS += \
./src/Vector/DefaultVector.o \
./src/Vector/VectorSizeFiveCapacityTen.o 

CPP_DEPS += \
./src/Vector/DefaultVector.d \
./src/Vector/VectorSizeFiveCapacityTen.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector/%.o: ../src/Vector/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/iainhemstock/GitHub/Prism/code/Prism" -I/Users/iainhemstock/hpc-gcc -I"/Users/iainhemstock/GitHub/Prism/code/Prism/inc" -I/Users/iainhemstock/GitHub/PrismTests/external -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


