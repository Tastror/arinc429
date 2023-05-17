//
// Created by sekiro on 5/12/23.
// A non-meaning class MainWindow, for simulating
//

#ifndef TEST_ENCODING_MAINWINDOW_H
#define TEST_ENCODING_MAINWINDOW_H

#include <cstdint>

#define FIFO_TMAX 127

typedef uint32_t DWORD;
typedef uint16_t WORD;
typedef uint8_t BYTE;

class CMainWindow {
public:
    CMainWindow();
    void Coding();
    void set_value_parity(DWORD value, bool is_idd=true);
    DWORD DecodeThreadFunc(const DWORD recv_buf[], int index, bool is_odd=true);

    DWORD dwTxBuf[FIFO_TMAX];
    WORD wdTxBufLen;

    // input of encoder
    int data_send_RealSpeed;        //
    int data_send_Speed;            //
    float data_send_Roll;           //
    float data_send_Pitch;          //
    int data_send_High;             //
    float data_send_Azimuth;        //
    float data_send_Sideslip;       //
    float data_send_Mach;           //
    float data_send_AirP;           //
    float data_send_Attack;         //
    int data_send_SpeedUD;          //
    int data_send_HighR;            //
    int data_send_HighL;            //
    float data_send_NormalOverload; //

    // output of decoder
    int data_receive_RealSpeed;
    int data_receive_Speed;
    float data_receive_Roll;
    float data_receive_Pitch;
    int data_receive_High;
    float data_receive_Azimuth;
    float data_receive_Sideslip;
    float data_receive_Mach;
    float data_receive_AirP;
    float data_receive_Attack;
    int data_receive_SpeedUD;
    int data_receive_HighR;
    int data_receive_HighL;
    float data_receive_NormalOverload;

    // for both
    DWORD m_ControlWord1;
    DWORD m_ControlWord2;


};

#endif //TEST_ENCODING_MAINWINDOW_H
