#include "stdafx.h"
#include "ARNIC429.h"
#include "MainWindow.h"

#include "math.h"

#include "DevelopWindow.h"
#include "MoreWindow.h"

void CMainWindow::OnChangeEDITSpeed()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    char c[80], s[80], f[80];
    char tc = '\0';
    int i = 0;
    int l = 0, j = 0;
    int nStart = 0, nEnd = 0;
    BOOL isErr = FALSE;
    DWORD dw = 0;
    int ii = 0;
    float ff = 0;

    l = this->textbox_send_Speed.LineLength(-1);
    if (l == 0)
        return;

    memset(s, 0, sizeof(s)); // s和c两个变量初始化为零
    memset(c, 0, sizeof(c));

    dw = this->textbox_send_Speed.GetSel();

    this->textbox_send_Speed.GetWindowText(c, sizeof(c)); // get data string with

    //  analyze data string with HEX
    //
    j = 0;
    for (i = 0; i < l; i++)
    {
        tc = c[i];
        if ((tc >= '0') && (tc <= '9'))
        {
            s[j] = tc;
            j++;
        }
        else
        {
            isErr = TRUE;
        }
    }

    if (!isErr)
    {
        ii = atoi(c); // 字符串转化为整形
        ff = ii / 3.6 / 340;
        sprintf(f, "%f", ff);
        this->textbox_send_Ma.SetWindowText("3");
        return;
    }

    //  write back the HEX value
    ii = atoi(s);
    ff = ii / 3.6 / 340;
    sprintf(f, "%f", ff);
    this->textbox_send_Ma.SetWindowText(f);

    this->textbox_send_Speed.SetWindowText(s);
    this->textbox_send_Speed.SetSel(HIWORD(dw) - 1, HIWORD(dw) - 1, FALSE);
}

void CMainWindow::OnKillfocusEDITSpeed()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Speed.LineLength(-1) == 0)
    {
        this->textbox_send_Speed.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChangeEDITSlideslip()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    char c[80], s[80];
    char tc = '\0';
    int i = 0;
    int l = 0, j = 0;
    int nStart = 0, nEnd = 0;
    BOOL isErr = FALSE;
    DWORD dw = 0;

    l = this->textbox_send_Sideslip.LineLength(-1);
    if (l == 0)
        return;

    memset(s, 0, sizeof(s));
    memset(c, 0, sizeof(c));

    dw = this->textbox_send_Sideslip.GetSel();

    this->textbox_send_Sideslip.GetWindowText(c, sizeof(c)); // get data string with HEX

    //  analyze data string with HEX
    //
    j = 0;
    for (i = 0; i < l; i++)
    {
        tc = c[i];
        if ((tc >= '0') && (tc <= '9') || tc == '.' || tc == '-')
        {
            s[j] = tc;
            j++;
        }
        else
        {
            isErr = TRUE;
        }
    }

    if (!isErr)
        return;

    //  write back the HEX value
    //
    this->textbox_send_Sideslip.SetWindowText(s);
    this->textbox_send_Sideslip.SetSel(HIWORD(dw) - 1, HIWORD(dw) - 1, FALSE);
}

void CMainWindow::OnKillfocusEDITSlideslip()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Sideslip.LineLength(-1) == 0)
    {
        this->textbox_send_Sideslip.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChangeEDITRoll()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    char c[80], s[80];
    char tc = '\0';
    int i = 0;
    int l = 0, j = 0;
    int nStart = 0, nEnd = 0;
    BOOL isErr = FALSE;
    DWORD dw = 0;

    l = this->textbox_send_Roll.LineLength(-1);
    if (l == 0)
        return;

    memset(s, 0, sizeof(s));
    memset(c, 0, sizeof(c));

    dw = this->textbox_send_Roll.GetSel();

    this->textbox_send_Roll.GetWindowText(c, sizeof(c)); // get data string with HEX

    //  analyze data string with HEX
    //
    j = 0;
    for (i = 0; i < l; i++)
    {
        tc = c[i];
        if ((tc >= '0') && (tc <= '9') || tc == '.' || tc == '-')
        {
            s[j] = tc;
            j++;
        }
        else
        {
            isErr = TRUE;
        }
    }

    if (!isErr)
        return;

    //  write back the HEX value
    //
    this->textbox_send_Roll.SetWindowText(s);
    this->textbox_send_Roll.SetSel(HIWORD(dw) - 1, HIWORD(dw) - 1, FALSE);
}

