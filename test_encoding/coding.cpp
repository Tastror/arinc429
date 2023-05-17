//
// Created by sekiro on 5/12/23.
//

#include "coding.h"
#include <cstdio>
#include <cassert>
#include "MainWindow.h"

// in main window
CMainWindow *mother_window = NULL;

static DWORD cal_parity(DWORD a) {
    DWORD res = 0;
    while (a > 0) {
        res ^= (a % 2);
        a /= 2;
    }
    assert(res == 0 || res == 1);
    return res;
}

void CMainWindow::set_value_parity(DWORD value, bool is_odd) {
    for (int i = 14; i <= 29; i++) {
        dwTxBuf[wdTxBufLen] |= (value % 2) << (32 - i);
        value /= 2;
    }

    DWORD parity = cal_parity(dwTxBuf[wdTxBufLen]);
    if (is_odd) {
        parity ^= 1;
    }
    dwTxBuf[wdTxBufLen] |= parity;
}

static DWORD check_value(const char *name, DWORD value, DWORD mask, bool check_parity) {

    DWORD ident = value & ~0x0007fff8;
    if (ident != mask) {
        char tmp[100];
    }


    DWORD parity = cal_parity(value);
    if (parity != 0) {
        char tmp[100];
    }


    value &= 0x0007fff8;
    return value;
}

CMainWindow::CMainWindow() {
    mother_window = this;
    data_send_RealSpeed = 1231;
    data_send_Speed = 1234;
    data_send_AirP = 3.1;
    data_send_Attack = 44.72;
    data_send_Pitch = 64.25;
    data_send_Roll = 178.90;
    data_send_Sideslip = 9.94;
    data_send_High = 157;
    data_send_HighR = 155;
    data_send_HighL = 300;
    data_send_SpeedUD = 31;
    data_send_Azimuth = 15.5;
    data_send_NormalOverload = 3.1;
    m_ControlWord1 = 0x30000006;
    m_ControlWord2 = 0x31000006;
}

void CMainWindow::Coding() {
    wdTxBufLen = 0;

    // 0x30 & 0x31, Control word
    dwTxBuf[wdTxBufLen] = m_ControlWord1 & ControlWord1_Mask;
    dwTxBuf[++wdTxBufLen] = m_ControlWord2 & ControlWord2_Mask;

    // 0x88, Real air speed
    dwTxBuf[++wdTxBufLen] = 0xffffffff & Air_RealSpeed_Mask;
    DWORD speed_real;
    assert(data_send_RealSpeed >= 0 && data_send_RealSpeed <= 4096);
    speed_real = (DWORD)(data_send_RealSpeed / (4096.0 / 32768));
    set_value_parity(speed_real);

    // 0x86, Speed
    dwTxBuf[++wdTxBufLen] = 0xffffffff & Air_Speed_Mask;
    DWORD speed;
    assert(data_send_Speed >= 0 && data_send_Speed <= 2048);
    speed = (DWORD) (data_send_Speed / (2048.0 / 32768));
    set_value_parity(speed);

    // 0x85, Mach
    dwTxBuf[++wdTxBufLen] = 0xffffffff & Ma_Mask;
    data_send_Mach = data_send_Speed / 3.6 / 340;
    DWORD ma;
    assert(data_send_Mach >= 0 && data_send_Mach <= 4.096);
    ma = (DWORD)(data_send_Mach / (4.096 / 32768));
    set_value_parity(ma);

    // 0x97, Air pressure
    dwTxBuf[++wdTxBufLen] = 0xffffffff & AirP_Mask;
    DWORD airP;
    assert(data_send_AirP >= -128 && data_send_AirP <= 128);
    airP = (DWORD)((data_send_AirP + 128) / (2 * 128.0 / 32768));
    set_value_parity(airP);

    // 0xa1, Attack angle
    dwTxBuf[++wdTxBufLen] = 0xffffffff & Attack_Mask;
    assert(data_send_Attack >= -45 && data_send_Attack <= 45);
    DWORD attack;
    attack = (DWORD)((data_send_Attack + 45) / (2 * 45.0 / 32768));
    set_value_parity(attack);

    // 0x84, Height relevant
    dwTxBuf[++wdTxBufLen] = 0xffffffff & High_Mask;
    assert(data_send_High >= 0 && data_send_High <= 32768);
    DWORD high;
    high = (DWORD)(data_send_High);
    set_value_parity(high);

    // 0x8a, Speed up and down
    dwTxBuf[++wdTxBufLen] = 0xffffffff & SpeedUD_Mask;
    assert(data_send_SpeedUD >= -512 && data_send_SpeedUD <= 512);
    DWORD speedUD;
    speedUD = (DWORD)((data_send_SpeedUD + 512) / (2 * 512.0 / 32768));
    set_value_parity(speedUD);

    // 0x32, Azimuth
    dwTxBuf[++wdTxBufLen] = 0xffffffff & Azimuth_Mask;
    assert(data_send_Azimuth >= 0 && data_send_Azimuth <= 360);
    DWORD azimuth;
    azimuth = (DWORD)(data_send_Azimuth / (360.0 / 32768));
    set_value_parity(azimuth);

    // 0x33, Pitch
    dwTxBuf[++wdTxBufLen] = 0xffffffff & Pitch_Mask;
    assert(data_send_Pitch >= -180 && data_send_Pitch <= 180);
    DWORD pitch;
    pitch = (DWORD)((data_send_Pitch + 180) / (2 * 180.0 / 32768));
    set_value_parity(pitch);

    // 0x34, Roll
    dwTxBuf[++wdTxBufLen] = 0xffffffff & Roll_Mask;
    assert(data_send_Roll >= -180 && data_send_Roll <= 180);
    DWORD roll;
    roll = (DWORD)((data_send_Roll + 180) / (2 * 180.0 / 32768));
    set_value_parity(roll);

    // 0x35, Height remote
    dwTxBuf[++wdTxBufLen] = 0xffffffff & HighR_Mask;
    assert(data_send_HighR >= 0 && data_send_HighR <= 1524);
    DWORD highR;
    highR = (DWORD)(data_send_HighR / (1524.0 / 32768));
    set_value_parity(highR);

    // 0x36, Height least
    dwTxBuf[++wdTxBufLen] = 0xffffffff & HighL_Mask;
    assert(data_send_HighL >= 0 && data_send_HighL <= 1500);
    DWORD highL;
    highL = (DWORD)(data_send_HighL / (1500.0 / 32768));
    set_value_parity(highL);

    // 0x37, Side slip
    dwTxBuf[++wdTxBufLen] = 0xffffffff & Sideslip_Mask;
    assert(data_send_Sideslip >= -10 && data_send_Sideslip <= 10);
    DWORD sideslip;
    sideslip = (DWORD)((data_send_Sideslip + 10) / (2 * 10.0 / 32768));
    set_value_parity(sideslip);

    // 0x38, Normal overload
    dwTxBuf[++wdTxBufLen] = 0xffffffff & N_Mask;
    assert(data_send_NormalOverload >= -10 && data_send_NormalOverload <= 10);
    DWORD n;
    n = (DWORD)((data_send_NormalOverload + 10) / (2 * 10.0 / 32768));
    set_value_parity(n);
}

