################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CamionTesteur.cpp \
../ProprietaireTesteur.cpp \
../ValidationFormatTesteur.cpp \
../VehiculePromenadeTesteur.cpp \
../main.cpp 

OBJS += \
./CamionTesteur.o \
./ProprietaireTesteur.o \
./ValidationFormatTesteur.o \
./VehiculePromenadeTesteur.o \
./main.o 

CPP_DEPS += \
./CamionTesteur.d \
./ProprietaireTesteur.d \
./ValidationFormatTesteur.d \
./VehiculePromenadeTesteur.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++98 -std=c++98 -I"/home/etudiant/workspace/projet_session/eclipse/tp3" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