void CMainWindow::OnKillfocusEDITRoll()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Roll.LineLength(-1) == 0)
    {
        this->textbox_send_Roll.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChangeEDITPitch()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    char c[80], s[80];
    char tc = '\0';
    int i = 0;
    int l = 0, j = 0;
    int nStart = 0, nEnd = 0;
    BOOL isErr = FALSE;
    DWORD dw = 0;

    l = this->textbox_send_Pitch.LineLength(-1);
    if (l == 0)
        return;

    memset(s, 0, sizeof(s));
    memset(c, 0, sizeof(c));

    dw = this->textbox_send_Pitch.GetSel();

    this->textbox_send_Pitch.GetWindowText(c, sizeof(c)); // get data string with HEX

    //  analyze data string with HEX
    //
    j = 0;
    for (i = 0; i < l; i++)
    {
        tc = c[i];
        if ((tc >= '0') && (tc <= '9') || tc == '.' || tc == '-')
        {
            s[j] = tc;
            j++;
        }
        else
        {
            isErr = TRUE;
        }
    }

    if (!isErr)
        return;

    //  write back the HEX value
    //
    this->textbox_send_Pitch.SetWindowText(s);
    this->textbox_send_Pitch.SetSel(HIWORD(dw) - 1, HIWORD(dw) - 1, FALSE);
}

void CMainWindow::OnKillfocusEDITPitch()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Pitch.LineLength(-1) == 0)
    {
        this->textbox_send_Pitch.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChangeEDITHigh()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    char c[80], s[80];
    char tc = '\0';
    int i = 0;
    int l = 0, j = 0;
    int nStart = 0, nEnd = 0;
    BOOL isErr = FALSE;
    DWORD dw = 0;

    l = this->textbox_send_High.LineLength(-1);
    if (l == 0)
        return;

    memset(s, 0, sizeof(s));
    memset(c, 0, sizeof(c));

    dw = this->textbox_send_High.GetSel();

    this->textbox_send_High.GetWindowText(c, sizeof(c)); // get data string with HEX

    //  analyze data string with HEX
    //
    j = 0;
    for (i = 0; i < l; i++)
    {
        tc = c[i];
        if ((tc >= '0') && (tc <= '9'))
        {
            s[j] = tc;
            j++;
        }
        else
        {
            isErr = TRUE;
        }
    }

    if (!isErr)
        return;

    //  write back the HEX value
    //
    this->textbox_send_High.SetWindowText(s);
    this->textbox_send_High.SetSel(HIWORD(dw) - 1, HIWORD(dw) - 1, FALSE);
}

void CMainWindow::OnKillfocusEDITHigh()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_High.LineLength(-1) == 0)
    {
        this->textbox_send_High.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChangeEDITAzimuth()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    char c[80], s[80];
    char tc = '\0';
    int i = 0;
    int l = 0, j = 0;
    int nStart = 0, nEnd = 0;
    BOOL isErr = FALSE;
    DWORD dw = 0;

    l = this->textbox_send_Azimuth.LineLength(-1);
    if (l == 0)
        return;

    memset(s, 0, sizeof(s));
    memset(c, 0, sizeof(c));

    dw = this->textbox_send_Azimuth.GetSel();

    this->textbox_send_Azimuth.GetWindowText(c, sizeof(c)); // get data string with HEX

    //  analyze data string with HEX
    //
    j = 0;
    for (i = 0; i < l; i++)
    {
        tc = c[i];
        if ((tc >= '0') && (tc <= '9') || tc == '.')
        {
            s[j] = tc;
            j++;
        }
        else
        {
            isErr = TRUE;
        }
    }

    if (!isErr)
        return;

    //  write back the HEX value
    //
    this->textbox_send_Azimuth.SetWindowText(s);
    this->textbox_send_Azimuth.SetSel(HIWORD(dw) - 1, HIWORD(dw) - 1, FALSE);
}

void CMainWindow::OnKillfocusEDITAzimuth()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChangeEDITRealSpeed()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    char c[80], s[80];
    char tc = '\0';
    int i = 0;
    int l = 0, j = 0;
    int nStart = 0, nEnd = 0;
    BOOL isErr = FALSE;
    DWORD dw = 0;

    l = this->textbox_send_RealSpeed.LineLength(-1);
    if (l == 0)
        return;

    memset(s, 0, sizeof(s));
    memset(c, 0, sizeof(c));

    dw = this->textbox_send_RealSpeed.GetSel();

    this->textbox_send_RealSpeed.GetWindowText(c, sizeof(c)); // get data string with HEX

    //  analyze data string with HEX
    //
    j = 0;
    for (i = 0; i < l; i++)
    {
        tc = c[i];
        if ((tc >= '0') && (tc <= '9'))
        {
            s[j] = tc;
            j++;
        }
        else
        {
            isErr = TRUE;
        }
    }

    if (!isErr)
        return;

    //  write back the HEX value
    //
    this->textbox_send_RealSpeed.SetWindowText(s);
    this->textbox_send_RealSpeed.SetSel(HIWORD(dw) - 1, HIWORD(dw) - 1, FALSE);
}

void CMainWindow::OnKillfocusEDITRealSpeed()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnKillfocusEDITMa()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Ma.LineLength(-1) == 0)
    {
        this->textbox_send_Ma.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChangeEDITMa()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
}

void CMainWindow::OnChangeEDITAirP()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    char c[80], s[80];
    char tc = '\0';
    int i = 0;
    int l = 0, j = 0;
    int nStart = 0, nEnd = 0;
    BOOL isErr = FALSE;
    DWORD dw = 0;

    l = this->textbox_send_AirP.LineLength(-1);
    if (l == 0)
        return;

    memset(s, 0, sizeof(s));
    memset(c, 0, sizeof(c));

    dw = this->textbox_send_AirP.GetSel();

    this->textbox_send_AirP.GetWindowText(c, sizeof(c)); // get data string with HEX

    //  analyze data string with HEX
    //
    j = 0;
    for (i = 0; i < l; i++)
    {
        tc = c[i];
        if ((tc >= '0') && (tc <= '9') || tc == '.' || tc == '-')
        {
            s[j] = tc;
            j++;
        }
        else
        {
            isErr = TRUE;
        }
    }

    if (!isErr)
        return;

    //  write back the HEX value
    //
    this->textbox_send_AirP.SetWindowText(s);
    this->textbox_send_AirP.SetSel(HIWORD(dw) - 1, HIWORD(dw) - 1, FALSE);
}

void CMainWindow::OnKillfocusEDITAirP()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChangeEDITAttack()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    char c[80], s[80];
    char tc = '\0';
    int i = 0;
    int l = 0, j = 0;
    int nStart = 0, nEnd = 0;
    BOOL isErr = FALSE;
    DWORD dw = 0;

    l = this->textbox_send_Attack.LineLength(-1);
    if (l == 0)
        return;

    memset(s, 0, sizeof(s));
    memset(c, 0, sizeof(c));

    dw = this->textbox_send_Attack.GetSel();

    this->textbox_send_Attack.GetWindowText(c, sizeof(c)); // get data string with HEX

    //  analyze data string with HEX
    //
    j = 0;
    for (i = 0; i < l; i++)
    {
        tc = c[i];
        if ((tc >= '0') && (tc <= '9') || tc == '.' || tc == '-')
        {
            s[j] = tc;
            j++;
        }
        else
        {
            isErr = TRUE;
        }
    }

    if (!isErr)
        return;

    //  write back the HEX value
    //
    this->textbox_send_Attack.SetWindowText(s);
    this->textbox_send_Attack.SetSel(HIWORD(dw) - 1, HIWORD(dw) - 1, FALSE);
}

void CMainWindow::OnKillfocusEDITAttack()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChangeEDITSpeedUD()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    char c[80], s[80];
    char tc = '\0';
    int i = 0;
    int l = 0, j = 0;
    int nStart = 0, nEnd = 0;
    BOOL isErr = FALSE;
    DWORD dw = 0;

    l = this->textbox_send_SpeedUD.LineLength(-1);
    if (l == 0)
        return;

    memset(s, 0, sizeof(s));
    memset(c, 0, sizeof(c));

    dw = this->textbox_send_SpeedUD.GetSel();

    this->textbox_send_SpeedUD.GetWindowText(c, sizeof(c)); // get data string with HEX

    //  analyze data string with HEX
    //
    j = 0;
    for (i = 0; i < l; i++)
    {
        tc = c[i];
        if ((tc >= '0') && (tc <= '9'))
        {
            s[j] = tc;
            j++;
        }
        else
        {
            isErr = TRUE;
        }
    }

    if (!isErr)
        return;

    //  write back the HEX value
    //
    this->textbox_send_SpeedUD.SetWindowText(s);
    this->textbox_send_SpeedUD.SetSel(HIWORD(dw) - 1, HIWORD(dw) - 1, FALSE);
}

