/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'Nios2' in SOPC Builder design 'nios_system'
 * SOPC Builder design path: ../../nios_system.sopcinfo
 *
 * Generated: Mon May 27 16:44:56 CEST 2019
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x0a000020
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "fast"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1d
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00000020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 1
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 1
#define ALT_CPU_HARDWARE_MULX_PRESENT 1
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_DIVISION_ERROR_EXCEPTION
#define ALT_CPU_HAS_EXTRA_EXCEPTION_INFO
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 32
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 5
#define ALT_CPU_ICACHE_SIZE 4096
#define ALT_CPU_INST_ADDR_WIDTH 0x1c
#define ALT_CPU_NAME "Nios2"
#define ALT_CPU_NUM_OF_SHADOW_REG_SETS 0
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x0a000020
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "fast"
#define NIOS2_DATA_ADDR_WIDTH 0x1d
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00000020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 1
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 1
#define NIOS2_HARDWARE_MULX_PRESENT 1
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_DIVISION_ERROR_EXCEPTION
#define NIOS2_HAS_EXTRA_EXCEPTION_INFO
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 32
#define NIOS2_ICACHE_LINE_SIZE_LOG2 5
#define NIOS2_ICACHE_SIZE 4096
#define NIOS2_INST_ADDR_WIDTH 0x1c
#define NIOS2_NUM_OF_SHADOW_REG_SETS 0
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00000000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_PIO
#define __ALTERA_NIOS2_GEN2
#define __ALTERA_UP_AVALON_SRAM
#define __ALTERA_UP_FLASH_MEMORY_IP_CORE_AVALON_INTERFACE


/*
 * Flash_flash_data configuration
 *
 */

#define ALT_MODULE_CLASS_Flash_flash_data Altera_UP_Flash_Memory_IP_Core_Avalon_Interface
#define FLASH_FLASH_DATA_BASE 0xc000000
#define FLASH_FLASH_DATA_IRQ -1
#define FLASH_FLASH_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FLASH_FLASH_DATA_NAME "/dev/Flash_flash_data"
#define FLASH_FLASH_DATA_SPAN 8388608
#define FLASH_FLASH_DATA_TYPE "Altera_UP_Flash_Memory_IP_Core_Avalon_Interface"


/*
 * Flash_flash_erase_control configuration
 *
 */

#define ALT_MODULE_CLASS_Flash_flash_erase_control Altera_UP_Flash_Memory_IP_Core_Avalon_Interface
#define FLASH_FLASH_ERASE_CONTROL_BASE 0xbff0000
#define FLASH_FLASH_ERASE_CONTROL_IRQ -1
#define FLASH_FLASH_ERASE_CONTROL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define FLASH_FLASH_ERASE_CONTROL_NAME "/dev/Flash_flash_erase_control"
#define FLASH_FLASH_ERASE_CONTROL_SPAN 4
#define FLASH_FLASH_ERASE_CONTROL_TYPE "Altera_UP_Flash_Memory_IP_Core_Avalon_Interface"


/*
 * JTAG_UART configuration
 *
 */

#define ALT_MODULE_CLASS_JTAG_UART altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x10001000
#define JTAG_UART_IRQ 8
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/JTAG_UART"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * SDRAM configuration
 *
 */

#define ALT_MODULE_CLASS_SDRAM altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x0
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/SDRAM"
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 15.625
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x19
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 10
#define SDRAM_SDRAM_DATA_WIDTH 32
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 1
#define SDRAM_SPAN 134217728
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.5
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 20.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 20.0
#define SDRAM_T_WR 14.0


/*
 * SRAM configuration
 *
 */

#define ALT_MODULE_CLASS_SRAM altera_up_avalon_sram
#define SRAM_BASE 0x8000000
#define SRAM_IRQ -1
#define SRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SRAM_NAME "/dev/SRAM"
#define SRAM_SPAN 2097152
#define SRAM_TYPE "altera_up_avalon_sram"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/JTAG_UART"
#define ALT_STDERR_BASE 0x10001000
#define ALT_STDERR_DEV JTAG_UART
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/JTAG_UART"
#define ALT_STDIN_BASE 0x10001000
#define ALT_STDIN_DEV JTAG_UART
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/JTAG_UART"
#define ALT_STDOUT_BASE 0x10001000
#define ALT_STDOUT_DEV JTAG_UART
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "nios_system"


