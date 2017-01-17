################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector/Vector.cpp \
../src/Vector/VectorConversions.cpp \
../src/Vector/VectorElementAccess.cpp \
../src/Vector/VectorInsertions.cpp \
../src/Vector/VectorIterators.cpp \
../src/Vector/VectorNonMember.cpp \
../src/Vector/VectorQueries.cpp \
../src/Vector/VectorRemovals.cpp 

OBJS += \
./src/Vector/Vector.o \
./src/Vector/VectorConversions.o \
./src/Vector/VectorElementAccess.o \
./src/Vector/VectorInsertions.o \
./src/Vector/VectorIterators.o \
./src/Vector/VectorNonMember.o \
./src/Vector/VectorQueries.o \
./src/Vector/VectorRemovals.o 

CPP_DEPS += \
./src/Vector/Vector.d \
./src/Vector/VectorConversions.d \
./src/Vector/VectorElementAccess.d \
./src/Vector/VectorInsertions.d \
./src/Vector/VectorIterators.d \
./src/Vector/VectorNonMember.d \
./src/Vector/VectorQueries.d \
./src/Vector/VectorRemovals.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector/%.o: ../src/Vector/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/iainhemstock/GitHub/Prism/code/Prism" -I/Users/iainhemstock/hpc-gcc -I"/Users/iainhemstock/GitHub/Prism/code/Prism/inc" -I/Users/iainhemstock/GitHub/PrismTests/external -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fno-elide-constructors -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


