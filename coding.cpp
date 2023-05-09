#include "stdafx.h"
#include "ARNIC429.h"
#include "MainWindow.h"

#include "coding.h"
#include <assert.h>




static UINT cal_parity(DWORD a) {
    UINT res = 0;
    while (a > 0) {
        res ^= (a % 2);
        a /= 2;
    }
    assert(res == 0 || res == 1);
    return res;
}

static void set_value_parity(DWORD value) {
    for (int i = 14; i <= 29; i++) {
        dwTxBuf[wdTxBufLen] |= (value % 2) << (32 - i);
        value /= 2;
    }
    // ������żУ��
    dwTxBuf[wdTxBufLen] |= cal_parity(dwTxBuf[wdTxBufLen]);
}

static DWORD check_value(char *name, DWORD value, DWORD mask, bool check_parity) {
    // �� value 14 λ�� 29 λΪ 0
    // ���ͱ�ʶ���Ƿ���ͬ
    DWORD ident = value & ~0x0007fff8;
    if (ident != mask) {
        char tmp[100];
        strcpy(tmp, name);
        strcat(tmp, " has wrong ident");
        perror(tmp);
    }

    // �����żУ���Ƿ���ȷ
    UINT parity = cal_parity(value);
    if (parity != 0) {
        char tmp[100];
        strcpy(tmp, name);
        strcat(tmp, " has wrong parity");
        perror(tmp);
    }

    // ���ؽ���õ���ֵ
    value &= 0x0007fff8;
    return value;
}

void CMainWindow::Coding() {
    wdTxBufLen=0;
    
    // ������ 1��2
    dwTxBuf[wdTxBufLen] = m_ControlWord1;
    dwTxBuf[++wdTxBufLen] = m_ControlWord2;
    
    // �����
    // ��ΧΪ 0 ~ 4096, �ֱ���Ϊ (4096/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Air_RealSpeed_Mask;
    DWORD speed_real = (DWORD)(data_send_RealSpeed/(4096.0/32768));
    set_value_parity(speed_real);
    
    // ָʾ����
    // ��ΧΪ 0 ~ 2048, �ֱ���Ϊ (2048/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Air_Speed_Mask;
    DWORD speed = (DWORD)(data_send_Speed/(2048.0/32768));
    set_value_parity(speed);
    
    // �����
    // ��ΧΪ 0 ~ 4.096, �ֱ���Ϊ (4.096/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Ma_Mask;
    // �����������
    data_send_Mach = data_send_Speed/(3.6/340);
    DWORD ma = (DWORD)(data_send_Mach/(4.096/32768));
    set_value_parity(ma);

    // װ����ѹ
    // ��ΧΪ -128 ~ 128, �ֱ���Ϊ (128/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | AirP_Mask;
    DWORD airP = (DWORD)(data_send_AirP/(128.0/32768));
    set_value_parity(airP);

    // ����
    // ��ΧΪ -45 ~ 45, �ֱ���Ϊ (45/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Attack_Mask;
    DWORD attack = (DWORD)(data_send_Attack/(45.0/32768));
    set_value_parity(attack);

    // �����ѹ�߶�
    // ��ΧΪ 0 ~ 32768, �ֱ���Ϊ 1
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | High_Mask;
    DWORD high = (DWORD)(data_send_High);
    set_value_parity(high);

    // �����ٶ�
    // ��ΧΪ -512 ~ 512, �ֱ���Ϊ (512/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | SpeedUD_Mask;
    DWORD speedUD = (DWORD)(data_send_SpeedUD/(512.0/32768));
    set_value_parity(speedUD);
    
    // ����
    // ��ΧΪ 0 ~ 360, �ֱ���Ϊ (360/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Azimuth_Mask;
    DWORD azimuth = (DWORD)(data_send_Azimuth/(360.0/32768));
    set_value_parity(azimuth);

    // ������
    // ��ΧΪ -180 ~ 180, �ֱ���Ϊ (180/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Pitch_Mask;
    DWORD pitch = (DWORD)(data_send_Pitch/(180.0/32768));
    set_value_parity(pitch);

    // �����
    // ��ΧΪ -180 ~ 180, �ֱ���Ϊ (180/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Roll_Mask;
    DWORD roll = (DWORD)(data_send_Roll/(180.0/32768));
    set_value_parity(roll);
    
    // ���ߵ�߶�
    // ��ΧΪ 0 ~ 1524, �ֱ���Ϊ (1524/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | HighR_Mask;
    DWORD highR = (DWORD)(data_send_HighR/(1524.0/32768));
    set_value_parity(highR);

    // ��Ͱ�ȫ�߶�
    // ��ΧΪ 0 ~ 1500, �ֱ���Ϊ (1500/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | HighL_Mask;
    DWORD highL = (DWORD)(data_send_HighL/(1500.0/32768));
    set_value_parity(highL);

    // �໬��
    // ��ΧΪ -10 ~ 10, �ֱ���Ϊ (10/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Sideslip_Mask;
    DWORD sideslip = (DWORD)(data_send_Sideslip/(10.0/32768));
    set_value_parity(sideslip);

    // �������
    // ��ΧΪ -10 ~ 10, �ֱ���Ϊ (10/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | N_Mask;
    DWORD n = (DWORD)(data_send_NormalOverload/(10.0/32768));
    set_value_parity(n);
}

