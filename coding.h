#include "stdafx.h"
#include "DLL429D42_lib.h"

// 数据结构
DWORD dwTxBuf[FIFO_TMAX];    //发送 FIFO
WORD wdTxBufLen=0;        //发送FIFO长度

// 编码使用的 16 个变量
int     m_ControlWord1 = 0;         // MCHUD/00_00 控制字 1, 25, 100K
int     m_ControlWord2 = 0;         // MCHUD/00_01 控制字 2    
int	    s_Air_Speed_Real;           // MCHUD/00_02 真空速
int	    s_Air_Speed;	            // MCHUD/00_03 指示空速
double	s_Air_Ma;			        // MCHUD/00_04 马赫数
double	s_Air_AirP;			        // MCHUD/00_05 装订气压
double	s_Air_Attack;		        // MCHUD/00_06 攻角
int	    s_Air_High;			        // MCHUD/00_07 相对气压高度
int		s_Air_SpeedUD;		        // MCHUD/00_08 升降高度
float	s_Air_Azimuth;		        // MCHUD/00_09 航向
float	s_Air_Pitch;		        // MCHUD/00_10 俯仰角
float	s_Air_Roll;			        // MCHUD/00_11 横滚角
int		s_Air_HighR;		        // MCHUD/00_12 无线电高度
int		s_Air_HighL;		        // MCHUD/00_13 最低安全高度
float	s_Air_Sideslip;		        // MCHUD/00_14 侧滑角
float	s_Air_N;			        // MCHUD/00_15 过载

// 掩码
DWORD ControlWord1_Mask     = 0x30000006;
DWORD ControlWord2_Mask     = 0x31000006;
DWORD Air_Speed_Real_Mask   = 0x88000006;
DWORD Air_Speed_Mask        = 0x86000006;
DWORD Ma_Mask               = 0x85000006;
DWORD AirP_Mask             = 0x97000006;
DWORD Attack_Mask           = 0xa1000006;
DWORD High_Mask             = 0x84000006;
DWORD SpeedUD_Mask          = 0x8a000006;
DWORD Azimuth_Mask          = 0x32000006;
DWORD Pitch_Mask            = 0x33000006;
DWORD Roll_Mask             = 0x34000006;
DWORD HighR_Mask            = 0x35000006;
DWORD HighL_Mask            = 0x36000006;
DWORD Sideslip_Mask         = 0x37000006;
DWORD N_Mask                = 0x38000006;
