#include "stdafx.h"
#include "ARNIC429.h"
#include "MainWindow.h"

#include "math.h"

#include "DevelopWindow.h"
#include "MoreWindow.h"

void CMainWindow::OnChange_Speed()
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
        this->textbox_send_Ma.SetWindowText(ff);
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

void CMainWindow::OnKillFocus_Speed()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Speed.LineLength(-1) == 0)
    {
        this->textbox_send_Speed.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChange_SlideSlip()
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

    l = this->textbox_send_SideSlip.LineLength(-1);
    if (l == 0)
        return;

    memset(s, 0, sizeof(s));
    memset(c, 0, sizeof(c));

    dw = this->textbox_send_SideSlip.GetSel();

    this->textbox_send_SideSlip.GetWindowText(c, sizeof(c)); // get data string with HEX

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
    this->textbox_send_SideSlip.SetWindowText(s);
    this->textbox_send_SideSlip.SetSel(HIWORD(dw) - 1, HIWORD(dw) - 1, FALSE);
}

void CMainWindow::OnKillFocus_SlideSlip()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_SideSlip.LineLength(-1) == 0)
    {
        this->textbox_send_SideSlip.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChange_Roll()
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

void CMainWindow::OnKillFocus_Roll()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Roll.LineLength(-1) == 0)
    {
        this->textbox_send_Roll.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChange_Pitch()
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

void CMainWindow::OnKillFocus_Pitch()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Pitch.LineLength(-1) == 0)
    {
        this->textbox_send_Pitch.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChange_High()
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

void CMainWindow::OnKillFocus_High()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_High.LineLength(-1) == 0)
    {
        this->textbox_send_High.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChange_Azimuth()
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

void CMainWindow::OnKillFocus_Azimuth()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChange_RealSpeed()
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

void CMainWindow::OnKillFocus_RealSpeed()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnKillFocus_Mach()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Ma.LineLength(-1) == 0)
    {
        this->textbox_send_Ma.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChange_Mach()
{
    // TODO: If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO: Add your control notification handler code here
}

void CMainWindow::OnChange_AirP()
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

void CMainWindow::OnKillFocus_AirP()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChange_Attack()
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

void CMainWindow::OnKillFocus_Attack()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChange_SpeedUD()
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

void CMainWindow::OnKillFocus_SpeedUD()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChange_HighR()
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

void CMainWindow::OnKillFocus_HighR()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChange_HighL()
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

void CMainWindow::OnKillFocus_HighL()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}

void CMainWindow::OnChange_NormalOverload()
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

void CMainWindow::OnKillFocus_NormalOverload()
{
    // TODO: Add your control notification handler code here
    if (this->textbox_send_Azimuth.LineLength(-1) == 0)
    {
        this->textbox_send_Azimuth.SetWindowText(TEXT("0"));
    }
}
