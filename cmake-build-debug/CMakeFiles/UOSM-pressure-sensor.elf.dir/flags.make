# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

# compile ASM with C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/13.3 rel1/bin/arm-none-eabi-gcc.exe
# compile C with C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/13.3 rel1/bin/arm-none-eabi-gcc.exe
# compile CXX with C:/Program Files (x86)/Arm GNU Toolchain arm-none-eabi/13.3 rel1/bin/arm-none-eabi-g++.exe
ASM_DEFINES = -DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -DDEBUG -DSTM32L432xx -DUSE_HAL_DRIVER

ASM_INCLUDES = -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Core\Inc -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Drivers\STM32L4xx_HAL_Driver\Inc -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Drivers\STM32L4xx_HAL_Driver\Inc\Legacy -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Drivers\CMSIS\Device\ST\STM32L4xx\Include -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Drivers\CMSIS\Include -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Middlewares\Third_Party\FreeRTOS\Source\include -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Middlewares\Third_Party\FreeRTOS\Source\CMSIS_RTOS_V2 -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Middlewares\Third_Party\FreeRTOS\Source\portable\GCC\ARM_CM4F -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Core\Tasks -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Core\UserDrivers -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\UOSM-Core\Drivers -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\UOSM-Core\Inc -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\UOSM-Core\Modules -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\UOSM-Core\Utils

ASM_FLAGS = -g -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mthumb -mthumb-interwork -ffunction-sections -fdata-sections -fno-common -fmessage-length=0 -x assembler-with-cpp -Og -g

C_DEFINES = -DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -DDEBUG -DSTM32L432xx -DUSE_HAL_DRIVER

C_INCLUDES = -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Core\Inc -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Drivers\STM32L4xx_HAL_Driver\Inc -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Drivers\STM32L4xx_HAL_Driver\Inc\Legacy -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Drivers\CMSIS\Device\ST\STM32L4xx\Include -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Drivers\CMSIS\Include -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Middlewares\Third_Party\FreeRTOS\Source\include -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Middlewares\Third_Party\FreeRTOS\Source\CMSIS_RTOS_V2 -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Middlewares\Third_Party\FreeRTOS\Source\portable\GCC\ARM_CM4F -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Core\Tasks -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Core\UserDrivers -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\UOSM-Core\Drivers -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\UOSM-Core\Inc -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\UOSM-Core\Modules -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\UOSM-Core\Utils

C_FLAGS = -g -std=gnu11 -fdiagnostics-color=always -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mthumb -mthumb-interwork -ffunction-sections -fdata-sections -fno-common -fmessage-length=0 -Og -g

CXX_DEFINES = -DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -DDEBUG -DSTM32L432xx -DUSE_HAL_DRIVER

CXX_INCLUDES = -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Core\Inc -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Drivers\STM32L4xx_HAL_Driver\Inc -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Drivers\STM32L4xx_HAL_Driver\Inc\Legacy -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Drivers\CMSIS\Device\ST\STM32L4xx\Include -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Drivers\CMSIS\Include -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Middlewares\Third_Party\FreeRTOS\Source\include -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Middlewares\Third_Party\FreeRTOS\Source\CMSIS_RTOS_V2 -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Middlewares\Third_Party\FreeRTOS\Source\portable\GCC\ARM_CM4F -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Core\Tasks -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\Core\UserDrivers -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\UOSM-Core\Drivers -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\UOSM-Core\Inc -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\UOSM-Core\Modules -IC:\Users\David\CLionProjects\UOSM-Pressure-Sensor\UOSM-Core\Utils

CXX_FLAGS = -g -fdiagnostics-color=always -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mthumb -mthumb-interwork -ffunction-sections -fdata-sections -fno-common -fmessage-length=0 -Og -g

