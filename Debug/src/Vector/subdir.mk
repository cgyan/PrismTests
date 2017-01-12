################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector/Conversions.cpp \
../src/Vector/DefaultVector.cpp \
../src/Vector/DuplicatesVector.cpp \
../src/Vector/ElementAccess.cpp \
../src/Vector/Iterators.cpp \
../src/Vector/NewVector.cpp \
../src/Vector/Queries.cpp \
../src/Vector/UniqueVector.cpp \
../src/Vector/VectorNonMember.cpp 

OBJS += \
./src/Vector/Conversions.o \
./src/Vector/DefaultVector.o \
./src/Vector/DuplicatesVector.o \
./src/Vector/ElementAccess.o \
./src/Vector/Iterators.o \
./src/Vector/NewVector.o \
./src/Vector/Queries.o \
./src/Vector/UniqueVector.o \
./src/Vector/VectorNonMember.o 

CPP_DEPS += \
./src/Vector/Conversions.d \
./src/Vector/DefaultVector.d \
./src/Vector/DuplicatesVector.d \
./src/Vector/ElementAccess.d \
./src/Vector/Iterators.d \
./src/Vector/NewVector.d \
./src/Vector/Queries.d \
./src/Vector/UniqueVector.d \
./src/Vector/VectorNonMember.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector/%.o: ../src/Vector/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/iainhemstock/GitHub/Prism/code/Prism" -I/Users/iainhemstock/hpc-gcc -I"/Users/iainhemstock/GitHub/Prism/code/Prism/inc" -I/Users/iainhemstock/GitHub/PrismTests/external -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


