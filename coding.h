#include "stdafx.h"
#include "DLL429D42_lib.h"
#include "cusfunc.h"

// 数据结构
extern DWORD dwTxBuf[FIFO_TMAX]; // 发送 FIFO
extern WORD wdTxBufLen;          // 发送FIFO长度

// 编码使用的 16 个变量
extern DWORD m_ControlWord1;   // MCHUD/00_00 控制字 1, 25, 100K
extern DWORD m_ControlWord2;   // MCHUD/00_01 控制字 2
extern int s_Air_Speed_Real;   // MCHUD/00_02 真空速
extern int s_Air_Speed;        // MCHUD/00_03 指示空速
extern float s_Air_Ma;         // MCHUD/00_04 马赫数
extern float s_Air_AirP;       // MCHUD/00_05 装订气压
extern float s_Air_Attack;     // MCHUD/00_06 攻角
extern int s_Air_High;         // MCHUD/00_07 相对气压高度
extern int s_Air_SpeedUD;      // MCHUD/00_08 升降高度
extern float s_Air_Azimuth;    // MCHUD/00_09 航向
extern float s_Air_Pitch;      // MCHUD/00_10 俯仰角
extern float s_Air_Roll;       // MCHUD/00_11 横滚角
extern int s_Air_HighR;        // MCHUD/00_12 无线电高度
extern int s_Air_HighL;        // MCHUD/00_13 最低安全高度
extern float s_Air_Sideslip;   // MCHUD/00_14 侧滑角
extern float s_Air_N;          // MCHUD/00_15 过载

// 掩码
#define ControlWord1_Mask 0x30000006
#define ControlWord2_Mask 0x31000006
#define Air_Speed_Real_Mask 0x88000006
#define Air_Speed_Mask 0x86000006
#define Ma_Mask 0x85000006
#define AirP_Mask 0x97000006
#define Attack_Mask 0xa1000006
#define High_Mask 0x84000006
#define SpeedUD_Mask 0x8a000006
#define Azimuth_Mask 0x32000006
#define Pitch_Mask 0x33000006
#define Roll_Mask 0x34000006
#define HighR_Mask 0x35000006
#define HighL_Mask 0x36000006
#define Sideslip_Mask 0x37000006
#define N_Mask 0x38000006

// 是否继续解码
extern bool keep_receive;

// 缓冲区触发深度
extern TriggerDepth_STRUCT stTriggerLevel;

// 板卡的句柄
extern HANDLE hCard;

// 工作模式
extern WORD wdMode;

extern STCOMMUNICATION stComm[CHNO_TMAX];

extern DWORD ReceiveData_Vector[FIFO_RMAX];

extern CString x_ControlWord1;
extern CString x_ControlWord2;

extern int r_Air_Speed;      // 真空速
extern float r_Air_Roll;     // 横滚角
extern float r_Air_Pitch;    // 俯仰角
extern int r_Air_High;       // 无线电高度
extern float r_Air_Azimuth;  // 方位角
extern float r_Air_Sideslip; // 侧滑角
extern int r_Air_Speed_Real; // 指示空速
extern float r_Air_Ma;       // 马赫数
extern float r_Air_AirP;     // 装订气压
extern float r_Air_Attack;   // 攻角
extern int r_Air_SpeedUD;    // 升降高度
extern int r_Air_HighR;      // 气压高度
extern int r_Air_HighL;      // 最低安全高度
extern float r_Air_N;        // 过载
extern int T;

extern CString x_Air_Speed;      // 真空速
extern CString x_Air_Roll;       // 横滚角
extern CString x_Air_Pitch;      // 俯仰角
extern CString x_Air_High;       // 无线电高度
extern CString x_Air_Azimuth;    // 方位角
extern CString x_Air_Sideslip;   // 侧滑角
extern CString x_Air_Speed_Real; // 指示空速
extern CString x_Air_Ma;         // 马赫数
extern CString x_Air_AirP;       // 装订气压
extern CString x_Air_Attack;     // 攻角
extern CString x_Air_SpeedUD;    // 升降高度
extern CString x_Air_HighR;      // 气压高度
extern CString x_Air_HighL;      // 最低安全高度
extern CString x_Air_N;          // 过载
