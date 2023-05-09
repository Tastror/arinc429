#ifndef _CODING_H_
#define _CODING_H_

#include "stdafx.h"
#include "DLL429D42_lib.h"
#include "cusfunc.h"

// ���ݽṹ
// mother_window->dwTxBuf[FIFO_TMAX]; // ���� FIFO
// mother_window->wdTxBufLen;          // ����FIFO����

// ����ʹ�õ� 16 ������
// mother_window->m_ControlWord1;   // MCHUD/00_00 ������ 1, 25, 100K
// mother_window->m_ControlWord2;   // MCHUD/00_01 ������ 2
// mother_window->data_send_RealSpeed;   // MCHUD/00_02 �����
// mother_window->data_send_Speed;        // MCHUD/00_03 ָʾ����
// mother_window->data_send_Mach;         // MCHUD/00_04 �����
// mother_window->data_send_AirP;       // MCHUD/00_05 װ����ѹ
// mother_window->data_send_Attack;     // MCHUD/00_06 ����
// mother_window->data_send_High;         // MCHUD/00_07 �����ѹ�߶�
// mother_window->data_send_SpeedUD;      // MCHUD/00_08 �����߶�
// mother_window->data_send_Azimuth;    // MCHUD/00_09 ����
// mother_window->data_send_Pitch;      // MCHUD/00_10 ������
// mother_window->data_send_Roll;       // MCHUD/00_11 �����
// mother_window->data_send_HighR;        // MCHUD/00_12 ���ߵ�߶�
// mother_window->data_send_HighL;        // MCHUD/00_13 ��Ͱ�ȫ�߶�
// mother_window->data_send_Sideslip;   // MCHUD/00_14 �໬��
// mother_window->data_send_NormalOverload;          // MCHUD/00_15 ����

// ����
#define ControlWord1_Mask 0x30000006
#define ControlWord2_Mask 0x31000006
#define Air_RealSpeed_Mask 0x88000006
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

#endif