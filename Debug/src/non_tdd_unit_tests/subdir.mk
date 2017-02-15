################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/non_tdd_unit_tests/ArrayTest.cpp \
../src/non_tdd_unit_tests/BitvectorTest.cpp \
../src/non_tdd_unit_tests/CircleTest.cpp \
../src/non_tdd_unit_tests/DequeTest.cpp \
../src/non_tdd_unit_tests/ListTest.cpp \
../src/non_tdd_unit_tests/PairTest.cpp \
../src/non_tdd_unit_tests/ReverseIteratorTest.cpp \
../src/non_tdd_unit_tests/SharedDataPointerTest.cpp \
../src/non_tdd_unit_tests/SharedDataTest.cpp \
../src/non_tdd_unit_tests/StackTest.cpp \
../src/non_tdd_unit_tests/StringTest.cpp \
../src/non_tdd_unit_tests/TimeTest.cpp \
../src/non_tdd_unit_tests/UniquePointerArrayTest.cpp \
../src/non_tdd_unit_tests/UniquePointerTest.cpp \
../src/non_tdd_unit_tests/VersionTest.cpp \
../src/non_tdd_unit_tests/algorithmTest.cpp \
../src/non_tdd_unit_tests/functorTest.cpp \
../src/non_tdd_unit_tests/type_traitsTest.cpp 

OBJS += \
./src/non_tdd_unit_tests/ArrayTest.o \
./src/non_tdd_unit_tests/BitvectorTest.o \
./src/non_tdd_unit_tests/CircleTest.o \
./src/non_tdd_unit_tests/DequeTest.o \
./src/non_tdd_unit_tests/ListTest.o \
./src/non_tdd_unit_tests/PairTest.o \
./src/non_tdd_unit_tests/ReverseIteratorTest.o \
./src/non_tdd_unit_tests/SharedDataPointerTest.o \
./src/non_tdd_unit_tests/SharedDataTest.o \
./src/non_tdd_unit_tests/StackTest.o \
./src/non_tdd_unit_tests/StringTest.o \
./src/non_tdd_unit_tests/TimeTest.o \
./src/non_tdd_unit_tests/UniquePointerArrayTest.o \
./src/non_tdd_unit_tests/UniquePointerTest.o \
./src/non_tdd_unit_tests/VersionTest.o \
./src/non_tdd_unit_tests/algorithmTest.o \
./src/non_tdd_unit_tests/functorTest.o \
./src/non_tdd_unit_tests/type_traitsTest.o 

CPP_DEPS += \
./src/non_tdd_unit_tests/ArrayTest.d \
./src/non_tdd_unit_tests/BitvectorTest.d \
./src/non_tdd_unit_tests/CircleTest.d \
./src/non_tdd_unit_tests/DequeTest.d \
./src/non_tdd_unit_tests/ListTest.d \
./src/non_tdd_unit_tests/PairTest.d \
./src/non_tdd_unit_tests/ReverseIteratorTest.d \
./src/non_tdd_unit_tests/SharedDataPointerTest.d \
./src/non_tdd_unit_tests/SharedDataTest.d \
./src/non_tdd_unit_tests/StackTest.d \
./src/non_tdd_unit_tests/StringTest.d \
./src/non_tdd_unit_tests/TimeTest.d \
./src/non_tdd_unit_tests/UniquePointerArrayTest.d \
./src/non_tdd_unit_tests/UniquePointerTest.d \
./src/non_tdd_unit_tests/VersionTest.d \
./src/non_tdd_unit_tests/algorithmTest.d \
./src/non_tdd_unit_tests/functorTest.d \
./src/non_tdd_unit_tests/type_traitsTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/non_tdd_unit_tests/%.o: ../src/non_tdd_unit_tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/iainhemstock/GitHub/Prism/code/Prism" -I/Users/iainhemstock/hpc-gcc -I"/Users/iainhemstock/GitHub/Prism/code/Prism/inc" -I/Users/iainhemstock/GitHub/PrismTests/external -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fno-elide-constructors -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


