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
    // �����ʵ�ѡ��
    for (i = 0; i < CHNO_TMAX; i++)
    {
        // followed definitions can be found in cusfunc.h
        stComm[i].iSelBR = C429_BITRATE100K;     // 0: 100k    1: 48k    2: 12.5k
        stComm[i].iSelParity = C429_PARITY_NONE; // 0: odd    1: even    2: none
        wdBInterval[i] = 0;
        wdSInterval[i] = 0; // 100K / ��У��
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
    data_receive_ControlWord1 = 0x00000630; ////????
    data_receive_ControlWord2 = 0x00000631; ////????
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
        MessageBox(TEXT("�����Ҳ����忨,�����˳�!\n\n(Card_Open��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
        ExitProcess(0);
        // return FALSE; // quit program
    }
    if (hCard == NULL)
    {
        MessageBox(TEXT("�����Ҳ����忨,�����˳�!\n\n(�忨�����ȡʧ��)"), TEXT("����"), MB_OK | MB_ICONERROR);
        ExitProcess(0);
        // return FALSE; // quit program
    }

    //  1. reset card�����ð忨��
    //
    if (!ResetCard(hCard)) // reset Card
    {
        MessageBox(TEXT("��λ�忨ʧ��,�����˳�����!\n\n(ResetCard��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
        if (!Card_Close(hCard))
        {
            MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
        }
        ExitProcess(0);
        // return FALSE; // quit program
    }

    //  2. setting up configure word for communication
    //
    for (i = 0; i < CHNO_TMAX; i++) // ����ͨ����2ͨ����
    {
        wd = ::Get429ConfigureWord(stComm[i].iSelBR, stComm[i].iSelParity, wdMode); // wdMode����ģʽ
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
        if (SetConfigureWord(hCard, (BYTE)(i), wd)) // ���˼��䲨���ʵ�ѡ��//����429 ��������
        {
            if (stComm[i].iSelBR == C429_BITRATE48K) // enable 48k function
            {
                EnableBaudrate_48K(hCard, (BYTE)(i), TRUE); // �˱����£�������ͳһѡ��48k
            }
            else
            {
                EnableBaudrate_48K(hCard, (BYTE)(i), FALSE);
            }
        }
        else
        {
            MessageBox(TEXT("����Ӳ������,�����˳�����!\n\n(SetConfigureWord��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
            if (!Card_Close(hCard))
            {
                MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
            }
            ExitProcess(0);
            // return FALSE; // quit program
        }
    }

    //  3. configuring Trigger Level
    //On_RADIO_SelfSend
    SetTriggerDepth(hCard, &stTriggerLevel); // ���ô������

    //  4. setting up Label Filter
    //
    SetLabelFilter(hCard, &stLabelTable); // ���ñ�ǩ����
    for (i = 0; i < CHNO_RMAX; i++)       // ֻ����ڽ���ͨ��
    {
        if (blFilter[i])
        {
            if (!StartLabelFilter(hCard, (BYTE)(i), TRUE))
            {
                MessageBox(TEXT("��ӱ�Ź��˹��ܳ���,�����˳�����!\n\n(StartLabelFilter��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
                if (!Card_Close(hCard))
                {
                    MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
                }
                ExitProcess(0);
                //    return FALSE; // quit program
            }
        }
        else
        {
            if (!StartLabelFilter(hCard, (BYTE)(i), FALSE))
            {
                MessageBox(TEXT("ȡ����Ź��˹��ܳ���,�����˳�����!\n\n(StartLabelFilter��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
                if (!Card_Close(hCard))
                {
                    MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
                }
                ExitProcess(0);
                //    return FALSE; // quit program
            }
        }
    }

    //  5. configuring Time Tag�����ʱ���ǩ
    //
    for (i = 0; i < CHNO_RMAX; i++)
    {
        if (blTimeTag[i])
        {
            if (!AddTimeTag(hCard, (BYTE)(i), TRUE))
            {
                MessageBox(TEXT("���ʱ���ǩ���ܳ���,�����˳�����!\n\n(AddTimeTag��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
                if (!Card_Close(hCard))
                {
                    MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
                }
                ExitProcess(0);
                //    return FALSE; // quit program
            }
        }
        else
        {
            if (!AddTimeTag(hCard, (BYTE)(i), FALSE))
            {
                MessageBox(TEXT("ȡ��ʱ���ǩ���ܳ���,�����˳�����!\n\n(AddTimeTag��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
                if (!Card_Close(hCard))
                {
                    MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
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
    for (i = 0; i < CHNO_TMAX; i++) // ��Ϣ�ķ���
    {
        if (!SetTimerIntervalB(hCard, (BYTE)(i), wdBInterval[i])) // b��Ⱥ��ʱ����
        {
            MessageBox(TEXT("����Ⱥ��ʱ���͹��ܳ���,�����˳�����!\n\n(SetTimerIntervalB��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
            if (!Card_Close(hCard))
            {
                MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
            }
            // ExitProcess(0);
            ExitProcess(0);
            //    return FALSE; // quit program
        }

        if (!SetTimerIntervalS(hCard, (BYTE)(i), wdSInterval[i])) // s���ֶ�ʱ����
        {
            MessageBox(TEXT("�����ֶ�ʱ���͹��ܳ���,�����˳�����!\n\n(SetTimerIntervalS��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
            if (!Card_Close(hCard))
            {
                MessageBox(TEXT("�رհ忨ʧ��!\n\n(Card_Close��������ֵΪ[0])"), TEXT("����"), MB_OK | MB_ICONERROR);
            }
            ExitProcess(0);
            //    return FALSE; // quit program
        }

        if (wdBInterval[i] > 0)
        {
            StartTimerB(hCard, (BYTE)(i), TRUE); // enable Tx Timer//����Ⱥ��ʱ����
        }
        else
        {
            StartTimerB(hCard, (BYTE)(i), FALSE); // disable Tx Timer
        }

        if (wdSInterval[i] > 0)
        {
            StartTimerS(hCard, (BYTE)(i), TRUE); // enable Tx Timer//�����ֶ�ʱ����
        }
        else
        {
            StartTimerS(hCard, (BYTE)(i), FALSE); // disable Tx Timer
        }
    }

    if (!Enable_R(hCard, TRUE)) // ʹ�ܽ��գ��ڸ�λ�忨ʱ��ֹ�˽���
    {
        MessageBox(TEXT("ʹ�ܽ���ʧ��"), TEXT("����"), MB_OK | MB_ICONERROR);
    }
#endif
    return TRUE;
}