static DWORD getDataFromDWORD(DWORD a) {
    DWORD res = 0;
    a >>= (32 - 29);
    for (int i = 29; i >= 14; i--) {
        res |= (a % 2) << (i - 14);
        a /= 2;
    }
    return res;
}

/*++
	Routine Description:
		Thread function used to read six channels counter and two AD's sampling data.

	Arguments:
		1) lpParam: [IN/OUT] needed parameter for thread.

	Return Value:
		If the function is seceeded, return value is TRUE else is FALSE;
--*/
DWORD CMainWindow::DecodeThreadFunc(const DWORD recv_buf[], int index, bool is_odd) {
    // in REAL case, d = ReceiveData(mother_window->hCard, chno);
    DWORD d = recv_buf[index];

    // get id and data
    DWORD id = d >> 24;
    DWORD mid = getDataFromDWORD(d);
    double data = mid / 32768.0;

    if (id != ControlWord1_ID && id != ControlWord2_ID) {
        // check parity
        DWORD parity = cal_parity(d);
        if ((is_odd && parity != 1) || (!is_odd && parity != 0)) {
            perror("parity check failed\n");
        }
    }

    // switch id, control word or data
    switch (id) {
        // if control word, decide if equal
        case ControlWord1_ID:
            if (d != ControlWord1_Mask) {
                perror("control world 1 check failed\n");
            }
            break;
        case ControlWord2_ID:
            if (d != ControlWord2_Mask) {
                perror("control world 2 check failed\n");
            }
            break;
        // if data, get data
        case Air_RealSpeed_ID:
            mother_window->data_receive_RealSpeed = data * 4096;
            break;
        case Air_Speed_ID:
            mother_window->data_receive_Speed = data * 2048;
            break;
        case Ma_ID:
            mother_window->data_receive_Mach = data * 4.096;
            break;
        case AirP_ID:
            mother_window->data_receive_AirP = data * 2 * 128 - 128;
            break;
        case Attack_ID:
            mother_window->data_receive_Attack = data * 2 * 45 - 45;
            break;
        case High_ID:
            mother_window->data_receive_High = data * 32768;
            break;
        case SpeedUD_ID:
            mother_window->data_receive_SpeedUD = data * 2 * 512 - 512;
            break;
        case Azimuth_ID:
            mother_window->data_receive_Azimuth = data * 360;
            break;
        case Pitch_ID:
            mother_window->data_receive_Pitch = data * 2 * 180 - 180;
            break;
        case Roll_ID:
            mother_window->data_receive_Roll = data * 2 * 180 - 180;
            break;
        case HighR_ID:
            mother_window->data_receive_HighR = data * 1524;
            break;
        case HighL_ID:
            mother_window->data_receive_HighL = data * 1500;
            break;
        case Sideslip_ID:
            mother_window->data_receive_Sideslip = data * 2 * 10 - 10;
            break;
        case N_ID:
            mother_window->data_receive_NormalOverload = data * 2 * 10 - 10;
            break;
        default:
            perror("unrecognized data type\n");
    }

    return 0;
}
