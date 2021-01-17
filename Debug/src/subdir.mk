################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FileReader.cpp \
../src/Layer.cpp \
../src/Layers.cpp \
../src/Neuron.cpp \
../src/Utils.cpp \
../src/cats.cpp 

OBJS += \
./src/FileReader.o \
./src/Layer.o \
./src/Layers.o \
./src/Neuron.o \
./src/Utils.o \
./src/cats.o 

CPP_DEPS += \
./src/FileReader.d \
./src/Layer.d \
./src/Layers.d \
./src/Neuron.d \
./src/Utils.d \
./src/cats.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I"/home/kszmmnn/STM32CubeIDE/workspace_1.4.0/cats/inc" -I"/home/kszmmnn/STM32CubeIDE/workspace_1.4.0/cats/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


