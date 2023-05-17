//
// Created by sekiro on 5/12/23.
// used to check the correctness of encoding and decoding
//

#include "MainWindow.h"
#include <cstdio>
#include <cmath>

int main() {
    CMainWindow *mainWindow = new CMainWindow();

    // table head
    // index, input, coded, output, diff
    printf("%3s|%10s|%10s|%10s|%10s\n", "i", "input", "coded", "output", "diff");

    // Coding
    mainWindow->Coding();

    // Decoding
    for (int i = 0; i <= mainWindow->wdTxBufLen; i++) {
        mainWindow->DecodeThreadFunc(mainWindow->dwTxBuf, i, true);
    }

    // Pre-process
    double input[14] = {
            (double)mainWindow->data_send_RealSpeed,
            (double)mainWindow->data_send_Speed,
            mainWindow->data_send_Mach,
            mainWindow->data_send_AirP,
            mainWindow->data_send_Attack,
            (double)mainWindow->data_send_High,
            (double)mainWindow->data_send_SpeedUD,
            mainWindow->data_send_Azimuth,
            mainWindow->data_send_Pitch,
            mainWindow->data_send_Roll,
            (double)mainWindow->data_send_HighR,
            (double)mainWindow->data_send_HighL,
            mainWindow->data_send_Sideslip,
            mainWindow->data_send_NormalOverload
    };
    double output[14] = {
            (double)mainWindow->data_receive_RealSpeed,
            (double)mainWindow->data_receive_Speed,
            mainWindow->data_receive_Mach,
            mainWindow->data_receive_AirP,
            mainWindow->data_receive_Attack,
            (double)mainWindow->data_receive_High,
            (double)mainWindow->data_receive_SpeedUD,
            mainWindow->data_receive_Azimuth,
            mainWindow->data_receive_Pitch,
            mainWindow->data_receive_Roll,
            (double)mainWindow->data_receive_HighR,
            (double)mainWindow->data_receive_HighL,
            mainWindow->data_receive_Sideslip,
            mainWindow->data_receive_NormalOverload
    };

    double diff[14];
    for (int i = 0; i < 14; i++) {
        diff[i] = output[i] - input[i];
    }

    // Output
    printf("%3d|%10x|%10x|%10x|%10s\n", 0, mainWindow->m_ControlWord1, mainWindow->dwTxBuf[0], mainWindow->m_ControlWord1, "True");
    printf("%3d|%10x|%10x|%10x|%10s\n", 1, mainWindow->m_ControlWord2, mainWindow->dwTxBuf[1], mainWindow->m_ControlWord2, "True");
    for (int i = 0; i < 14; i++) {
        printf("%3d|%10.3f|%10x|%10.3f|%10.3f(%.4f\%)\n", i + 2, input[i], mainWindow->dwTxBuf[i + 2], output[i], diff[i],
               abs(diff[i])/input[i]);
    }

    return 0;
}
