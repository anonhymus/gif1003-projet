################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Camion.cpp \
../Proprietaire.cpp \
../vehicule.cpp \
../vehiculePromenade.cpp 

OBJS += \
./Camion.o \
./Proprietaire.o \
./vehicule.o \
./vehiculePromenade.o 

CPP_DEPS += \
./Camion.d \
./Proprietaire.d \
./vehicule.d \
./vehiculePromenade.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++98 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