/*
 * cam_in_0 configuration
 *
 */

#define ALT_MODULE_CLASS_cam_in_0 altera_avalon_pio
#define CAM_IN_0_BASE 0x8200000
#define CAM_IN_0_BIT_CLEARING_EDGE_REGISTER 0
#define CAM_IN_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define CAM_IN_0_CAPTURE 0
#define CAM_IN_0_DATA_WIDTH 15
#define CAM_IN_0_DO_TEST_BENCH_WIRING 0
#define CAM_IN_0_DRIVEN_SIM_VALUE 0
#define CAM_IN_0_EDGE_TYPE "NONE"
#define CAM_IN_0_FREQ 50000000
#define CAM_IN_0_HAS_IN 1
#define CAM_IN_0_HAS_OUT 0
#define CAM_IN_0_HAS_TRI 0
#define CAM_IN_0_IRQ -1
#define CAM_IN_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CAM_IN_0_IRQ_TYPE "NONE"
#define CAM_IN_0_NAME "/dev/cam_in_0"
#define CAM_IN_0_RESET_VALUE 0
#define CAM_IN_0_SPAN 16
#define CAM_IN_0_TYPE "altera_avalon_pio"


/*
 * cam_in_1 configuration
 *
 */

#define ALT_MODULE_CLASS_cam_in_1 altera_avalon_pio
#define CAM_IN_1_BASE 0x8200010
#define CAM_IN_1_BIT_CLEARING_EDGE_REGISTER 0
#define CAM_IN_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define CAM_IN_1_CAPTURE 0
#define CAM_IN_1_DATA_WIDTH 15
#define CAM_IN_1_DO_TEST_BENCH_WIRING 0
#define CAM_IN_1_DRIVEN_SIM_VALUE 0
#define CAM_IN_1_EDGE_TYPE "NONE"
#define CAM_IN_1_FREQ 50000000
#define CAM_IN_1_HAS_IN 1
#define CAM_IN_1_HAS_OUT 0
#define CAM_IN_1_HAS_TRI 0
#define CAM_IN_1_IRQ -1
#define CAM_IN_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CAM_IN_1_IRQ_TYPE "NONE"
#define CAM_IN_1_NAME "/dev/cam_in_1"
#define CAM_IN_1_RESET_VALUE 0
#define CAM_IN_1_SPAN 16
#define CAM_IN_1_TYPE "altera_avalon_pio"


/*
 * cam_in_2 configuration
 *
 */

#define ALT_MODULE_CLASS_cam_in_2 altera_avalon_pio
#define CAM_IN_2_BASE 0x8200020
#define CAM_IN_2_BIT_CLEARING_EDGE_REGISTER 0
#define CAM_IN_2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define CAM_IN_2_CAPTURE 0
#define CAM_IN_2_DATA_WIDTH 15
#define CAM_IN_2_DO_TEST_BENCH_WIRING 0
#define CAM_IN_2_DRIVEN_SIM_VALUE 0
#define CAM_IN_2_EDGE_TYPE "NONE"
#define CAM_IN_2_FREQ 50000000
#define CAM_IN_2_HAS_IN 1
#define CAM_IN_2_HAS_OUT 0
#define CAM_IN_2_HAS_TRI 0
#define CAM_IN_2_IRQ -1
#define CAM_IN_2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CAM_IN_2_IRQ_TYPE "NONE"
#define CAM_IN_2_NAME "/dev/cam_in_2"
#define CAM_IN_2_RESET_VALUE 0
#define CAM_IN_2_SPAN 16
#define CAM_IN_2_TYPE "altera_avalon_pio"


/*
 * cam_in_3 configuration
 *
 */

