################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MyCoffeePotFunctions_CPP.cpp \
../src/My_CoffeePot_2016main.cpp \
../src/My_HeaterControlCode_CPP.cpp \
../src/My_WaterControlCode_CPP.cpp 

ASM_SRCS += \
../src/My_HeaterControlCode_ASM.asm \
../src/My_WaterControlCode_ASM.asm 

SRC_OBJS += \
./src/MyCoffeePotFunctions_CPP.doj \
./src/My_CoffeePot_2016main.doj \
./src/My_HeaterControlCode_ASM.doj \
./src/My_HeaterControlCode_CPP.doj \
./src/My_WaterControlCode_ASM.doj \
./src/My_WaterControlCode_CPP.doj 

ASM_DEPS += \
./src/My_HeaterControlCode_ASM.d \
./src/My_WaterControlCode_ASM.d 

CPP_DEPS += \
./src/MyCoffeePotFunctions_CPP.d \
./src/My_CoffeePot_2016main.d \
./src/My_HeaterControlCode_CPP.d \
./src/My_WaterControlCode_CPP.d 


# Each subdirectory must supply rules for building sources it contributes
src/MyCoffeePotFunctions_CPP.doj: ../src/MyCoffeePotFunctions_CPP.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn.exe -c -file-attr ProjectName="My_CoffeePot_2016Assignment" -proc ADSP-BF533 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG -I"C:\Users\aspireE15\Documents\Fourth Year\ENCM_511\ENCM511_2016Workspace\My_CoffeePot_2016Assignment\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "src/MyCoffeePotFunctions_CPP.d" -c++ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/My_CoffeePot_2016main.doj: ../src/My_CoffeePot_2016main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn.exe -c -file-attr ProjectName="My_CoffeePot_2016Assignment" -proc ADSP-BF533 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG -I"C:\Users\aspireE15\Documents\Fourth Year\ENCM_511\ENCM511_2016Workspace\My_CoffeePot_2016Assignment\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "src/My_CoffeePot_2016main.d" -c++ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/My_HeaterControlCode_ASM.doj: ../src/My_HeaterControlCode_ASM.asm
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin Assembler'
	easmblkfn.exe -file-attr ProjectName="My_CoffeePot_2016Assignment" -proc ADSP-BF533 -si-revision any -g -DCORE0 -D_DEBUG -i"C:\Users\aspireE15\Documents\Fourth Year\ENCM_511\ENCM511_2016Workspace\My_CoffeePot_2016Assignment\system" -gnu-style-dependencies -MM -Mo "src/My_HeaterControlCode_ASM.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/My_HeaterControlCode_CPP.doj: ../src/My_HeaterControlCode_CPP.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn.exe -c -file-attr ProjectName="My_CoffeePot_2016Assignment" -proc ADSP-BF533 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG -I"C:\Users\aspireE15\Documents\Fourth Year\ENCM_511\ENCM511_2016Workspace\My_CoffeePot_2016Assignment\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "src/My_HeaterControlCode_CPP.d" -c++ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/My_WaterControlCode_ASM.doj: ../src/My_WaterControlCode_ASM.asm
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin Assembler'
	easmblkfn.exe -file-attr ProjectName="My_CoffeePot_2016Assignment" -proc ADSP-BF533 -si-revision any -g -DCORE0 -D_DEBUG -i"C:\Users\aspireE15\Documents\Fourth Year\ENCM_511\ENCM511_2016Workspace\My_CoffeePot_2016Assignment\system" -gnu-style-dependencies -MM -Mo "src/My_WaterControlCode_ASM.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/My_WaterControlCode_CPP.doj: ../src/My_WaterControlCode_CPP.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore Blackfin C/C++ Compiler'
	ccblkfn.exe -c -file-attr ProjectName="My_CoffeePot_2016Assignment" -proc ADSP-BF533 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE0 -D_DEBUG -I"C:\Users\aspireE15\Documents\Fourth Year\ENCM_511\ENCM511_2016Workspace\My_CoffeePot_2016Assignment\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -decls-strong -cplbs -gnu-style-dependencies -MD -Mo "src/My_WaterControlCode_CPP.d" -c++ -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


