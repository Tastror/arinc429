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
    // 计算奇偶校验
    dwTxBuf[wdTxBufLen] |= cal_parity(dwTxBuf[wdTxBufLen]);
}

static DWORD check_value(char *name, DWORD value, DWORD mask, bool check_parity) {
    // 赋 value 14 位到 29 位为 0
    // 检查和标识号是否相同
    DWORD ident = value & ~0x0007fff8;
    if (ident != mask) {
        char tmp[100];
        strcpy(tmp, name);
        strcat(tmp, " has wrong ident");
        perror(tmp);
    }

    // 检查奇偶校验是否正确
    UINT parity = cal_parity(value);
    if (parity != 0) {
        char tmp[100];
        strcpy(tmp, name);
        strcat(tmp, " has wrong parity");
        perror(tmp);
    }

    // 返回解码得到的值
    value &= 0x0007fff8;
    return value;
}

void CARNIC429Dlg::Coding() {
    wdTxBufLen=0;
	
    // 控制字 1、2
    dwTxBuf[wdTxBufLen] = m_ControlWord1;
	dwTxBuf[++wdTxBufLen] = m_ControlWord2;
	
    // 真空速
    // 范围为 0 ~ 4096, 分辨率为 (4096/32768)
    // 14 位为 LSB，29 位为 MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Air_Speed_Real_Mask;
    DWORD speed_real = (DWORD)(s_Air_Speed_Real/(4096.0/32768));
    set_value_parity(speed_real);
	
    // 指示空速
    // 范围为 0 ~ 2048, 分辨率为 (2048/32768)
    // 14 位为 LSB，29 位为 MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Air_Speed_Mask;
    DWORD speed = (DWORD)(s_Air_Speed/(2048.0/32768));
    set_value_parity(speed);
	
	// 马赫数
    // 范围为 0 ~ 4.096, 分辨率为 (4.096/32768)
    // 14 位为 LSB，29 位为 MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Ma_Mask;
    // 计算其马赫数
    s_Air_Ma = s_Air_Speed/(3.6/340);
    DWORD ma = (DWORD)(s_Air_Ma/(4.096/32768));
    set_value_parity(ma);

	// 装订气压
    // 范围为 -128 ~ 128, 分辨率为 (128/32768)
    // 14 位为 LSB，29 位为 MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | AirP_Mask;
    DWORD airP = (DWORD)(s_Air_AirP/(128.0/32768));
    set_value_parity(airP);


    // 攻角
    // 范围为 -45 ~ 45, 分辨率为 (45/32768)
    // 14 位为 LSB，29 位为 MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Attack_Mask;
    DWORD attack = (DWORD)(s_Air_Attack/(45.0/32768));
	set_value_parity(attack);

	// 相对气压高度
    // 范围为 0 ~ 32768, 分辨率为 1
    // 14 位为 LSB，29 位为 MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | High_Mask;
    DWORD attack = (DWORD)(s_Air_Attack);
    set_value_parity(attack);

	// 升降速度
    // 范围为 -512 ~ 512, 分辨率为 (512/32768)
    // 14 位为 LSB，29 位为 MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | SpeedUD_Mask;
    DWORD speedUD = (DWORD)(s_Air_SpeedUD/(512.0/32768));
    set_value_parity(speedUD);
	
	// 航向
    // 范围为 0 ~ 360, 分辨率为 (360/32768)
    // 14 位为 LSB，29 位为 MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Azimuth_Mask;
    DWORD azimuth = (DWORD)(s_Air_Azimuth/(360.0/32768));
    set_value_parity(azimuth);


    // 俯仰角
    // 范围为 -180 ~ 180, 分辨率为 (180/32768)
    // 14 位为 LSB，29 位为 MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Pitch_Mask;
    DWORD pitch = (DWORD)(s_Air_Pitch/(180.0/32768));
	set_value_parity(pitch);


    // 横滚角
    // 范围为 -180 ~ 180, 分辨率为 (180/32768)
    // 14 位为 LSB，29 位为 MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Roll_Mask;
    DWORD roll = (DWORD)(s_Air_Roll/(180.0/32768));
	set_value_parity(roll);
	
    // 无线电高度
    // 范围为 0 ~ 1524, 分辨率为 (1524/32768)
    // 14 位为 LSB，29 位为 MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | HighR_Mask;
    DWORD highR = (DWORD)(s_Air_HighR/(1524.0/32768));
	set_value_parity(highR);

    // 最低安全高度
    // 范围为 0 ~ 1500, 分辨率为 (1500/32768)
    // 14 位为 LSB，29 位为 MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | HighL_Mask;
    DWORD highL = (DWORD)(s_Air_HighL/(1500.0/32768));
	set_value_parity(highL);

    // 侧滑角
    // 范围为 -10 ~ 10, 分辨率为 (10/32768)
    // 14 位为 LSB，29 位为 MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | Sideslip_Mask;
    DWORD sideslip = (DWORD)(s_Air_Sideslip/(10.0/32768));
	set_value_parity(sideslip);

    // 法向过载
    // 范围为 -10 ~ 10, 分辨率为 (10/32768)
    // 14 位为 LSB，29 位为 MSB
    dwTxBuf[++wdTxBufLen] = 0x00000000 | N_Mask;
    DWORD n = (DWORD)(s_Air_N/(10.0/32768));
	set_value_parity(n);
}

void CARNIC429Dlg::Decoding()
{
	
}
