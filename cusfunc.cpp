/*
	Module Name: cusfunc.cpp

	Description: 
		this file declared a number of function	we usually used in project.

	Author: WaterBaby 

	History:
		2007/9/10 : this module is created.
*/

#include "stdafx.h"
#include "cusfunc.h"


/* ++

	Routine Description:
		configure 429 word with baudrate and parity.

	Arguments:
		1) baudrate: [IN]
			0: 100k
			1: 50k
			2: 12.5k
		2) parity: [IN]
			0: none parity;
			1: odd parity;
			2: even parity.
		3) workmode: [IN]
			0: normal
			1: selftest
		
	Return Value:
		if this function is succeeded, return value is the 429 configure word for dei1016 chip,
	else is error word returned as followed:
		baudrate error: 0xFFFF
		parity error:	0xFFFE
		workmode error: 0xFFFD

-- */
unsigned short Get429ConfigureWord(unsigned short baudrate,unsigned short parity, unsigned short workmode)
{
	unsigned short cw=0x0000;

	switch (baudrate) // configure baudrate
	{
		case C429_BITRATE100K:
			cw = cw & 0x9ff0;
			break;
		case C429_BITRATE48K:
			cw = cw & 0x9ff0;
			break;
		case C429_BITRATE125K:
			cw = cw | 0x6000;
			break;
		default:
			return C429_BAUDRATE_ERR;
			break;
	}

	switch (parity) // configure parity
	{
		case C429_PARITY_ODD:
			cw = cw | 0x0010;
			break;
		case C429_PARITY_EVEN:
			cw = cw | 0x1010;
			break;
		case C429_PARITY_NONE:
			cw = cw & 0xefe0;
			break;
		default:
			return C429_PARITY_ERR;
			break;
	}

	switch (workmode) // work mode
	{
		case C429_NORMAL:
			cw = cw | 0x0020;
			break;
		case C429_SELFTEST:
			cw = cw & 0xffd0;
			break;
		default:
			return C429_WORKMODE_ERR;
			break;
	}

	return cw;
}


/* ++

	Routine Description:
		reception of dei1016 chip can automatic change received data with odd parity,
	so we must resume the data to an original data.

	Arguments:
		1) dw429w: [IN] received 429 word from dei1016 receiption channels.
		
	Return Value:
		the return value is a resumed data.

	Comments:
		this function only can be used when the parity of dei1016 was disabled.

-- */

unsigned long Resume429Word(unsigned long dw429w)
{
	unsigned long dw=dw429w, tp=dw429w;
	int bitsNum=0;
	int i=0;
	unsigned char bit8IsZero=0;

	// bit 8 == 0
	if ((tp&0x00000100)==0x00000100)
	{
		bit8IsZero = 0;
	}
	else
	{
		bit8IsZero = 1;
	}

	// odd bits number of data
	tp = tp&0xfffffeff;
	for (i=0; i<32; i++)
	{
		if ((tp&0x00000001)==0x00000001)
		{
			bitsNum++;
		}
		tp = tp>>1;
	}

	if (bit8IsZero==1)
	{
		if ((bitsNum%2)==0)
		{
			dw = dw|0x00000100;
		}
	}
	else
	{
		if ((bitsNum%2)==0)
		{
			dw = dw&0xfffffeff;
		}
	}

	return dw;	
}


/* ++

	Routine Description:
		change string to number in HEX.

	Arguments:
		1) decString: [IN] dest string.
		
	Return Value:
		the return value always be a DWORD byte data.

-- */
DWORD HEXS(char *decString)
{
	DWORD hexValue=0;
	DWORD sl=0;
	BOOL isWhile=FALSE;
	DWORD idx=0;
	char str[256];
	BYTE ct=0;

	sl=strlen(decString);
	if((sl>0) && (sl<256))
		isWhile=TRUE;
	strcpy(str,decString);
	idx=0;
	while(isWhile)
	{
		ct=(BYTE)(str[idx]);
		switch(ct)
		{
		case 48: // "0"
			hexValue=hexValue<<4;
			hexValue+=0x0;
			break;
		case 49: // "1"
			hexValue=hexValue<<4;
			hexValue+=0x01;
			break;
		case 50: // "2"
			hexValue=hexValue<<4;
			hexValue+=0x02;
			break;
		case 51: // "3"
			hexValue=hexValue<<4;
			hexValue+=0x03;
			break;
		case 52: // "4"
			hexValue=hexValue<<4;
			hexValue+=0x04;
			break;
		case 53: // "5"
			hexValue=hexValue<<4;
			hexValue+=0x05;
			break;
		case 54: // "6"
			hexValue=hexValue<<4;
			hexValue+=0x06;
			break;
		case 55: // "7"
			hexValue=hexValue<<4;
			hexValue+=0x07;
			break;
		case 56: // "8"
			hexValue=hexValue<<4;
			hexValue+=0x08;
			break;
		case 57: // "9"
			hexValue=hexValue<<4;
			hexValue+=0x09;
			break;
		case 65: // "A"
			hexValue=hexValue<<4;
			hexValue+=0x0a;
			break;
		case 97: // "a"
			hexValue=hexValue<<4;
			hexValue+=0x0a;
			break;
		case 66: // "B"
			hexValue=hexValue<<4;
			hexValue+=0x0b;
			break;
		case 98: // "b"
			hexValue=hexValue<<4;
			hexValue+=0x0b;
			break;
		case 67: // "C"
			hexValue=hexValue<<4;
			hexValue+=0x0c;
			break;
		case 99: // "c"
			hexValue=hexValue<<4;
			hexValue+=0x0c;
			break;
		case 68: // "D"
			hexValue=hexValue<<4;
			hexValue+=0x0d;
			break;
		case 100: // "d"
			hexValue=hexValue<<4;
			hexValue+=0x0d;
			break;
		case 69: // "E"
			hexValue=hexValue<<4;
			hexValue+=0x0e;
			break;
		case 101: // "e"
			hexValue=hexValue<<4;
			hexValue+=0x0e;
			break;
		case 70: // "F"
			hexValue=hexValue<<4;
			hexValue+=0x0f;
			break;
		case 102: // "f"
			hexValue=hexValue<<4;
			hexValue+=0x0f;
			break;
		default: //unknown char
			isWhile=FALSE;
			break;
		}
		idx++;
		if(idx>=sl)
			isWhile=FALSE;
	}

	return  hexValue;
}


void CHTIME(DWORD ctime, DWORD gtime, char *rtString)
{
	DWORD t=0, d=0;
	char s[80];
	WORD hour=0, minute=0, second=0, millseconds=0;

	//  calculate the hour / minute / second / millseconds
	//
	t = ctime + (gtime/20);
	hour = (WORD) (t/3600000);
	t = t - hour*3600000;
	minute = (WORD) (t/60000);
	t = t - minute*60000;
	second = (WORD) (t/1000);
	millseconds = (WORD)(t - second*1000);

	//  link string follow the data
	//
	memset(s, 0, sizeof(s));
	sprintf(s, "-%02d:%02d:%02d.%03d", hour, minute, second, millseconds);
//	sprintf(s,"-%8x",gtime);
	strcat(rtString, s);
}