void CMainWindow::OnKillfocusEDITSpeedUD()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChangeEDITHighR()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    char c[80], s[80];
    char tc = '\0';
    int i = 0;
    int l = 0, j = 0;
    int nStart = 0, nEnd = 0;
    BOOL isErr = FALSE;
    DWORD dw = 0;

    l = this->textbox_send_HighR.LineLength(-1);
    if (l == 0)
        return;

    memset(s, 0, sizeof(s));
    memset(c, 0, sizeof(c));

    dw = this->textbox_send_HighR.GetSel();

    this->textbox_send_HighR.GetWindowText(c, sizeof(c)); // get data string with HEX

    //  analyze data string with HEX
    //
    j = 0;
    for (i = 0; i < l; i++)
    {
        tc = c[i];
        if ((tc >= '0') && (tc <= '9'))
        {
            s[j] = tc;
            j++;
        }
        else
        {
            isErr = TRUE;
        }
    }

    if (!isErr)
        return;

    //  write back the HEX value
    //
    this->textbox_send_HighR.SetWindowText(s);
    this->textbox_send_HighR.SetSel(HIWORD(dw) - 1, HIWORD(dw) - 1, FALSE);
}

void CMainWindow::OnKillfocusEDITHighR()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChangeEDITHighL()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    char c[80], s[80];
    char tc = '\0';
    int i = 0;
    int l = 0, j = 0;
    int nStart = 0, nEnd = 0;
    BOOL isErr = FALSE;
    DWORD dw = 0;

    l = this->textbox_send_HighL.LineLength(-1);
    if (l == 0)
        return;

    memset(s, 0, sizeof(s));
    memset(c, 0, sizeof(c));

    dw = this->textbox_send_HighL.GetSel();

    this->textbox_send_HighL.GetWindowText(c, sizeof(c)); // get data string with HEX

    //  analyze data string with HEX
    //
    j = 0;
    for (i = 0; i < l; i++)
    {
        tc = c[i];
        if ((tc >= '0') && (tc <= '9'))
        {
            s[j] = tc;
            j++;
        }
        else
        {
            isErr = TRUE;
        }
    }

    if (!isErr)
        return;

    //  write back the HEX value
    //
    this->textbox_send_HighL.SetWindowText(s);
    this->textbox_send_HighL.SetSel(HIWORD(dw) - 1, HIWORD(dw) - 1, FALSE);
}

void CMainWindow::OnKillfocusEDITHighL()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChangeEditn()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
    char c[80], s[80];
    char tc = '\0';
    int i = 0;
    int l = 0, j = 0;
    int nStart = 0, nEnd = 0;
    BOOL isErr = FALSE;
    DWORD dw = 0;

    l = this->textbox_send_NormalOverload.LineLength(-1);
    if (l == 0)
        return;

    memset(s, 0, sizeof(s));
    memset(c, 0, sizeof(c));

    dw = this->textbox_send_NormalOverload.GetSel();

    this->textbox_send_NormalOverload.GetWindowText(c, sizeof(c)); // get data string with HEX

    //  analyze data string with HEX
    //
    j = 0;
    for (i = 0; i < l; i++)
    {
        tc = c[i];
        if ((tc >= '0') && (tc <= '9') || tc == '-')
        {
            s[j] = tc;
            j++;
        }
        else
        {
            isErr = TRUE;
        }
    }

    if (!isErr)
        return;

    //  write back the HEX value
    //
    this->textbox_send_NormalOverload.SetWindowText(s);
    this->textbox_send_NormalOverload.SetSel(HIWORD(dw) - 1, HIWORD(dw) - 1, FALSE); // 为FALSE表示会随光标位置改变而滚动滚动条。
}

void CMainWindow::OnKillfocusEditn()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}
