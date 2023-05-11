#include "stdafx.h"
#include "ARNIC429.h"
#include "MainWindow.h"

#include "coding.h"
#include <assert.h>

// in main window
extern CMainWindow* mother_window;

// static UINT cal_parity(DWORD a) {
//     UINT res = 0;
//     while (a > 0) {
//         res ^= (a % 2);
//         a /= 2;
//     }
//     assert(res == 0 || res == 1);
//     return res;
// }

// static void set_value_parity(DWORD value) {
//     for (int i = 14; i <= 29; i++) {
//         mother_window->dwTxBuf[mother_window->wdTxBufLen] |= (value % 2) << (32 - i);
//         value /= 2;
//     }
//     // 计算奇偶校验
//     mother_window->dwTxBuf[mother_window->wdTxBufLen] |= cal_parity(mother_window->dwTxBuf[mother_window->wdTxBufLen]);
// }

// static DWORD check_value(char *name, DWORD value, DWORD mask, bool check_parity) {
//     // 赋 value 14 位到 29 位为 0
//     // 检查和标识号是否相同
//     DWORD ident = value & ~0x0007fff8;
//     if (ident != mask) {
//         char tmp[100];
//         strcpy(tmp, name);
//         strcat(tmp, " has wrong ident");
//         perror(tmp);
//     }

//     // 检查奇偶校验是否正确
//     UINT parity = cal_parity(value);
//     if (parity != 0) {
//         char tmp[100];
//         strcpy(tmp, name);
//         strcat(tmp, " has wrong parity");
//         perror(tmp);
//     }

//     // 返回解码得到的值
//     value &= 0x0007fff8;
//     return value;
// }

void CMainWindow::Coding()
{
    wdTxBufLen=0;
    dwTxBuf[wdTxBufLen] = m_ControlWord1;
    dwTxBuf[++wdTxBufLen] = m_ControlWord2;

    dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_RealSpeed/(4096.0/32768));
    dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000688;

    dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_Speed/(2048.0/32768));
    dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000686;

    data_send_Mach = data_send_Speed/3.6/340;//????????????
    dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_Mach/(4.096/32768));
    dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000685;

    {
        dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_AirP/(128.0/32768));
        dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000697;
    }

    {
        dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_Attack/(45.0/32768));
        dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x000006a1;
    }

    dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_High);
    dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000684;

    dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_SpeedUD/(512.0/32768));
    dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x0000068a;

    dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_Azimuth/(360.0/32768));
    dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000632;

    {
        dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_Pitch/(180.0/32768));
        dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000633;
    }

    {
        dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_Roll/(180.0/32768));
        dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000634;
    }

    dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_HighR/(1524.0/32768));
    dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000635;

    dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_HighL/(1500.0/32768));
    dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000636;

    {
        dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_Sideslip/(10.0/32768));
        dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000637;
    }

    {
        dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_NormalOverload/(10.0/32768));
        dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000638;
    }

}

// void CMainWindow::Coding() {
//     mother_window->wdTxBufLen = 0;
    
//     // 控制字 1、2
//     mother_window->dwTxBuf[mother_window->wdTxBufLen] = mother_window->m_ControlWord1;
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = mother_window->m_ControlWord2;
    
//     // 真空速
//     // 范围为 0 ~ 4096, 分辨率为 (4096/32768)
//     // 14 位为 LSB，29 位为 MSB
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = 0x00000000 | Air_RealSpeed_Mask;
//     DWORD speed_real = (DWORD)(mother_window->data_send_RealSpeed / (4096.0/32768));
//     set_value_parity(speed_real);
    
//     // 指示空速
//     // 范围为 0 ~ 2048, 分辨率为 (2048/32768)
//     // 14 位为 LSB，29 位为 MSB
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = 0x00000000 | Air_Speed_Mask;
//     DWORD speed = (DWORD)(mother_window->data_send_Speed / (2048.0/32768));
//     set_value_parity(speed);
    
//     // 马赫数
//     // 范围为 0 ~ 4.096, 分辨率为 (4.096/32768)
//     // 14 位为 LSB，29 位为 MSB
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = 0x00000000 | Ma_Mask;
//     // 计算其马赫数
//     mother_window->data_send_Mach = mother_window->data_send_Speed / (3.6/340);
//     DWORD ma = (DWORD)(mother_window->data_send_Mach / (4.096/32768));
//     set_value_parity(ma);

//     // 装订气压
//     // 范围为 -128 ~ 128, 分辨率为 (128/32768)
//     // 14 位为 LSB，29 位为 MSB
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = 0x00000000 | AirP_Mask;
//     DWORD airP = (DWORD)(mother_window->data_send_AirP / (128.0/32768));
//     set_value_parity(airP);

//     // 攻角
//     // 范围为 -45 ~ 45, 分辨率为 (45/32768)
//     // 14 位为 LSB，29 位为 MSB
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = 0x00000000 | Attack_Mask;
//     DWORD attack = (DWORD)(mother_window->data_send_Attack / (45.0/32768));
//     set_value_parity(attack);

