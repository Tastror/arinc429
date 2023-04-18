/*
	Module Name: cusfunc.h

	Description: 
		Being included by cusfunc.cpp, this file declared a number of function
	we usually used in project.

	Author: Steven Ren by [Code Boy Station]

	History:
		2005/11/17 : this module is created.
*/


#ifndef _CUSFUNC_H_
#define _CUSFUNC_H_

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif


// + ----------------------------------------------
//		429 communication parameters definition
// - ----------------------------------------------

//	parity definition
//
#define C429_PARITY_ODD		0
#define C429_PARITY_EVEN	1
#define C429_PARITY_NONE	2

// bits Rate
//
#define C429_BITRATE100K	0
#define C429_BITRATE48K	1
#define C429_BITRATE125K	2

// work mode
//
#define C429_NORMAL		0
#define C429_SELFTEST	1

// error
//
#define C429_BAUDRATE_ERR	0xFFFF
#define C429_PARITY_ERR		0xFFFE
#define C429_WORKMODE_ERR	0xFFFD


typedef struct _ST_CW429{
	unsigned short baudrate;
	unsigned short parity;
	unsigned short workmode;
} STCW429, *LPSTCW429;

typedef struct _STRUCT_COMMUICATION {
	int iSelBR;
	int iSelParity;
} STCOMMUNICATION, *LPSTCOMMUNICATION;



// + ----------------------------------------------
//		custom functions declaration
// - ----------------------------------------------

unsigned short Get429ConfigureWord(unsigned short baudrate, unsigned short parity, unsigned short workmode);
unsigned long Resume429Word(unsigned long dw429w);
//unsigned long HEXS(char *decString);
void CHTIME(DWORD ctime, DWORD gtime, char *rtString);
void Save_ReceiveData(DWORD d,DWORD *Data_Vector);

#ifdef __cplusplus
}
#endif

#endif


