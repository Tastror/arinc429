#include "stdafx.h"
#include "ARNIC429.h"
#include "MainWindow.h"

#include "math.h"

#include "DevelopWindow.h"
#include "MoreWindow.h"

BOOL CMainWindow::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.
    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu *pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_Develop);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog. The framework does this automatically
    // when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);  // Set big icon
    SetIcon(m_hIcon, FALSE); // Set small icon

    // Add extra initialization here
    int i, j;

    // default Trigger Level
    stTriggerLevel.Chan0Depth_I = TriggerLevel;
    stTriggerLevel.Chan1Depth_I = TriggerLevel;
    stTriggerLevel.Chan2Depth_I = TriggerLevel;
    stTriggerLevel.Chan3Depth_I = TriggerLevel;
    stTriggerLevel.Chan0Depth_O = TriggerLevel;
    stTriggerLevel.Chan1Depth_O = TriggerLevel;

    // default Label Filter
    for (i = 0; i < SD_MAX; i++)
    {
        for (j = 0; j < LABEL_MAX; j++)
        {
            stLabelTable.LabFilterChan0[i][j] = 0;
            stLabelTable.LabFilterChan1[i][j] = 0;
            stLabelTable.LabFilterChan2[i][j] = 0;
            stLabelTable.LabFilterChan3[i][j] = 0;
        }
    }

    // bits rate & parity
    // 波特率的选择
    for (i = 0; i < CHNO_TMAX; i++)
    {
        // followed definitions can be found in cusfunc.h
        stComm[i].iSelBR = C429_BITRATE100K;     // 0: 100k    1: 48k    2: 12.5k
        stComm[i].iSelParity = C429_PARITY_NONE; // 0: odd    1: even    2: none
        wdBInterval[i] = 0;
        wdSInterval[i] = 0; // 100K / 无校验
    }

    for (i = 0; i < CHNO_RMAX; i++)
    {
        blFilter[i] = FALSE;  // disable label filter function
        blTimeTag[i] = FALSE; // disable Time Tag function
    }

    wdMode = C429_SELFTEST; // SELFTEST work mode

    for (i = 0; i < FIFO_RMAX; i++)
        ReceiveData_Vector[i] = 0x0;
    time_counter = 0;
    m_ControlWord1 = 0x00000630; ////????
    m_ControlWord2 = 0x00000631; ////????
    Complete_flg = FALSE;
    return TRUE; // return TRUE  unless you set the focus to a control
}

HCURSOR CMainWindow::OnQueryDragIcon() // demo
{
    return (HCURSOR)m_hIcon;
}

void CMainWindow::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CDevelopWindow window;
        window.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

BOOL CMainWindow::SetUp429Card()
{
    WORD wd = 0;
    int i = 0;
#ifndef CARD_DEBUG
    //    Try to Open card and setting up the card with default configuration
    //

    //  0. open card
    //
    if (!Card_Open(&hCard, btCardId))
    {
        MessageBox(TEXT("程序找不到板卡,即将退出!\n\n(Card_Open函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
        ExitProcess(0);
        // return FALSE; // quit program
    }
    if (hCard == NULL)
    {
        MessageBox(TEXT("程序找不到板卡,即将退出!\n\n(板卡句柄获取失败)"), TEXT("错误"), MB_OK | MB_ICONERROR);
        ExitProcess(0);
        // return FALSE; // quit program
    }

    //  1. reset card（重置板卡）
    //
    if (!ResetCard(hCard)) // reset Card
    {
        MessageBox(TEXT("复位板卡失败,即将退出程序!\n\n(ResetCard函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
        if (!Card_Close(hCard))
        {
            MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
        }
        ExitProcess(0);
        // return FALSE; // quit program
    }

    //  2. setting up configure word for communication
    //
    for (i = 0; i < CHNO_TMAX; i++) // 发出通道（2通道）
    {
        wd = ::Get429ConfigureWord(stComm[i].iSelBR, stComm[i].iSelParity, wdMode); // wdMode工作模式
        switch (wd)
        {
        case 0xFFFF:
            MessageBox("baudrate", "Error", MB_OK);
            break;
        case 0xFFFE:
            MessageBox("parity", "Error", MB_OK);
            break;
        case 0xFFFD:
            MessageBox("workmode", "Error", MB_OK);
            break;
        }
        if (SetConfigureWord(hCard, (BYTE)(i), wd)) // 过滤及其波特率的选择//设置429 的配置字
        {
            if (stComm[i].iSelBR == C429_BITRATE48K) // enable 48k function
            {
                EnableBaudrate_48K(hCard, (BYTE)(i), TRUE); // 此背景下，波特率统一选择48k
            }
            else
            {
                EnableBaudrate_48K(hCard, (BYTE)(i), FALSE);
            }
        }
        else
        {
            MessageBox(TEXT("配置硬件出错,即将退出程序!\n\n(SetConfigureWord函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
            if (!Card_Close(hCard))
            {
                MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
            }
            ExitProcess(0);
            // return FALSE; // quit program
        }
    }

    //  3. configuring Trigger Level
    //On_RADIO_SelfSend
    SetTriggerDepth(hCard, &stTriggerLevel); // 设置触发深度

    //  4. setting up Label Filter
    //
    SetLabelFilter(hCard, &stLabelTable); // 设置标签过滤
    for (i = 0; i < CHNO_RMAX; i++)       // 只针对于接收通道
    {
        if (blFilter[i])
        {
            if (!StartLabelFilter(hCard, (BYTE)(i), TRUE))
            {
                MessageBox(TEXT("添加标号过滤功能出错,即将退出程序!\n\n(StartLabelFilter函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
                if (!Card_Close(hCard))
                {
                    MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
                }
                ExitProcess(0);
                //    return FALSE; // quit program
            }
        }
        else
        {
            if (!StartLabelFilter(hCard, (BYTE)(i), FALSE))
            {
                MessageBox(TEXT("取消标号过滤功能出错,即将退出程序!\n\n(StartLabelFilter函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
                if (!Card_Close(hCard))
                {
                    MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
                }
                ExitProcess(0);
                //    return FALSE; // quit program
            }
        }
    }

    //  5. configuring Time Tag。添加时间标签
    //
    for (i = 0; i < CHNO_RMAX; i++)
    {
        if (blTimeTag[i])
        {
            if (!AddTimeTag(hCard, (BYTE)(i), TRUE))
            {
                MessageBox(TEXT("添加时间标签功能出错,即将退出程序!\n\n(AddTimeTag函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
                if (!Card_Close(hCard))
                {
                    MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
                }
                ExitProcess(0);
                //    return FALSE; // quit program
            }
        }
        else
        {
            if (!AddTimeTag(hCard, (BYTE)(i), FALSE))
            {
                MessageBox(TEXT("取消时间标签功能出错,即将退出程序!\n\n(AddTimeTag函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
                if (!Card_Close(hCard))
                {
                    MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
                }
                ExitProcess(0);
                //    return FALSE; // quit program
            }
        }
    }
    StartTimeTag(hCard, FALSE, &stSysTime); // disable time tag
    dwTime = 0;

    //  6. setting up Tx Timer Interval
    //
    for (i = 0; i < CHNO_TMAX; i++) // 消息的发送
    {
        if (!SetTimerIntervalB(hCard, (BYTE)(i), wdBInterval[i])) // b是群定时发送
        {
            MessageBox(TEXT("设置群定时发送功能出错,即将退出程序!\n\n(SetTimerIntervalB函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
            if (!Card_Close(hCard))
            {
                MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
            }
            // ExitProcess(0);
            ExitProcess(0);
            //    return FALSE; // quit program
        }

        if (!SetTimerIntervalS(hCard, (BYTE)(i), wdSInterval[i])) // s是字定时发送
        {
            MessageBox(TEXT("设置字定时发送功能出错,即将退出程序!\n\n(SetTimerIntervalS函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
            if (!Card_Close(hCard))
            {
                MessageBox(TEXT("关闭板卡失败!\n\n(Card_Close函数返回值为[0])"), TEXT("错误"), MB_OK | MB_ICONERROR);
            }
            ExitProcess(0);
            //    return FALSE; // quit program
        }

        if (wdBInterval[i] > 0)
        {
            StartTimerB(hCard, (BYTE)(i), TRUE); // enable Tx Timer//设置群定时发送
        }
        else
        {
            StartTimerB(hCard, (BYTE)(i), FALSE); // disable Tx Timer
        }

        if (wdSInterval[i] > 0)
        {
            StartTimerS(hCard, (BYTE)(i), TRUE); // enable Tx Timer//设置字定时发送
        }
        else
        {
            StartTimerS(hCard, (BYTE)(i), FALSE); // disable Tx Timer
        }
    }

    if (!Enable_R(hCard, TRUE)) // 使能接收，在复位板卡时禁止了接收
    {
        MessageBox(TEXT("使能接收失败"), TEXT("错误"), MB_OK | MB_ICONERROR);
    }
#endif
    return TRUE;
}