#define ALT_MODULE_CLASS_cam_in_3 altera_avalon_pio
#define CAM_IN_3_BASE 0x8200030
#define CAM_IN_3_BIT_CLEARING_EDGE_REGISTER 0
#define CAM_IN_3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define CAM_IN_3_CAPTURE 0
#define CAM_IN_3_DATA_WIDTH 15
#define CAM_IN_3_DO_TEST_BENCH_WIRING 0
#define CAM_IN_3_DRIVEN_SIM_VALUE 0
#define CAM_IN_3_EDGE_TYPE "NONE"
#define CAM_IN_3_FREQ 50000000
#define CAM_IN_3_HAS_IN 1
#define CAM_IN_3_HAS_OUT 0
#define CAM_IN_3_HAS_TRI 0
#define CAM_IN_3_IRQ -1
#define CAM_IN_3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CAM_IN_3_IRQ_TYPE "NONE"
#define CAM_IN_3_NAME "/dev/cam_in_3"
#define CAM_IN_3_RESET_VALUE 0
#define CAM_IN_3_SPAN 16
#define CAM_IN_3_TYPE "altera_avalon_pio"


/*
 * cam_in_4 configuration
 *
 */

#define ALT_MODULE_CLASS_cam_in_4 altera_avalon_pio
#define CAM_IN_4_BASE 0x8200040
#define CAM_IN_4_BIT_CLEARING_EDGE_REGISTER 0
#define CAM_IN_4_BIT_MODIFYING_OUTPUT_REGISTER 0
#define CAM_IN_4_CAPTURE 0
#define CAM_IN_4_DATA_WIDTH 15
#define CAM_IN_4_DO_TEST_BENCH_WIRING 0
#define CAM_IN_4_DRIVEN_SIM_VALUE 0
#define CAM_IN_4_EDGE_TYPE "NONE"
#define CAM_IN_4_FREQ 50000000
#define CAM_IN_4_HAS_IN 1
#define CAM_IN_4_HAS_OUT 0
#define CAM_IN_4_HAS_TRI 0
#define CAM_IN_4_IRQ -1
#define CAM_IN_4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CAM_IN_4_IRQ_TYPE "NONE"
#define CAM_IN_4_NAME "/dev/cam_in_4"
#define CAM_IN_4_RESET_VALUE 0
#define CAM_IN_4_SPAN 16
#define CAM_IN_4_TYPE "altera_avalon_pio"


/*
 * cam_in_5 configuration
 *
 */

#define ALT_MODULE_CLASS_cam_in_5 altera_avalon_pio
#define CAM_IN_5_BASE 0x8200050
#define CAM_IN_5_BIT_CLEARING_EDGE_REGISTER 0
#define CAM_IN_5_BIT_MODIFYING_OUTPUT_REGISTER 0
#define CAM_IN_5_CAPTURE 0
#define CAM_IN_5_DATA_WIDTH 15
#define CAM_IN_5_DO_TEST_BENCH_WIRING 0
#define CAM_IN_5_DRIVEN_SIM_VALUE 0
#define CAM_IN_5_EDGE_TYPE "NONE"
#define CAM_IN_5_FREQ 50000000
#define CAM_IN_5_HAS_IN 1
#define CAM_IN_5_HAS_OUT 0
#define CAM_IN_5_HAS_TRI 0
#define CAM_IN_5_IRQ -1
#define CAM_IN_5_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CAM_IN_5_IRQ_TYPE "NONE"
#define CAM_IN_5_NAME "/dev/cam_in_5"
#define CAM_IN_5_RESET_VALUE 0
#define CAM_IN_5_SPAN 16
#define CAM_IN_5_TYPE "altera_avalon_pio"


/*
 * cam_in_6 configuration
 *
 */

