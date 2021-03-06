/*
 * rtc.c
 *
 *  Created on: 2 de ene. de 2020
 *      Author: Santiago
 */

#include "../task_support/rtc.h"

#include <lpc17xx_rtc.h>
typedef enum {
	Jan = ('J' << 16) + ('a' << 8) + 'n',
	Feb = ('F' << 16) + ('e' << 8) + 'b',
	Mar = ('M' << 16) + ('a' << 8) + 'r',
	Apr = ('A' << 16) + ('p' << 8) + 'r',
	May = ('M' << 16) + ('a' << 8) + 'y',
	Jun = ('J' << 16) + ('u' << 8) + 'n',
	Jul = ('J' << 16) + ('u' << 8) + 'l',
	Ago = ('A' << 16) + ('g' << 8) + 'o',
	Sep = ('S' << 16) + ('e' << 8) + 'p',
	Oct = ('O' << 16) + ('c' << 8) + 't',
	Nov = ('N' << 16) + ('o' << 8) + 'v',
	Dec = ('D' << 16) + ('e' << 8) + 'c'
} MonthName;

static uint8_t GetMonth(uint8_t * month){
	uint32_t value = (month[0] << 16) + (month[1] << 8) + month[2];
	switch (value)
	{
	case Jan:
		return 1;
	case Feb:
		return 2;
	case Mar:
		return 3;
	case Apr:
		return 4;
	case May:
		return 5;
	case Jun:
		return 6;
	case Jul:
		return 7;
	case Ago:
		return 8;
	case Sep:
		return 9;
	case Oct:
		return 10;
	case Nov:
		return 11;
	case Dec:
		return 12;
	default:
		return 0;
	}
}
void RTCInit(void){
	RTC_Init(LPC_RTC);
	RTC_Cmd(LPC_RTC,ENABLE);
}
void RTCDeInit(void){
	RTC_Cmd(LPC_RTC,DISABLE);
	RTC_DeInit(LPC_RTC);
}
void RTCSetTime(uint8_t * date){
	//Thu, 02 Jan 2020 23:33:11 GMT

	LPC_RTC->YEAR = (date[12] - '0')*1000 + (date[13] - '0') * 100 + (date[14] - '0') * 10 + (date[15] - '0');
	LPC_RTC->MONTH = GetMonth(&date[8]);
	LPC_RTC->DOM = (date[5] - '0') *10 + (date[6] - '0');
	LPC_RTC->HOUR= (date[17] - '0')*10 + (date[18] - '0');
	LPC_RTC->MIN = (date[20] - '0')*10 + (date[21] - '0');
	LPC_RTC->SEC = (date[23] - '0')*10 + (date[24] - '0');

}
void RTCGetTime(uint8_t * date){

}


