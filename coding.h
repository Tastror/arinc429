#include "stdafx.h"
#include "DLL429D42_lib.h"
#include "cusfunc.h"

// ���ݽṹ
extern DWORD dwTxBuf[FIFO_TMAX]; // ���� FIFO
extern WORD wdTxBufLen;          // ����FIFO����

// ����ʹ�õ� 16 ������
extern DWORD m_ControlWord1;   // MCHUD/00_00 ������ 1, 25, 100K
extern DWORD m_ControlWord2;   // MCHUD/00_01 ������ 2
extern int data_send_RealSpeed;   // MCHUD/00_02 �����
extern int data_send_Speed;        // MCHUD/00_03 ָʾ����
extern float data_send_Mach;         // MCHUD/00_04 �����
extern float data_send_AirP;       // MCHUD/00_05 װ����ѹ
extern float data_send_Attack;     // MCHUD/00_06 ����
extern int data_send_High;         // MCHUD/00_07 �����ѹ�߶�
extern int data_send_SpeedUD;      // MCHUD/00_08 �����߶�
extern float data_send_Azimuth;    // MCHUD/00_09 ����
extern float data_send_Pitch;      // MCHUD/00_10 ������
extern float data_send_Roll;       // MCHUD/00_11 �����
extern int data_send_HighR;        // MCHUD/00_12 ���ߵ�߶�
extern int data_send_HighL;        // MCHUD/00_13 ��Ͱ�ȫ�߶�
extern float data_send_Sideslip;   // MCHUD/00_14 �໬��
extern float data_send_NormalOverload;          // MCHUD/00_15 ����

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

// �Ƿ��������
extern bool keep_receive;

// �������������
extern TriggerDepth_STRUCT stTriggerLevel;

// �忨�ľ��
extern HANDLE hCard;

// ����ģʽ
extern WORD wdMode;

extern STCOMMUNICATION stComm[CHNO_TMAX];

extern DWORD ReceiveData_Vector[FIFO_RMAX];

extern CString x_ControlWord1;
extern CString x_ControlWord2;

extern int data_receive_Speed;      // �����
extern float data_receive_Roll;     // �����
extern float data_receive_Pitch;    // ������
extern int data_receive_High;       // ���ߵ�߶�
extern float data_receive_Azimuth;  // ��λ��
extern float data_receive_Sideslip; // �໬��
extern int data_receive_RealSpeed; // ָʾ����
extern float data_receive_Mach;       // �����
extern float data_receive_AirP;     // װ����ѹ
extern float data_receive_Attack;   // ����
extern int data_receive_SpeedUD;    // �����߶�
extern int data_receive_HighR;      // ��ѹ�߶�
extern int data_receive_HighL;      // ��Ͱ�ȫ�߶�
extern float data_receive_NormalOverload;        // ����
extern int time_counter;

extern CString data_difference_Speed;      // �����
extern CString data_difference_Roll;       // �����
extern CString data_difference_Pitch;      // ������
extern CString data_difference_High;       // ���ߵ�߶�
extern CString data_difference_Azimuth;    // ��λ��
extern CString data_difference_Sideslip;   // �໬��
extern CString data_difference_RealSpeed; // ָʾ����
extern CString data_difference_Mach;         // �����
extern CString data_difference_AirP;       // װ����ѹ
extern CString data_difference_Attack;     // ����
extern CString data_difference_SpeedUD;    // �����߶�
extern CString data_difference_HighR;      // ��ѹ�߶�
extern CString data_difference_HighL;      // ��Ͱ�ȫ�߶�
extern CString data_difference_NormalOverload;          // ����
