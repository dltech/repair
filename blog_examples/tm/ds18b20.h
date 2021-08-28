#ifndef H_DS18B20
#define H_DS18B20
/*
 * stm32 usart based ds18b20 lib
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

// Rom commands
#define SEARCH_ROM          0xf0
#define READ_ROM            0x33
#define MATCH_ROM           0x55
#define SKIP_ROM            0xcc
#define ALARM_SEARCH        0xec

#define FAMILY_CODE         0x28

// Function commands
#define CONVERT_T           0x44
#define READ_SCRATCHPAD     0xbe
#define WRITE_SCRATCHPAD    0x4e
#define COPY_SCRATCHPAD     0x48
#define RECALL_E2           0xb8
#define READ_POWER_SUPPLY   0xb4

// configuration
#define RESOL_9BIT          0x1f
#define RESOL_10BIT         0x3f
#define RESOL_11BIT         0x5f
#define RESOL_12BIT         0x7f

// mcu related
#define DS_PORT GPIOA
#define RX_PIN  3
#define TX_PIN  2
// mcu usart related
#define BAUD9600    0x1388
#define BAUD115200  0x01A1

// set the resolution
#define DEFAULT_RESOL       RESOL_9BIT

void dsInit(void);
int dsStart(void);
int32_t tempBlocking(void);
int32_t dsReadScratchpad(void);

#endif
