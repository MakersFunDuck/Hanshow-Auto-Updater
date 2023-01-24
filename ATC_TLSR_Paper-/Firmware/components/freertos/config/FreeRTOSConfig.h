/*
 * FreeRTOS Kernel V10.1.1
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

/* 1�� ��ռʽ���� 0��Э��ʽ */
#define configUSE_PREEMPTION                                                      1

/* tc32 Ӳ����֧�����෽�� */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION                                   0

/* ��configUSE_TICKLESS_IDLE����Ϊ1��ʹ�� �͹����޵δ�ģʽ��������Ϊ0��ʹ
 * �δ��ж�ʼ�ձ������С���������FreeRTOS�˿ڶ��ṩ�͹����޵δ�ʵ�֡�*/
#define configUSE_TICKLESS_IDLE                                                   1

/* See into vPortSuppressTicksAndSleep source code for explanation */
#define configUSE_TICKLESS_IDLE_SIMPLE_DEBUG                                      0

/* ϵͳʱ�� */
#define configCPU_CLOCK_HZ                                                        (16000000UL)  /*SystemCoreClock*/

/* �δ��жϵ�Ƶ�� */
#define configTICK_RATE_HZ                                                        1000

/* Ӧ�ó���������� �����ȼ��� */
#define configMAX_PRIORITIES                                                      ( 6 )

/* ��������ʹ�õĶ�ջ��С ��λΪ *4 byte */
#define configMINIMAL_STACK_SIZE                                                  ( 96 )

/*FreeRTOS���п��õ�RAM(��)���� */
#define configTOTAL_HEAP_SIZE                                                     ( 4096*2 )

/* task ���ֳ��� */
#define configMAX_TASK_NAME_LEN                                                   ( 8 )

/* ʱ����'ticks'������ - ������RTOS�ں���������tick�ж�ִ�еĴ���
 * ��configUSE_16_BIT_TICKS����Ϊ1�ᵼ��TickType_t�����壨typedef'ed��
 * Ϊ�޷���16λ���͡���configUSE_16_BIT_TICKS����Ϊ0�ᵼ��TickType_t������
 * ��typedef'ed��Ϊ�޷���32λ���� */
#define configUSE_16_BIT_TICKS                                                    0

/* ��ִ�������������ͬ���ȼ�����������У����������Ƿ������ռ�Ļ��� */
#define configIDLE_SHOULD_YIELD                                                   0

/* ������ʹ�� */
#define configUSE_MUTEXES                                                         0

/* �ݹ黥����ʹ�� */
#define configUSE_RECURSIVE_MUTEXES                                               0

/* �ź���ʹ�� */
#define configUSE_COUNTING_SEMAPHORES                                             1

/* �Ѿ����� */
#define configUSE_ALTERNATIVE_API                                                 0    /* Deprecated! */

/* �������ע��������к��ź���*/
#define configQUEUE_REGISTRY_SIZE                                                 2

/* ���м�ʹ��*/
#define configUSE_QUEUE_SETS                                                      0

/* ʱ��Ƭʹ��*/
#define configUSE_TIME_SLICING                                                    1

/* newlibʹ��*/
#define configUSE_NEWLIB_REENTRANT                                                0

#define configENABLE_BACKWARD_COMPATIBILITY                                       1

/* Hook function related definitions. */
#define configUSE_IDLE_HOOK                                                       0
#define configUSE_TICK_HOOK                                                       0

/* ��ջ���*/
#define configCHECK_FOR_STACK_OVERFLOW                                            0

/* ���ڴ����빳�Ӽ��*/
#define configUSE_MALLOC_FAILED_HOOK                                              0

/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS                                             0
#define configUSE_TRACE_FACILITY                                                  0
#define configUSE_STATS_FORMATTING_FUNCTIONS                                      0

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                                                     0
#define configMAX_CO_ROUTINE_PRIORITIES                                           ( 2 )

/* Software timer definitions. */
/* ��ʱ��ʹ��*/
#define configUSE_TIMERS                                                          1

/* ��ʱ�����ȼ�*/
#define configTIMER_TASK_PRIORITY                                                 ( 2 )

/* ��ʱ�����г���*/
#define configTIMER_QUEUE_LENGTH                                                  32

/* ��ʱ�����ж�ջ���*/
#define configTIMER_TASK_STACK_DEPTH                                              ( 80 )

/* Tickless Idle configuration. */
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP                                     3		//  sleep duration must  greater than 3 ms


/* Define to trap errors during development. */
#define configASSERT( x )                                                         //ASSERT(x)

/* FreeRTOS MPU specific definitions. */
#define configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS                    0

/* Optional functions - most linkers will remove unused functions anyway. */
#define INCLUDE_vTaskPrioritySet                                                  1
#define INCLUDE_uxTaskPriorityGet                                                 1
#define INCLUDE_vTaskDelete                                                       1
#define INCLUDE_vTaskSuspend                                                      1
#define INCLUDE_xResumeFromISR                                                    1
#define INCLUDE_vTaskDelayUntil                                                   1
#define INCLUDE_vTaskDelay                                                        1
#define INCLUDE_xTaskGetSchedulerState                                            1
#define INCLUDE_xTaskGetCurrentTaskHandle                                         1
#define INCLUDE_uxTaskGetStackHighWaterMark                                       1
#define INCLUDE_xTaskGetIdleTaskHandle                                            1
#define INCLUDE_xTimerGetTimerDaemonTaskHandle                                    1
#define INCLUDE_pcTaskGetTaskName                                                 1
#define INCLUDE_eTaskGetState                                                     1
#define INCLUDE_xEventGroupSetBitFromISR                                          1
#define INCLUDE_xTimerPendFunctionCall                                            1

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
//#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    1

/* Code below should be only used by the compiler, and not the assembler. */
#if !(defined(__ASSEMBLY__) || defined(__ASSEMBLER__))

#endif /* !assembler */

#endif /* FREERTOS_CONFIG_H */