#define ALT_MODULE_CLASS_cam_in_6 altera_avalon_pio
#define CAM_IN_6_BASE 0x8200060
#define CAM_IN_6_BIT_CLEARING_EDGE_REGISTER 0
#define CAM_IN_6_BIT_MODIFYING_OUTPUT_REGISTER 0
#define CAM_IN_6_CAPTURE 0
#define CAM_IN_6_DATA_WIDTH 15
#define CAM_IN_6_DO_TEST_BENCH_WIRING 0
#define CAM_IN_6_DRIVEN_SIM_VALUE 0
#define CAM_IN_6_EDGE_TYPE "NONE"
#define CAM_IN_6_FREQ 50000000
#define CAM_IN_6_HAS_IN 1
#define CAM_IN_6_HAS_OUT 0
#define CAM_IN_6_HAS_TRI 0
#define CAM_IN_6_IRQ -1
#define CAM_IN_6_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CAM_IN_6_IRQ_TYPE "NONE"
#define CAM_IN_6_NAME "/dev/cam_in_6"
#define CAM_IN_6_RESET_VALUE 0
#define CAM_IN_6_SPAN 16
#define CAM_IN_6_TYPE "altera_avalon_pio"


/*
 * cam_in_7 configuration
 *
 */

#define ALT_MODULE_CLASS_cam_in_7 altera_avalon_pio
#define CAM_IN_7_BASE 0x8200070
#define CAM_IN_7_BIT_CLEARING_EDGE_REGISTER 0
#define CAM_IN_7_BIT_MODIFYING_OUTPUT_REGISTER 0
#define CAM_IN_7_CAPTURE 0
#define CAM_IN_7_DATA_WIDTH 15
#define CAM_IN_7_DO_TEST_BENCH_WIRING 0
#define CAM_IN_7_DRIVEN_SIM_VALUE 0
#define CAM_IN_7_EDGE_TYPE "NONE"
#define CAM_IN_7_FREQ 50000000
#define CAM_IN_7_HAS_IN 1
#define CAM_IN_7_HAS_OUT 0
#define CAM_IN_7_HAS_TRI 0
#define CAM_IN_7_IRQ -1
#define CAM_IN_7_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CAM_IN_7_IRQ_TYPE "NONE"
#define CAM_IN_7_NAME "/dev/cam_in_7"
#define CAM_IN_7_RESET_VALUE 0
#define CAM_IN_7_SPAN 16
#define CAM_IN_7_TYPE "altera_avalon_pio"


/*
 * cam_in_8 configuration
 *
 */

#define ALT_MODULE_CLASS_cam_in_8 altera_avalon_pio
#define CAM_IN_8_BASE 0x8200090
#define CAM_IN_8_BIT_CLEARING_EDGE_REGISTER 0
#define CAM_IN_8_BIT_MODIFYING_OUTPUT_REGISTER 0
#define CAM_IN_8_CAPTURE 0
#define CAM_IN_8_DATA_WIDTH 15
#define CAM_IN_8_DO_TEST_BENCH_WIRING 0
#define CAM_IN_8_DRIVEN_SIM_VALUE 0
#define CAM_IN_8_EDGE_TYPE "NONE"
#define CAM_IN_8_FREQ 50000000
#define CAM_IN_8_HAS_IN 1
#define CAM_IN_8_HAS_OUT 0
#define CAM_IN_8_HAS_TRI 0
#define CAM_IN_8_IRQ -1
#define CAM_IN_8_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CAM_IN_8_IRQ_TYPE "NONE"
#define CAM_IN_8_NAME "/dev/cam_in_8"
#define CAM_IN_8_RESET_VALUE 0
#define CAM_IN_8_SPAN 16
#define CAM_IN_8_TYPE "altera_avalon_pio"


/*
 * cam_in_9 configuration
 *
 */

#define ALT_MODULE_CLASS_cam_in_9 altera_avalon_pio
#define CAM_IN_9_BASE 0x8200080
#define CAM_IN_9_BIT_CLEARING_EDGE_REGISTER 0
#define CAM_IN_9_BIT_MODIFYING_OUTPUT_REGISTER 0
#define CAM_IN_9_CAPTURE 0
#define CAM_IN_9_DATA_WIDTH 15
#define CAM_IN_9_DO_TEST_BENCH_WIRING 0
#define CAM_IN_9_DRIVEN_SIM_VALUE 0
#define CAM_IN_9_EDGE_TYPE "NONE"
#define CAM_IN_9_FREQ 50000000
#define CAM_IN_9_HAS_IN 1
#define CAM_IN_9_HAS_OUT 0
#define CAM_IN_9_HAS_TRI 0
#define CAM_IN_9_IRQ -1
#define CAM_IN_9_IRQ_INTERRUPT_CONTROLLER_ID -1
#define CAM_IN_9_IRQ_TYPE "NONE"
#define CAM_IN_9_NAME "/dev/cam_in_9"
#define CAM_IN_9_RESET_VALUE 0
#define CAM_IN_9_SPAN 16
#define CAM_IN_9_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * ucosii configuration
 *
 */