//     // 相对气压高度
//     // 范围为 0 ~ 32768, 分辨率为 1
//     // 14 位为 LSB，29 位为 MSB
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = 0x00000000 | High_Mask;
//     DWORD high = (DWORD)(mother_window->data_send_High);
//     set_value_parity(high);

//     // 升降速度
//     // 范围为 -512 ~ 512, 分辨率为 (512/32768)
//     // 14 位为 LSB，29 位为 MSB
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = 0x00000000 | SpeedUD_Mask;
//     DWORD speedUD = (DWORD)(mother_window->data_send_SpeedUD / (512.0/32768));
//     set_value_parity(speedUD);
    
//     // 航向
//     // 范围为 0 ~ 360, 分辨率为 (360/32768)
//     // 14 位为 LSB，29 位为 MSB
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = 0x00000000 | Azimuth_Mask;
//     DWORD azimuth = (DWORD)(mother_window->data_send_Azimuth / (360.0/32768));
//     set_value_parity(azimuth);

//     // 俯仰角
//     // 范围为 -180 ~ 180, 分辨率为 (180/32768)
//     // 14 位为 LSB，29 位为 MSB
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = 0x00000000 | Pitch_Mask;
//     DWORD pitch = (DWORD)(mother_window->data_send_Pitch / (180.0/32768));
//     set_value_parity(pitch);

//     // 横滚角
//     // 范围为 -180 ~ 180, 分辨率为 (180/32768)
//     // 14 位为 LSB，29 位为 MSB
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = 0x00000000 | Roll_Mask;
//     DWORD roll = (DWORD)(mother_window->data_send_Roll / (180.0/32768));
//     set_value_parity(roll);
    
//     // 无线电高度
//     // 范围为 0 ~ 1524, 分辨率为 (1524/32768)
//     // 14 位为 LSB，29 位为 MSB
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = 0x00000000 | HighR_Mask;
//     DWORD highR = (DWORD)(mother_window->data_send_HighR / (1524.0/32768));
//     set_value_parity(highR);

//     // 最低安全高度
//     // 范围为 0 ~ 1500, 分辨率为 (1500/32768)
//     // 14 位为 LSB，29 位为 MSB
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = 0x00000000 | HighL_Mask;
//     DWORD highL = (DWORD)(mother_window->data_send_HighL / (1500.0/32768));
//     set_value_parity(highL);

//     // 侧滑角
//     // 范围为 -10 ~ 10, 分辨率为 (10/32768)
//     // 14 位为 LSB，29 位为 MSB
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = 0x00000000 | Sideslip_Mask;
//     DWORD sideslip = (DWORD)(mother_window->data_send_Sideslip / (10.0/32768));
//     set_value_parity(sideslip);

//     // 法向过载
//     // 范围为 -10 ~ 10, 分辨率为 (10/32768)
//     // 14 位为 LSB，29 位为 MSB
//     mother_window->dwTxBuf[++mother_window->wdTxBufLen] = 0x00000000 | N_Mask;
//     DWORD n = (DWORD)(mother_window->data_send_NormalOverload /( 10.0/32768));
//     set_value_parity(n);
// }

// void CMainWindow::Decoding(LPVOID lpParam) {
//     HWND hwnd = (HWND)lpParam;
//     DWORD d = 0;
//     int i = 0;
//     // ?
//     BYTE chno = 0;
//     BYTE btTriggerLevel = 0;

//     while (mother_window->keep_receive) {
//         // Get Triger Level
//         btTriggerLevel = mother_window->stTriggerLevel.Chan0Depth_I;

//         // Rx channel 1 ~ chno_RMAX
//         // 进行过滤
//         if (btTriggerLevel > 0) {
//             if (IsFIFOTriggered_R(mother_window->hCard, chno)) {
//                 // 使能读 FIFO 数据
//                 EnablReadFIFO(mother_window->hCard, chno);
//                 // 如果读到数据
//                 while ((ReadFIFOStatus_R(mother_window->hCard, chno) != FIFOEmpty) &&
//                 (ReadFIFOStatus_R(mother_window->hCard, chno) != FIFOError)) {
//                     d = ReceiveData(mother_window->hCard, chno);
//                     if ((mother_window->wdMode == C429_SELFTEST) && (mother_window->stComm[chno / 2].iSelParity == C429_PARITY_NONE)) {
//                         d = Resume429Word(d);
//                     }
//                     Save_ReceiveData(d, ReceiveData_Vector + i);
//                 }
//                 // 关闭读 FIFO 数据
//                 DisablReadFIFO(mother_window->hCard);
//             }
//         } 
//         // 不进行过滤
//         else {
//             // 当 recieveFIFO 不空且不溢出时
//             if ((ReadFIFOStatus_R(mother_window->hCard, chno) != FIFOEmpty) && (ReadFIFOStatus_R(mother_window->hCard, chno) != FIFOError))
//             {
//                 // 使能读 FIFO 数据
//                 EnablReadFIFO(mother_window->hCard, chno);
//                 d = ReceiveData(mother_window->hCard, chno);
//                 if ((mother_window->wdMode == C429_SELFTEST) && (mother_window->stComm[chno / 2].iSelParity == C429_PARITY_NONE)) // resume 429 Word
//                 {
//                     d = Resume429Word(d);
//                 }
//                 DWORD temp;  
//                 temp = d >> 24;
//                 short s;
//                 // 根据标识符判断是哪个变量
//                 switch (temp)
//                 {
//                     case 0x30://控制字1
//                         mother_window->data_ControlWord1.Format(_T("%08x"), d); break;
//                         //0000 0110 0011 0000
//                     case 0x31://控制字2
//                         mother_window->data_ControlWord2.Format(_T("%08x"), d); break;
//                         //0000 0110 0011 0001
                    
