#include "stdafx.h"
#include "DLL429D42_lib.h"
#include "cusfunc.h"

// ���ݽṹ
DWORD dwTxBuf[FIFO_TMAX];    //���� FIFO
WORD wdTxBufLen=0;        //����FIFO����

// ����ʹ�õ� 16 ������
int     m_ControlWord1 = 0;         // MCHUD/00_00 ������ 1, 25, 100K
int     m_ControlWord2 = 0;         // MCHUD/00_01 ������ 2    
int	    s_Air_Speed_Real;           // MCHUD/00_02 �����
int	    s_Air_Speed;	            // MCHUD/00_03 ָʾ����
double	s_Air_Ma;			        // MCHUD/00_04 �����
double	s_Air_AirP;			        // MCHUD/00_05 װ����ѹ
double	s_Air_Attack;		        // MCHUD/00_06 ����
int	    s_Air_High;			        // MCHUD/00_07 �����ѹ�߶�
int		s_Air_SpeedUD;		        // MCHUD/00_08 �����߶�
float	s_Air_Azimuth;		        // MCHUD/00_09 ����
float	s_Air_Pitch;		        // MCHUD/00_10 ������
float	s_Air_Roll;			        // MCHUD/00_11 �����
int		s_Air_HighR;		        // MCHUD/00_12 ���ߵ�߶�
int		s_Air_HighL;		        // MCHUD/00_13 ��Ͱ�ȫ�߶�
float	s_Air_Sideslip;		        // MCHUD/00_14 �໬��
float	s_Air_N;			        // MCHUD/00_15 ����

// ����
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

// �Ƿ��������
bool    keep_receive = false;

// �������������
TriggerDepth_STRUCT stTriggerLevel={0};

// �忨�ľ��
HANDLE hCard = NULL;

// ����ģʽ
WORD wdMode = C429_SELFTEST;

STCOMMUNICATION stComm[CHNO_TMAX];

DWORD ReceiveData_Vector[FIFO_RMAX];

CString x_ControlWord1;
CString x_ControlWord2;

int		r_Air_Speed;		//�����
float	r_Air_Roll;			//�����
float	r_Air_Pitch;		//������
int		r_Air_High;			//���ߵ�߶�
float	r_Air_Azimuth;		//��λ��
float	r_Air_Sideslip;		//�໬��
int		r_Air_Speed_Real;	//ָʾ����
float	r_Air_Ma;			//�����
float	r_Air_AirP;			//װ����ѹ
float	r_Air_Attack;		//����
int		r_Air_SpeedUD;		//�����߶�
int		r_Air_HighR;		//��ѹ�߶�
int		r_Air_HighL;		//��Ͱ�ȫ�߶�
float	r_Air_N;			//����
int		T;

CString		x_Air_Speed;		//�����
CString	    x_Air_Roll;			//�����
CString	    x_Air_Pitch;		//������
CString		x_Air_High;			//���ߵ�߶�
CString	    x_Air_Azimuth;		//��λ��
CString	    x_Air_Sideslip;		//�໬��
CString		x_Air_Speed_Real;	//ָʾ����
CString	    x_Air_Ma;			//�����
CString	    x_Air_AirP;			//װ����ѹ
CString	    x_Air_Attack;		//����
CString		x_Air_SpeedUD;		//�����߶�
CString		x_Air_HighR;		//��ѹ�߶�
CString		x_Air_HighL;		//��Ͱ�ȫ�߶�
CString	    x_Air_N;			//����
