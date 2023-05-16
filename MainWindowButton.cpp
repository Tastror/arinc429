#include "stdafx.h"
#include "ARNIC429.h"
#include "MainWindow.h"

#include "math.h"

#include "DevelopWindow.h"
#include "MoreWindow.h"

void CMainWindow::OnCheck_Control1()
{

    if (!CWord_flg1)
    {
        data_ControlWord1 = 0x00000630;
        CWord_flg1 = TRUE;
    }
    else
    {
        data_ControlWord1 = 0;
        string_ControlWord1.Format("%01x", 0);
        CWord_flg1 = FALSE;
    }
    UpdateData(FALSE);
}

void CMainWindow::OnCheck_Control2()
{

    if (!CWord_flg2)
    {
        data_ControlWord2 = 0x00000631;
        CWord_flg2 = TRUE;
    }
    else
    {
        data_ControlWord2 = 0;
        string_ControlWord2.Format("%01x", 0);
        CWord_flg2 = FALSE;
    }
    UpdateData(FALSE);
}

///////////////////////////////收发按钮///////////////////////////////////////////////
void CMainWindow::OnButton_Send() // 发送
{
    // TODO: Add your control notification handler code here
    UpdateData(true); // 读取
    Sleep(20);
    Send();
    Sleep(20);
    UpdateData(FALSE); // 显示
}

void CMainWindow::OnButton_Receive() // 一直接收
{
    // TODO: Add your control notification handler code here
    if (blRxNow)
    {
        if (hThread != NULL)
        {
            isNeedThread = FALSE;
            //  wait thread to terminated
            //
            {
                DWORD dwRet;
                do
                {
                    dwRet = ::MsgWaitForMultipleObjects(1, &hThread, FALSE, INFINITE, QS_ALLINPUT);
                    if (dwRet != WAIT_OBJECT_0)
                    {
                        {
                            MSG msg;
                            while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
                            {
                                TranslateMessage(&msg);
                                DispatchMessage(&msg);
                            }
                        }
                    }
                } while ((dwRet != WAIT_OBJECT_0) && (dwRet != WAIT_FAILED));
            }
            ::CloseHandle(hThread);
            hThread = NULL;
        }
        this->button_Receive.SetWindowText(TEXT("开始接收"));
        blRxNow = FALSE;
        // KillTimer(3); // this is send timer, do not need to kill
        KillTimer(2);
    }
    else
    {
        // create thread to receive data
        //
        isNeedThread = TRUE;
        hThread = ::CreateThread(NULL,          // no security attributes
                                 0,             // use default stack size
                                 DecodeThreadFunc,    // thread function
                                 (LPVOID)ghWnd, // argument to thread function
                                 0,             // CREATE_SUSPENDED,            // use default creation flags
                                 &dwThreadId);  // returns the thread identifier
        // AfxBeginThread(DecodeThreadFunc, 0, 0, 0, NULL);
        if (hThread == NULL)
        {
            MessageBox(TEXT("无法创建接收线程,请重新启动应用程序!"), TEXT("错误"), MB_OK | MB_ICONERROR);
            return;
        }
        this->button_Receive.SetWindowText(TEXT("停止接收"));
        blRxNow = TRUE;
        /*Sleep(20);
        Decoding();
        UpdateData(FALSE);
        this->OnPaint();*/
        SetTimer(2, 100, NULL);
    }
}

void CMainWindow::OnClose()
{
    if (MessageBox(TEXT("您确定要退出吗?"), TEXT("退出提示"), MB_YESNO | MB_ICONQUESTION) != IDYES)
    {
        return;
    }

    if (hThread != NULL)
    {
        isNeedThread = FALSE;
        //  wait thread to terminated
        //
        {
            DWORD dwRet;
            do
            {
                dwRet = ::MsgWaitForMultipleObjects(1, &hThread, FALSE, INFINITE, QS_ALLINPUT);
                if (dwRet != WAIT_OBJECT_0)
                {
                    {
                        MSG msg;
                        while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
                        {
                            TranslateMessage(&msg);
                            DispatchMessage(&msg);
                        }
                    }
                }
            } while ((dwRet != WAIT_OBJECT_0) && (dwRet != WAIT_FAILED));
        }
        ::CloseHandle(hThread);
        hThread = NULL;
    }

    if (hCard != NULL)
    {
        ResetCard(hCard); // reset Card
        if (!Card_Close(hCard))
        {
            MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
        }
    }

    CDialog::OnClose();
}

//////////////////////////////////解码编码/////////////////////////////////////
// void CMainWindow::Coding()
// {
//     wdTxBufLen=0;
//     dwTxBuf[wdTxBufLen] = data_ControlWord1;
//     dwTxBuf[++wdTxBufLen] = data_ControlWord2;

//     dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_RealSpeed/(4096.0/32768));
//     dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000688;

//     dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_Speed/(2048.0/32768));
//     dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000686;

//     data_send_Mach = data_send_Speed/3.6/340;//计算其马赫数
//     dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_Mach/(4.096/32768));
//     dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000685;

//     {
//         dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_AirP/(128.0/32768));
//         dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000697;
//     }

//     {
//         dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_Attack/(45.0/32768));
//         dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x000006a1;
//     }

//     dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_High);
//     dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000684;

//     dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_SpeedUD/(512.0/32768));
//     dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x0000068a;

//     dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_Azimuth/(360.0/32768));
//     dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000632;

//     {
//         dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_Pitch/(180.0/32768));
//         dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000633;
//     }

//     {
//         dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_Roll/(180.0/32768));
//         dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000634;
//     }

//     dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_HighR/(1524.0/32768));
//     dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000635;

//     dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_HighL/(1500.0/32768));
//     dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000636;

//     {
//         dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_Sideslip/(10.0/32768));
//         dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000637;
//     }

//     {
//         dwTxBuf[++wdTxBufLen] = (DWORD)(data_send_NormalOverload/(10.0/32768));
//         dwTxBuf[wdTxBufLen] = (dwTxBuf[wdTxBufLen]<<16)|0x00000638;
//     }

// }

/////////////////////////////发送接收流程////////////////////////////////////////////
void CMainWindow::Send() // 参考demo  OnButtonSend函数
{
    int i = 0; // 发送数据个数
    char c[128];

    //  get Tx data
    //
    wdTxBufLen = 0;
    memset(dwTxBuf, 0, sizeof(DWORD) * FIFO_TMAX);

    //  fill Tx Buffer
    Coding(); // 编码

#ifndef CARD_DEBUG
    //  data transmission
    //
    i = 0; // 初始化0发送通道为发送通道1
    // we must stop the Tx timer before we want to write data to Tx FIFO
    //
    if (wdBInterval[i] > 0)
    {
        if (!StartTimerB(hCard, i, FALSE)) // 启动失败
        {
            sprintf(c, "第[%d]路终止群定时发送功能出错!\n\n(StartTimerB函数返回值为[0])", i + 1);
            MessageBox(TEXT(c), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
        }
    }

    if (wdSInterval[i] > 0)
    {
        if (!StartTimerS(hCard, i, FALSE))
        {
            sprintf(c, "第[%d]路终止字定时发送功能出错!\n\n(StartTimerS函数返回值为[0])", i + 1);
            MessageBox(TEXT(c), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
        }
    }

    if (ReadFIFOStatus_S(hCard, i) != FIFOFull) // 当FIFO缓冲区不满时发送，否则报错
    {
        wdTxBufLen = 16;
        SendData(hCard, i, (BYTE)wdTxBufLen, dwTxBuf); // 第三项发送数据长度，32位，第四项dwTxBuf发送的数据
        //        if (!SendData(hCard, i, (BYTE) wdTxBufLen, dwTxBuf))
        //        {
        //            sprintf(c, "第[%d]路发送数据出错!\n\n(SendData函数返回值为[0])", i+1);
        //            MessageBox(TEXT(c), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
        //        }
    }
    else
    { // Tx FIFO is not empty
        sprintf(c, "第[%d]路硬件缓冲区已满!\n\n(ReadFIFOStatus_S函数返回值为[0x12])", i + 1);
        MessageBox(TEXT(c), TEXT("信息提示"), MB_OK | MB_ICONINFORMATION);
    }
#endif
    // UpdateData(FALSE);
}

void CMainWindow::Receive()
{
}

void CMainWindow::OnButton_StartStopTimer() // 开始or停止自动发送
{
    // TODO: Add your control notification handler here
    if (!Timer_flg)
    {
		this->button_StartTimer.SetWindowText(TEXT("停止自动发送"));
        UpdateData(TRUE); // 用于将屏幕上控件中的数据交换到变量中，将窗口中的值读到变量中
        for (int i = 0; i < FIFO_RMAX; i++) // 清空FIFO
            ReceiveData_Vector[i] = 0x0;
        SetTimer(3, 100, NULL);
        Timer_flg = TRUE;
    }
    else
    {
		this->button_StartTimer.SetWindowText(TEXT("开始自动发送"));
        KillTimer(3);
        Sleep(10);
        Sleep(10);
        Sleep(10);
        Timer_flg = FALSE;
    }
}

void CMainWindow::OnButton_ClearTimer() // 清空自动发送
{
    memset(dwTxBuf, 0, sizeof(DWORD) * FIFO_TMAX);
    time_counter = 0;
    data_send_Speed = 0;          // 真空速
    data_send_Roll = 0.0;         // 横滚角
    data_send_Pitch = 0.0;        // 俯仰角
    data_send_High = 0;           // 无线电高度
    data_send_Azimuth = 0;        // 方位角
    data_send_Sideslip = 0.0;     // 侧滑角
    data_send_RealSpeed = 0;      // 指示空速
    data_send_Mach = 0;           // 马赫数
    data_send_AirP = 0;           // 装订气压
    data_send_Attack = 0.0;       // 攻角
    data_send_SpeedUD = 0;        // 升降高度
    data_send_HighR = 0;          // 气压高度
    data_send_HighL = 0;          // 最低安全高度
    data_send_NormalOverload = 0; // 过载

    data_receive_Speed = 0;          // 真空速
    data_receive_Roll = 0;           // 横滚角
    data_receive_Pitch = 0;          // 俯仰角
    data_receive_High = 0;           // 无线电高度
    data_receive_Azimuth = 0;        // 方位角
    data_receive_Sideslip = 0.0;     // 侧滑角
    data_receive_RealSpeed = 0;      // 指示空速
    data_receive_Mach = 0;           // 马赫数
    data_receive_AirP = 0;           // 装订气压
    data_receive_Attack = 0;         // 攻角
    data_receive_SpeedUD = 0;        // 升降高度
    data_receive_HighR = 0;          // 气压高度
    data_receive_HighL = 0;          // 最低安全高度
    data_receive_NormalOverload = 0; // 过载

    string_receive_Speed.Format("%01x", 0);
    string_receive_Roll.Format("%01x", 0);
    string_receive_Pitch.Format("%01x", 0);
    string_receive_High.Format("%01x", 0);
    string_receive_Azimuth.Format("%01x", 0);
    string_receive_Sideslip.Format("%01x", 0);
    string_receive_RealSpeed.Format("%01x", 0);
    string_receive_Mach.Format("%01x", 0);
    string_receive_AirP.Format("%01x", 0);
    string_receive_Attack.Format("%01x", 0);
    string_receive_SpeedUD.Format("%01x", 0);
    string_receive_HighR.Format("%01x", 0);
    string_receive_HighL.Format("%01x", 0);
    string_receive_NormalOverload.Format("%01x", 0);

    string_ControlWord1.Format("%01x", 0);
    string_ControlWord2.Format("%01x", 0);

    Sleep(20);
    UpdateData(FALSE);
    // TODO: Add your control notification handler code here
    // 用于移除先前设置的定时器
}

void CMainWindow::OnTimer(UINT_PTR nIDEvent) // 定时器
{
    time_counter++;
    switch (nIDEvent)
    {
    case 3:
        data_send_RealSpeed += 1;
        if (data_send_RealSpeed > 4096)
        {
            data_send_RealSpeed = 4096;
            // data_send_RealSpeed = 0;
        }

        data_send_Speed += 1;
        if (data_send_Speed > 2048)
        {
            data_send_Speed = 2048;
            // data_send_Speed = 0;
        }

        data_send_AirP += 0.1;
        if (data_send_AirP > 128)
        {
            data_send_AirP = -128;
        }

        data_send_Attack = 45 * sin(0.02 * time_counter);

        data_send_High += 5;
        if (data_send_High == 32768)
            data_send_High = 0;
        
        data_send_SpeedUD += 1;
        if (data_send_SpeedUD > 512)
        {
            data_send_SpeedUD = -512;
        }

        data_send_Azimuth += 0.5;
        if (data_send_Azimuth > 360)
            data_send_Azimuth = 0;
        
        data_send_Pitch = 180 * sin(0.005 * time_counter);

        data_send_Roll = 180 * sin(0.02 * time_counter);
        
        data_send_HighR += 5;
        if (data_send_HighR > 1524)
        {
            // data_send_HighR = 0;
            data_send_HighR = 1524;
        }
        
        data_send_HighL = 300;
        //    if (data_send_HighL > 1500)
        //    {
        //        data_send_HighL = 0;
        //    }
        data_send_Sideslip = 10 * sin(0.02 * time_counter);
        data_send_NormalOverload += 0.1;
        if (data_send_NormalOverload > 10)
        {
            data_send_NormalOverload = -10;
        }
        Send();
        UpdateData(FALSE);
        break;

    case 2:
        this->OnPaint();
        break;
    }
}


// in main window
extern CMainWindow* mother_window;

extern CMoreWindow* more_window;

/*++
	Routine Description:
		Thread function used to read six channels counter and two AD's sampling data.
		
	Arguments:
		1) lpParam: [IN/OUT] needed parameter for thread.
		
	Return Value:
		If the function is seceeded, return value is TRUE else is FALSE;
--*/
DWORD WINAPI DecodeThreadFunc(LPVOID lpParam)
{
start:	HWND hWnd = (HWND)lpParam;
	DWORD d = 0;
	BYTE chno = 0;
	BYTE btTriggerLevel = 0;
	int i = 0;
#ifndef CARD_DEBUG
	while (mother_window->isNeedThread)
	{
		//  Get trigger level
		//
		btTriggerLevel = mother_window->stTriggerLevel.Chan0Depth_I;

		//  Rx channel 1~CHNO_RMAX
		// ----------------------------------------------------------------
		if (btTriggerLevel > 0) // triggered//xu yao guo lv 
		{
			if (IsFIFOTriggered_R(mother_window->hCard, chno))
			{
				EnablReadFIFO(mother_window->hCard, chno);
				while ((ReadFIFOStatus_R(mother_window->hCard, chno) != FIFOEmpty) && (ReadFIFOStatus_R(mother_window->hCard, chno) != FIFOError))
					// recieveFIFO
				{
					d = ReceiveData(mother_window->hCard, chno);
					if ((mother_window->wdMode == C429_SELFTEST) && (mother_window->stComm[chno / 2].iSelParity == C429_PARITY_NONE)) // resume 429 Word
					{
						d = Resume429Word(d);
					}
					Save_ReceiveData(d, mother_window->ReceiveData_Vector + i);
				}
				DisablReadFIFO(mother_window->hCard);
			}
		}
		else // untriggered
		{
			if ((ReadFIFOStatus_R(mother_window->hCard, chno) != FIFOEmpty) && (ReadFIFOStatus_R(mother_window->hCard, chno) != FIFOError))//???????recieveFIFO ???????????
			{
				EnablReadFIFO(mother_window->hCard, chno);
				d = ReceiveData(mother_window->hCard, chno);
				if ((mother_window->wdMode == C429_SELFTEST) && (mother_window->stComm[chno / 2].iSelParity == C429_PARITY_NONE)) // resume 429 Word
				{
					d = Resume429Word(d);
				}
				DWORD temp;  
				temp = d & 0x00FF;
				short s;
				switch (temp)
				{
				case 0x30:
					mother_window->string_ControlWord1.Format("%08x", d); break;
					//0000 0110 0011 0000
				case 0x31:
					mother_window->string_ControlWord2.Format("%08x", d); break;
					//0000 0110 0011 0001
				
				case 0x88:	//?????
					s = (short)(d >> 16);
					mother_window->data_receive_RealSpeed = s * (4096. / 32768);
					mother_window->string_receive_RealSpeed.Format("%d", mother_window->data_receive_RealSpeed); 
					// mother_window->string_difference_RealSpeed.Format("%d", mother_window->data_receive_RealSpeed - mother_window->data_send_RealSpeed); 
					break;
					//0000 0110 1000 1000
				case 0x86://??????
					s = (short)(d >> 16);
					mother_window->data_receive_Speed = s * (2048. / 32768);
					mother_window->string_receive_Speed.Format("%d", mother_window->data_receive_Speed);
					break;
					//0000 0110 1000 0110
				case 0x85://??????
					s = (short)(d >> 16);
					mother_window->data_receive_Mach = s * (4.096 / 32768);
					mother_window->string_receive_Mach.Format("%.3f", mother_window->data_receive_Mach);
					break;
					//	0000 0110 0001 0101
				case 0x97://??????
					s = (short)(d >> 16);
					mother_window->data_receive_AirP = s * (128. / 32768);
					mother_window->string_receive_AirP.Format("%.3f", mother_window->data_receive_AirP); break;
					//0000 0110 1001 0111
				case 0xA1://????
					s = (short)(d >> 16);
					mother_window->data_receive_Attack = s * (45. / 32768);
					mother_window->string_receive_Attack.Format("%.2f", mother_window->data_receive_Attack); break;
					//0000 0110 1010 0001
				case 0x84://?????????
					s = (short)(d >> 16);
					mother_window->data_receive_High = s;
					mother_window->string_receive_High.Format("%d", mother_window->data_receive_High); break;
					//0000 0110 1000 0100
				case 0x8A://???????
					s = (short)(d >> 16);
					mother_window->data_receive_SpeedUD = s * (512. / 32768);
					mother_window->string_receive_SpeedUD.Format("%d", mother_window->data_receive_SpeedUD); break;
					//0000 0110 1000 1010
				case 0x32://?????
					s = (short)(d >> 16);
					mother_window->data_receive_Azimuth = s * (360. / 32768);
					mother_window->string_receive_Azimuth.Format("%.2f", mother_window->data_receive_Azimuth); break;
					//0000 0110 0011 0010
				case 0x33://??????
					s = (short)(d >> 16);
					mother_window->data_receive_Pitch = s * (180. / 32768);
					mother_window->string_receive_Pitch.Format("%.2f", mother_window->data_receive_Pitch); break;
					//0000 0110 0011 0011
				case 0x34://?????
					s = (short)(d >> 16);
					mother_window->data_receive_Roll = s * (180. / 32768);
					mother_window->string_receive_Roll.Format("%.2f", mother_window->data_receive_Roll); break;
					//0000 0110 0011 0100
				case 0x35://???????
					s = (short)(d >> 16);
					mother_window->data_receive_HighR = s * (1524. / 32768);
					mother_window->string_receive_HighR.Format("%d", mother_window->data_receive_HighR); break;
					//0000 0110 0011 0101
				case 0x36://????????
					s = (short)(d >> 16);
					mother_window->data_receive_HighL = s * (1500. / 32768);
					mother_window->string_receive_HighL.Format("%d", mother_window->data_receive_HighL); break;
					//0000 0110 0011 0110 
				case 0x37://????
					s = (short)(d >> 16);
					mother_window->data_receive_Sideslip = s * (10. / 32768);
					mother_window->string_receive_Sideslip.Format("%.2f", mother_window->data_receive_Sideslip); break;
					//0000 0110 0011 0111
				case 0x38://???????
					s = (short)(d >> 16);
					mother_window->data_receive_NormalOverload = s * (10. / 32768);
					mother_window->string_receive_NormalOverload.Format("%.2f", mother_window->data_receive_NormalOverload); break;
					//0000 0110 0011 1000
				default:
					break;
				}
			}
			DisablReadFIFO(mother_window->hCard);
		} // end of if (btTriggerLevel...		
	} // end of while ((chno<CHNO_RMAX...
	

	

#endif	

		ExitThread(THREAD_EXITCODE);
return 0;

}

void CMainWindow::OnGoToMore()
{
	CMoreWindow window;
    window.DoModal();
}