//                     case 0x88:    //真空速
//                         s = (short)(d >> 16);
//                         mother_window->data_receive_RealSpeed = s * (4096. / 32768);
//                         mother_window->data_difference_RealSpeed.Format(_T("%08x"), d); break;
//                         //0000 0110 1000 1000
//                     case 0x86://指示空速
//                         s = (short)(d >> 16);
//                         mother_window->data_receive_Speed = s * (2048. / 32768);
//                         mother_window->data_difference_Speed.Format(_T("%08x"), d); break;
//                         //0000 0110 1000 0110
//                     case 0x85://马赫数
//                         s = (short)(d >> 16);
//                         mother_window->data_receive_Mach = s * (4.096 / 32768);
//                         mother_window->data_difference_Mach.Format(_T("%08x"), d); break;
//                         //    0000 0110 0001 0101
//                     case 0x97://装订气压
//                         s = (short)(d >> 16);
//                         mother_window->data_receive_AirP = s * (128. / 32768);
//                         mother_window->data_difference_AirP.Format(_T("%08x"), d); break;
//                         //0000 0110 1001 0111
//                     case 0xA1://攻角
//                         s = (short)(d >> 16);
//                         mother_window->data_receive_Attack = s * (45. / 32768);
//                         mother_window->data_difference_Attack.Format(_T("%08x"), d); break;
//                         //0000 0110 1010 0001
//                     case 0x84://相对气压高度
//                         s = (short)(d >> 16);
//                         mother_window->data_receive_High = s;
//                         mother_window->data_difference_High.Format(_T("%08x"), d); break;
//                         //0000 0110 1000 0100
//                     case 0x8A://升降速度
//                         s = (short)(d >> 16);
//                         mother_window->data_receive_SpeedUD = s * (512. / 32768);
//                         mother_window->data_difference_SpeedUD.Format(_T("%08x"), d); break;
//                         //0000 0110 1000 1010
//                     case 0x32://航向角
//                         s = (short)(d >> 16);
//                         mother_window->data_receive_Azimuth = s * (360. / 32768);
//                         mother_window->data_difference_Azimuth.Format(_T("%08x"), d); break;
//                         //0000 0110 0011 0010
//                     case 0x33://俯仰角
//                         s = (short)(d >> 16);
//                         mother_window->data_receive_Pitch = s * (180. / 32768);
//                         mother_window->data_difference_Pitch.Format(_T("%08x"), d); break;
//                         //0000 0110 0011 0011
//                     case 0x34://横滚角
//                         s = (short)(d >> 16);
//                         mother_window->data_receive_Roll = s * (180. / 32768);
//                         mother_window->data_difference_Roll.Format(_T("%08x"), d); break;
//                         //0000 0110 0011 0100
//                     case 0x35://无线电高度
//                         s = (short)(d >> 16);
//                         mother_window->data_receive_HighR = s * (1524. / 32768);
//                         mother_window->data_difference_HighR.Format(_T("%08x"), d); break;
//                         //0000 0110 0011 0101
//                     case 0x36://最低安全高度
//                         s = (short)(d >> 16);
//                         mother_window->data_receive_HighL = s * (1500. / 32768);
//                         mother_window->data_difference_HighL.Format(_T("%08x"), d); break;
//                         //0000 0110 0011 0110 
//                     case 0x37://侧滑角
//                         s = (short)(d >> 16);
//                         mother_window->data_receive_Sideslip = s * (10. / 32768);
//                         mother_window->data_difference_Sideslip.Format(_T("%08x"), d); break;
//                         //0000 0110 0011 0111
//                     case 0x38://法向过载
//                         s = (short)(d >> 16);
//                         mother_window->data_receive_NormalOverload = s * (10. / 32768);
//                         mother_window->data_difference_NormalOverload.Format(_T("%08x"), d); break;
//                         //0000 0110 0011 1000
//                     default:
//                         break;
//                 }
//             }
//             DisablReadFIFO(mother_window->hCard);//禁止读FIFO数据    
//         }
//     }
// }
