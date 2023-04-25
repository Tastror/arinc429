#include "stdafx.h"
#include "DLL429D42_lib.h"
#include "cusfunc.h"

// ���ݽṹ
extern DWORD dwTxBuf[FIFO_TMAX]; // ���� FIFO
extern WORD wdTxBufLen;          // ����FIFO����

// ����ʹ�õ� 16 ������
extern DWORD m_ControlWord1;   // MCHUD/00_00 ������ 1, 25, 100K
extern DWORD m_ControlWord2;   // MCHUD/00_01 ������ 2
extern int s_Air_Speed_Real;   // MCHUD/00_02 �����
extern int s_Air_Speed;        // MCHUD/00_03 ָʾ����
extern float s_Air_Ma;         // MCHUD/00_04 �����
extern float s_Air_AirP;       // MCHUD/00_05 װ����ѹ
extern float s_Air_Attack;     // MCHUD/00_06 ����
extern int s_Air_High;         // MCHUD/00_07 �����ѹ�߶�
extern int s_Air_SpeedUD;      // MCHUD/00_08 �����߶�
extern float s_Air_Azimuth;    // MCHUD/00_09 ����
extern float s_Air_Pitch;      // MCHUD/00_10 ������
extern float s_Air_Roll;       // MCHUD/00_11 �����
extern int s_Air_HighR;        // MCHUD/00_12 ���ߵ�߶�
extern int s_Air_HighL;        // MCHUD/00_13 ��Ͱ�ȫ�߶�
extern float s_Air_Sideslip;   // MCHUD/00_14 �໬��
extern float s_Air_N;          // MCHUD/00_15 ����

// ����
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

extern int r_Air_Speed;      // �����
extern float r_Air_Roll;     // �����
extern float r_Air_Pitch;    // ������
extern int r_Air_High;       // ���ߵ�߶�
extern float r_Air_Azimuth;  // ��λ��
extern float r_Air_Sideslip; // �໬��
extern int r_Air_Speed_Real; // ָʾ����
extern float r_Air_Ma;       // �����
extern float r_Air_AirP;     // װ����ѹ
extern float r_Air_Attack;   // ����
extern int r_Air_SpeedUD;    // �����߶�
extern int r_Air_HighR;      // ��ѹ�߶�
extern int r_Air_HighL;      // ��Ͱ�ȫ�߶�
extern float r_Air_N;        // ����
extern int T;

extern CString x_Air_Speed;      // �����
extern CString x_Air_Roll;       // �����
extern CString x_Air_Pitch;      // ������
extern CString x_Air_High;       // ���ߵ�߶�
extern CString x_Air_Azimuth;    // ��λ��
extern CString x_Air_Sideslip;   // �໬��
extern CString x_Air_Speed_Real; // ָʾ����
extern CString x_Air_Ma;         // �����
extern CString x_Air_AirP;       // װ����ѹ
extern CString x_Air_Attack;     // ����
extern CString x_Air_SpeedUD;    // �����߶�
extern CString x_Air_HighR;      // ��ѹ�߶�
extern CString x_Air_HighL;      // ��Ͱ�ȫ�߶�
extern CString x_Air_N;          // ����
