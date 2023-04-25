#include "coding.h"
#include <assert.h>
#include "ARNIC429Dlg.h"

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

void CARNIC429Dlg::Coding() {
    wdTxBufLen=0;
	
    // ������ 1��2
    dwTxBuf[wdTxBufLen] = m_ControlWord1;
	dwTxBuf[++wdTxBufLen] = m_ControlWord2;
	
    // �����
    // ��ΧΪ 0 ~ 4096, �ֱ���Ϊ (4096/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Air_Speed_Real_Mask;
    DWORD speed_real = (DWORD)(s_Air_Speed_Real/(4096.0/32768));
    set_value_parity(speed_real);
	
    // ָʾ����
    // ��ΧΪ 0 ~ 2048, �ֱ���Ϊ (2048/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Air_Speed_Mask;
    DWORD speed = (DWORD)(s_Air_Speed/(2048.0/32768));
    set_value_parity(speed);
	
	// �����
    // ��ΧΪ 0 ~ 4.096, �ֱ���Ϊ (4.096/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Ma_Mask;
    // �����������
    s_Air_Ma = s_Air_Speed/(3.6/340);
    DWORD ma = (DWORD)(s_Air_Ma/(4.096/32768));
    set_value_parity(ma);

	// װ����ѹ
    // ��ΧΪ -128 ~ 128, �ֱ���Ϊ (128/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | AirP_Mask;
    DWORD airP = (DWORD)(s_Air_AirP/(128.0/32768));
    set_value_parity(airP);


    // ����
    // ��ΧΪ -45 ~ 45, �ֱ���Ϊ (45/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Attack_Mask;
    DWORD attack = (DWORD)(s_Air_Attack/(45.0/32768));
	set_value_parity(attack);

	// �����ѹ�߶�
    // ��ΧΪ 0 ~ 32768, �ֱ���Ϊ 1
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | High_Mask;
    DWORD attack = (DWORD)(s_Air_Attack);
    set_value_parity(attack);

	// �����ٶ�
    // ��ΧΪ -512 ~ 512, �ֱ���Ϊ (512/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | SpeedUD_Mask;
    DWORD speedUD = (DWORD)(s_Air_SpeedUD/(512.0/32768));
    set_value_parity(speedUD);
	
	// ����
    // ��ΧΪ 0 ~ 360, �ֱ���Ϊ (360/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Azimuth_Mask;
    DWORD azimuth = (DWORD)(s_Air_Azimuth/(360.0/32768));
    set_value_parity(azimuth);


    // ������
    // ��ΧΪ -180 ~ 180, �ֱ���Ϊ (180/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Pitch_Mask;
    DWORD pitch = (DWORD)(s_Air_Pitch/(180.0/32768));
	set_value_parity(pitch);


    // �����
    // ��ΧΪ -180 ~ 180, �ֱ���Ϊ (180/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Roll_Mask;
    DWORD roll = (DWORD)(s_Air_Roll/(180.0/32768));
	set_value_parity(roll);
	
    // ���ߵ�߶�
    // ��ΧΪ 0 ~ 1524, �ֱ���Ϊ (1524/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | HighR_Mask;
    DWORD highR = (DWORD)(s_Air_HighR/(1524.0/32768));
	set_value_parity(highR);

    // ��Ͱ�ȫ�߶�
    // ��ΧΪ 0 ~ 1500, �ֱ���Ϊ (1500/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | HighL_Mask;
    DWORD highL = (DWORD)(s_Air_HighL/(1500.0/32768));
	set_value_parity(highL);

    // �໬��
    // ��ΧΪ -10 ~ 10, �ֱ���Ϊ (10/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Sideslip_Mask;
    DWORD sideslip = (DWORD)(s_Air_Sideslip/(10.0/32768));
	set_value_parity(sideslip);

    // �������
    // ��ΧΪ -10 ~ 10, �ֱ���Ϊ (10/32768)
    // 14 λΪ LSB��29 λΪ MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | N_Mask;
    DWORD n = (DWORD)(s_Air_N/(10.0/32768));
	set_value_parity(n);
}

void CARNIC429Dlg::Decoding()
{
	
}
