/*
 * rtc.h
 *
 *  Created on: 2 de ene. de 2020
 *      Author: Santiago
 */

#ifndef TASK_SUPPORT_RTC_H_
#define TASK_SUPPORT_RTC_H_
#include <lpc_types.h>
void RTCInit(void);
void RTCDeInit(void);
void RTCSetTime(uint8_t * date);
void RTCGetTime(uint8_t * date);

#endif /* TASK_SUPPORT_RTC_H_ */
