################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm_Move.cpp \
../src/Iterator.cpp \
../src/List.cpp \
../src/Vector.cpp 

OBJS += \
./src/Algorithm_Move.o \
./src/Iterator.o \
./src/List.o \
./src/Vector.o 

CPP_DEPS += \
./src/Algorithm_Move.d \
./src/Iterator.d \
./src/List.d \
./src/Vector.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/iainhemstock/GitHub/Prism/code/Prism" -I"/Users/iainhemstock/GitHub/PrismTests/inc" -I/Users/iainhemstock/hpc-gcc -I"/Users/iainhemstock/GitHub/Prism/code/Prism/inc" -I/Users/iainhemstock/GitHub/PrismTests/external -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fno-elide-constructors -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


