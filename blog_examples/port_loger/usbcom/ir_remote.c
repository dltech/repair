/*
 * Part of USB HID IR adapter. Main file, of IR, initiates IR receiver
 * periodical poll. Runs code recognition and sends a report with a symbol
 * according to a table.
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
#include "../lib/regs/tim_regs.h"
#include "../lib/regs/rcc_regs.h"
#include "usb_core.h"
#include "ir_remote.h"

// A little of global variables, in order to keep data between interrupt calls
uint8_t irFramee[SEQUENCE_LEN];
volatile remotePropStruct remoteProp;
extern volatile usbPropStruct usbProp;

void gpioInit(void);
void sendReportIrqInit(void);


void gpioInit()
{
    // GPIO input mode
    RCC_APB2ENR |= IOPAEN;
    GPIOA_CRL = CNF_FLOATING(IR_PIN_INIT);
    GPIOA_ODR = 0;//IR_PIN;
}

// setting up timer interrupt for sending a report
void sendReportIrqInit()
{
    RCC_APB1ENR |= TIM3EN;
    TIM3_CR1   = (uint32_t) CKD_CK_INT;
    TIM3_PSC   = (uint32_t) POLL_PSC;// MAXIMAL_PSC;
    TIM3_ARR   = (uint32_t) 1;//SEQUENCE_LEN; // DECODE_RATE_ARR;
    TIM3_DIER  = (uint32_t) UIE;
    TIM3_CR1  |= (uint32_t) CEN;
//    nvic_set_priority(NVIC_TIM2_IRQ, 0x00);
    TIM3_SR    = 0;
    TIM3_EGR  |= (uint32_t) UG;
    NVIC_EnableIRQ(TIM3_IRQn);
}

// main init
void irInit()
{
    gpioInit();
    sendReportIrqInit();
}

void TIM3_Handler()
{
    TIM3_SR = 0;
    if(usbProp.deviceState != CONFIGURED)   return;
    static int i;
    irFramee[i++] = (uint8_t)IR_PORT;
    if(i >= SEQUENCE_LEN) {
        i=0;
        vcpTx(irFramee,SEQUENCE_LEN);
    }
}
