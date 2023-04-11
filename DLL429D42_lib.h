#ifndef _DLL429D42_LIB_H_
#define _DLL429D42_LIB_H_

#include <windows.h>
#include <winioctl.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DLL __declspec(dllexport)

	
#define SD_MAX			4
#define LABEL_MAX		256
#define CARDID_MAX		255
#define CHNO_TMAX		2
#define CHNO_RMAX		4
#define TRIGGER_TMAX	126
#define TRIGGER_RMAX	254
#define FIFO_TMAX		127
#define FIFO_RMAX		255
#define INTERVAL_TUNIT	50
#define INTERVAL_MAX	0xFFFF
#define TXDATA_MAX		0xFFFFFFFF
	
#define FIFOEmpty 0x10
#define FIFONotFull 0x11
#define FIFOFull 0x12
#define FIFOError 0x13
#define ErrIndex 0x14


//Self Struct Definitiopn
//触发深度设置表
typedef struct TriggerDepth
{
	BYTE Chan0Depth_I;
	BYTE Chan1Depth_I;
	BYTE Chan2Depth_I;
	BYTE Chan3Depth_I;
	BYTE Chan0Depth_O;
	BYTE Chan1Depth_O;
}TriggerDepth_STRUCT;

//设置标号过滤表
typedef struct LabelTable
{
	BYTE LabFilterChan0[4][256];
	BYTE LabFilterChan1[4][256];
	BYTE LabFilterChan2[4][256];
	BYTE LabFilterChan3[4][256];
}LabelTable_STRUCT;


//DLL Function Declaration

//打开和关闭板卡
DLL BOOL __stdcall Card_Open (HANDLE *phCardHandle,BYTE CardId);
DLL BOOL __stdcall Card_Close(HANDLE hCardHandle);

//复位板卡
DLL BOOL __stdcall ResetCard(HANDLE hCardHandle);

//设置429芯片配置字及波特率
DLL void __stdcall EnableBaudrate_48K(HANDLE hCardHandle,BYTE ChannelNo,BOOL Enable);
DLL BOOL __stdcall SetConfigureWord(HANDLE hCardHandle,BYTE ChannelNo,WORD CFGWord);

//设置标号过滤功能
DLL void __stdcall SetLabelFilter(HANDLE hCardHandle,LabelTable_STRUCT *Label);//设置标号过滤表
DLL BOOL __stdcall StartLabelFilter(HANDLE hCardHandle,BYTE ChannelNo,BOOL Enable);//使能标号过滤

//添加时间标签
DLL BOOL __stdcall AddTimeTag(HANDLE hCardHandle,BYTE ChannelNo,BOOL Enable);
DLL void __stdcall StartTimeTag(HANDLE hCardHandle,BOOL Enable,LPSYSTEMTIME CurSysTime);

//定时发送功能
DLL BOOL __stdcall SetTimerIntervalB(HANDLE hCardHandle,BYTE ChannelNo,WORD Time);//设置群定时发送时间
DLL BOOL __stdcall SetTimerIntervalS(HANDLE hCardHandle,BYTE ChannelNo,WORD Time);//设置字定时发送时间
DLL BOOL __stdcall StartTimerB(HANDLE hCardHandle,BYTE ChannelNo,BOOL Enable);//使能群定时
DLL BOOL __stdcall StartTimerS(HANDLE hCardHandle,BYTE ChannelNo,BOOL Enable);//使能字定时

//设置触发深度
DLL void __stdcall SetTriggerDepth(HANDLE hCardHandle,TriggerDepth_STRUCT *Depth);

//读取FIFO状态
DLL BOOL __stdcall IsFIFOTriggered_R(HANDLE hCardHandle,BYTE ChannelNo);
DLL BYTE __stdcall ReadFIFOStatus_R(HANDLE hCardHandle,BYTE ChannelNo);
DLL BOOL __stdcall IsFIFOTriggered_S(HANDLE hCardHandle,BYTE ChannelNo);
DLL BYTE __stdcall ReadFIFOStatus_S(HANDLE hCardHandle,BYTE ChannelNo);
DLL BOOL __stdcall EnablReadFIFO(HANDLE hCardHandle,BYTE ChannelNo);//使能读FIFO
DLL BOOL __stdcall DisablReadFIFO(HANDLE hCardHandle);//禁止读FIFO

//读取数据
DLL DWORD __stdcall ReceiveData(HANDLE hCardHandle,BYTE ChannelNo);
DLL BOOL __stdcall Enable_R(HANDLE hCardHandle,BOOL Enable);//使能接收

//发送数据
DLL BOOL __stdcall SendData(HANDLE hCardHandle,BYTE ChannelNo,BYTE Len,DWORD *DataAry);


#ifdef __cplusplus
}
#endif

#endif