#define OS_ARG_CHK_EN 1
#define OS_CPU_HOOKS_EN 1
#define OS_DEBUG_EN 1
#define OS_EVENT_NAME_SIZE 32
#define OS_FLAGS_NBITS 16
#define OS_FLAG_ACCEPT_EN 1
#define OS_FLAG_DEL_EN 1
#define OS_FLAG_EN 1
#define OS_FLAG_NAME_SIZE 32
#define OS_FLAG_QUERY_EN 1
#define OS_FLAG_WAIT_CLR_EN 1
#define OS_LOWEST_PRIO 20
#define OS_MAX_EVENTS 60
#define OS_MAX_FLAGS 20
#define OS_MAX_MEM_PART 60
#define OS_MAX_QS 20
#define OS_MAX_TASKS 10
#define OS_MBOX_ACCEPT_EN 1
#define OS_MBOX_DEL_EN 1
#define OS_MBOX_EN 1
#define OS_MBOX_POST_EN 1
#define OS_MBOX_POST_OPT_EN 1
#define OS_MBOX_QUERY_EN 1
#define OS_MEM_EN 1
#define OS_MEM_NAME_SIZE 32
#define OS_MEM_QUERY_EN 1
#define OS_MUTEX_ACCEPT_EN 1
#define OS_MUTEX_DEL_EN 1
#define OS_MUTEX_EN 1
#define OS_MUTEX_QUERY_EN 1
#define OS_Q_ACCEPT_EN 1
#define OS_Q_DEL_EN 1
#define OS_Q_EN 1
#define OS_Q_FLUSH_EN 1
#define OS_Q_POST_EN 1
#define OS_Q_POST_FRONT_EN 1
#define OS_Q_POST_OPT_EN 1
#define OS_Q_QUERY_EN 1
#define OS_SCHED_LOCK_EN 1
#define OS_SEM_ACCEPT_EN 1
#define OS_SEM_DEL_EN 1
#define OS_SEM_EN 1
#define OS_SEM_QUERY_EN 1
#define OS_SEM_SET_EN 1
#define OS_TASK_CHANGE_PRIO_EN 1
#define OS_TASK_CREATE_EN 1
#define OS_TASK_CREATE_EXT_EN 1
#define OS_TASK_DEL_EN 1
#define OS_TASK_IDLE_STK_SIZE 512
#define OS_TASK_NAME_SIZE 32
#define OS_TASK_PROFILE_EN 1
#define OS_TASK_QUERY_EN 1
#define OS_TASK_STAT_EN 1
#define OS_TASK_STAT_STK_CHK_EN 1
#define OS_TASK_STAT_STK_SIZE 512
#define OS_TASK_SUSPEND_EN 1
#define OS_TASK_SW_HOOK_EN 1
#define OS_TASK_TMR_PRIO 0
#define OS_TASK_TMR_STK_SIZE 512
#define OS_THREAD_SAFE_NEWLIB 1
#define OS_TICK_STEP_EN 1
#define OS_TIME_DLY_HMSM_EN 1
#define OS_TIME_DLY_RESUME_EN 1
#define OS_TIME_GET_SET_EN 1
#define OS_TIME_TICK_HOOK_EN 1
#define OS_TMR_CFG_MAX 16
#define OS_TMR_CFG_NAME_SIZE 16
#define OS_TMR_CFG_TICKS_PER_SEC 10
#define OS_TMR_CFG_WHEEL_SIZE 2
#define OS_TMR_EN 0

#endif /* __SYSTEM_H_ */