void CMainWindow::Decoding(LPVOID lpParam) {
    HWND hwnd = (HWND)lpParam;
    DWORD d = 0;
    int i = 0;
    // ?
    BYTE chno = 0;
    BYTE btTriggerLevel = 0;

    while (keep_receive) {
        // Get Triger Level
        btTriggerLevel = stTriggerLevel.Chan0Depth_I;

        // Rx channel 1 ~ CHNO_RMAX
        // ���й���
        if (btTriggerLevel > 0) {
            if (IsFIFOTriggered_R(hCard, chno)) {
                // ʹ�ܶ� FIFO ����
                EnablReadFIFO(hCard, chno);
                // �����������
                while ((ReadFIFOStatus_R(hCard, chno) != FIFOEmpty) &&
                (ReadFIFOStatus_R(hCard, chno) != FIFOError)) {
                    d = ReceiveData(hCard, chno);
                    if ((wdMode == C429_SELFTEST) && (stComm[chno / 2].iSelParity == C429_PARITY_NONE)) {
                        d = Resume429Word(d);
                    }
                    Save_ReceiveData(d, ReceiveData_Vector + i);
                }
                // �رն� FIFO ����
                DisablReadFIFO(hCard);
            }
        } 
        // �����й���
        else {
            // �� recieveFIFO �����Ҳ����ʱ
            if ((ReadFIFOStatus_R(hCard, chno) != FIFOEmpty) && (ReadFIFOStatus_R(hCard, chno) != FIFOError))
            {
                // ʹ�ܶ� FIFO ����
                EnablReadFIFO(hCard, chno);
                d = ReceiveData(hCard, chno);
                if ((wdMode == C429_SELFTEST) && (stComm[chno / 2].iSelParity == C429_PARITY_NONE)) // resume 429 Word
                {
                    d = Resume429Word(d);
                }
                DWORD temp;  
                temp = d >> 24;
                short s;
                // ���ݱ�ʶ���ж����ĸ�����
                switch (temp)
                {
                    case 0x30://������1
                        data_ControlWord1.Format(_T("%08x"), d); break;
                        //0000 0110 0011 0000
                    case 0x31://������2
                        data_ControlWord2.Format(_T("%08x"), d); break;
                        //0000 0110 0011 0001
                    
                    case 0x88:    //�����
                        s = (short)(d >> 16);
                        data_receive_RealSpeed = s * (4096. / 32768);
                        data_difference_RealSpeed.Format(_T("%08x"), d); break;
                        //0000 0110 1000 1000
                    case 0x86://ָʾ����
                        s = (short)(d >> 16);
                        data_receive_Speed = s * (2048. / 32768);
                        data_difference_Speed.Format(_T("%08x"), d); break;
                        //0000 0110 1000 0110
                    case 0x85://�����
                        s = (short)(d >> 16);
                        data_receive_Mach = s * (4.096 / 32768);
                        data_difference_Mach.Format(_T("%08x"), d); break;
                        //    0000 0110 0001 0101
                    case 0x97://װ����ѹ
                        s = (short)(d >> 16);
                        data_receive_AirP = s * (128. / 32768);
                        data_difference_AirP.Format(_T("%08x"), d); break;
                        //0000 0110 1001 0111
                    case 0xA1://����
                        s = (short)(d >> 16);
                        data_receive_Attack = s * (45. / 32768);
                        data_difference_Attack.Format(_T("%08x"), d); break;
                        //0000 0110 1010 0001
                    case 0x84://�����ѹ�߶�
                        s = (short)(d >> 16);
                        data_receive_High = s;
                        data_difference_High.Format(_T("%08x"), d); break;
                        //0000 0110 1000 0100
                    case 0x8A://�����ٶ�
                        s = (short)(d >> 16);
                        data_receive_SpeedUD = s * (512. / 32768);
                        data_difference_SpeedUD.Format(_T("%08x"), d); break;
                        //0000 0110 1000 1010
                    case 0x32://�����
                        s = (short)(d >> 16);
                        data_receive_Azimuth = s * (360. / 32768);
                        data_difference_Azimuth.Format(_T("%08x"), d); break;
                        //0000 0110 0011 0010
                    case 0x33://������
                        s = (short)(d >> 16);
                        data_receive_Pitch = s * (180. / 32768);
                        data_difference_Pitch.Format(_T("%08x"), d); break;
                        //0000 0110 0011 0011
                    case 0x34://�����
                        s = (short)(d >> 16);
                        data_receive_Roll = s * (180. / 32768);
                        data_difference_Roll.Format(_T("%08x"), d); break;
                        //0000 0110 0011 0100
                    case 0x35://���ߵ�߶�
                        s = (short)(d >> 16);
                        data_receive_HighR = s * (1524. / 32768);
                        data_difference_HighR.Format(_T("%08x"), d); break;
                        //0000 0110 0011 0101
                    case 0x36://��Ͱ�ȫ�߶�
                        s = (short)(d >> 16);
                        data_receive_HighL = s * (1500. / 32768);
                        data_difference_HighL.Format(_T("%08x"), d); break;
                        //0000 0110 0011 0110 
                    case 0x37://�໬��
                        s = (short)(d >> 16);
                        data_receive_Sideslip = s * (10. / 32768);
                        data_difference_Sideslip.Format(_T("%08x"), d); break;
                        //0000 0110 0011 0111
                    case 0x38://�������
                        s = (short)(d >> 16);
                        data_receive_NormalOverload = s * (10. / 32768);
                        data_difference_NormalOverload.Format(_T("%08x"), d); break;
                        //0000 0110 0011 1000
                    default:
                        break;
                }
            }
            DisablReadFIFO(hCard);//��ֹ��FIFO����    
        }
    }
}
