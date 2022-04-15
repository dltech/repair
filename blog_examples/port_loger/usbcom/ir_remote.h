#ifndef H_IR_REMOTE
#define H_IR_REMOTE
/*
 * Part of USB HID gamepad STM32 based solution.
 *
 * Copyright 2021 Mikhail Belkin <dltech174@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "inttypes.h"
#include "../lib/regs/gpio_regs.h"
#include "../lib/STM32F103_CMSIS/stm32f103.h"

// port poll frequency in us
#define POLL_RATE        1000//200
// port read frame in ms
#define SEQUENCE_TIME   100
// symbol decode rate in ms
#define READ_RATE       25
// calculating for fre prog
#define POLL_PSC        65534//((SYSTEM_CLOCK / 1000000) * POLL_RATE) - 1
#define SEQUENCE_LEN    63
//#define SEQUENCE_LEN    SEQUENCE_TIME * 1000 / POLL_RATE
#define MAXIMAL_PSC     65534
#define DECODE_RATE_ARR SEQUENCE_LEN
//#define DECODE_RATE_ARR (((SYSTEM_CLOCK / MAXIMAL_PSC) * SEQUENCE_TIME) / 1000) -1

// pin definitions
#define IR_PORT     GPIOA_IDR
#define IR_PIN      GPIO0
#define IR_PIN_INIT 0U

// ir information
typedef struct {
    // address of remote control
    uint32_t   address;
    // code table (ir codes according to keyboard codes)
    uint8_t codeTable[255];
    int isKeyPressed;
} remotePropStruct;

// call this to init receiving of IR codes
void irInit(void);

#endif
