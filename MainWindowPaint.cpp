#include "stdafx.h"
#include "ARNIC429.h"
#include "MainWindow.h"

#include "math.h"

#include "DevelopWindow.h"
#include "MoreWindow.h"

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CMainWindow::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon（图标）
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        int screen_x_offset = 270, screen_y_offset = 0;
		int screen_x_strip = 10, screen_y_strip = 0;
		int screen_width = 760, screen_height = 600;

        int display_x_offset = 0, display_y_offset = 0;

        CDC *pMem = new CDC;
        CBitmap *pBmp = new CBitmap;
        CBitmap *pOldBmp;
        CDC *pDC = GetDC();
        CRect rectTemp(
            screen_x_strip + screen_x_offset,
            screen_y_strip + screen_y_offset,
            screen_x_strip + screen_width + screen_x_offset,
            screen_y_strip + screen_width + screen_y_offset
        );
        pMem->CreateCompatibleDC(pDC);
        pBmp->CreateCompatibleBitmap(pDC, rectTemp.Width(), rectTemp.Height());
        pOldBmp = pMem->SelectObject(pBmp);

        OnDraw_SkyRect(pMem);
        OnDraw_Fighter(
            display_x_offset, display_y_offset,
            205 + (int)data_receive_Pitch, 260 + (int)data_receive_Sideslip, pMem
        );
        OnDraw_High(display_x_offset, display_y_offset, data_receive_High, pMem);
        OnDraw_Speed(display_x_offset, display_y_offset, data_receive_Speed, pMem);
        OnDraw_HXJ(display_x_offset, display_y_offset, data_receive_Azimuth, pMem); // 方位角
        OnDraw_HGKD(display_x_offset, display_y_offset, data_receive_Roll, pMem);
        OnDraw_HG(display_x_offset, display_y_offset, -data_receive_Roll, data_receive_Pitch, pMem);

        pDC->BitBlt(rectTemp.left, rectTemp.top, rectTemp.Width(), rectTemp.Height(), pMem, 0, 0, SRCCOPY);
        pMem->SelectObject(pOldBmp);
        pBmp->DeleteObject();
        pMem->DeleteDC();

        CDialog::OnPaint();
    }
}

void CMainWindow::OnDraw_SkyRect(CDC *pDC)
{
    CRect rect(0, 0, 800, 600);
    CBrush brush;
    CDC dcBmp;                                // 定义并创建一个内存设备环境
    CBitmap bmpBackground;                    // 定义位图句柄
    bmpBackground.LoadBitmap(IDB_BG_Sky);     // 将位图资源绑定在位图句柄上
    brush.CreatePatternBrush(&bmpBackground); // 绑定在位图画刷上
    // brush.CreateSolidBrush(RGB(0, 0, 0));
    pDC->FillRect(rect, &brush);
}

// 机炮十字线和速度矢量
void CMainWindow::OnDraw_Fighter(int x_offset, int y_offset, int x, int y, CDC *pDC) // 机炮十字线和速度矢量
{

    CPen GreenPen, WhitePen;
    GreenPen.CreatePen(PS_SOLID, 2, RGB(0, 250, 0));
    WhitePen.CreatePen(PS_SOLID, 2, RGB(250, 250, 250));

    // poldPen =pDC->SelectObject(&WhitePen);
    // pDC->SetArcDirection(AD_CLOCKWISE);   //顺时针
    // pDC->Arc(CRect(30, 30, 150, 150), CPoint(30, 90), CPoint(90, 30));
    // pDC->Arc(CRect(375, 320, 495, 440), CPoint(495, 380), CPoint(435, 440));
    // pDC->SetArcDirection(AD_COUNTERCLOCKWISE);   //逆时针
    // pDC->Arc(CRect(30, 320, 150, 440), CPoint(30, 380), CPoint(90, 440));
    // pDC->Arc(CRect(375, 30, 495, 150), CPoint(495, 90), CPoint(435, 30));
    // pDC->MoveTo(30, 90);
    // pDC->LineTo(30, 380);
    // pDC->MoveTo(495, 90);
    // pDC->LineTo(495,380);//直线边界

    CPen *poldPen = pDC->SelectObject(&WhitePen);
    pDC->MoveTo(260, 190);
    pDC->LineTo(260, 220);
    pDC->MoveTo(245, 205);
    pDC->LineTo(275, 205);
    pDC->Arc(y - radius, x - radius, y + radius, x + radius, y - radius, x - radius, y - radius, x - radius);
    pDC->MoveTo(y - radius, x);
    pDC->LineTo(y - radius - 10, x);
    pDC->MoveTo(y + radius, x);
    pDC->LineTo(y + radius + 10, x);
    pDC->MoveTo(y, x - radius);
    pDC->LineTo(y, x - radius - 10);

    if (data_receive_High <= data_receive_HighL)
    {
        pDC->MoveTo(y - 20, x - 5);
        pDC->LineTo(y - 20, x + 10);
        pDC->MoveTo(y - 20, x + 10);
        pDC->LineTo(y - 1, x + 10);
        pDC->MoveTo(y + 1, x + 10);
        pDC->LineTo(y + 20, x + 10);
        pDC->MoveTo(y + 20, x + 10);
        pDC->LineTo(y + 20, x - 5);
    }

    pDC->SelectObject(poldPen);
}

// 画高度
void CMainWindow::OnDraw_High(int x_offset, int y_offset, int x, CDC *pDC)
{
    char c[80];
    int a;
    unsigned int ad;
    unsigned int High_cas, High_casD, High_casU;
    int i, j;
    int text_offset = 7;

    CPen pNewPen;
    pNewPen.CreatePen(PS_SOLID, 2, RGB(0, 250, 0));
    CPen *poldPen = pDC->SelectObject(&pNewPen);
    pDC->SetTextColor(RGB(0, 250, 0));
    pDC->SetBkMode(TRANSPARENT);

    pDC->MoveTo(390, 205);
    pDC->LineTo(420, 205);
    pDC->TextOutA(431, 356, _T("FY.time_counter"));
    pDC->TextOutA(431, 376, _T("NAV GPS"));
    pDC->TextOutA(400, 208, _T("U"));
    itoa(data_receive_SpeedUD, c, 10);
    if (data_receive_SpeedUD < 10)
    {
        pDC->TextOutA(400, 188, c);
    }
    else if (data_receive_SpeedUD < 100)
    {
        pDC->TextOutA(396, 36, c);
    }
    else if (data_receive_SpeedUD < 1000)
    {
        pDC->TextOutA(392, 36, c);
    }
    else if (data_receive_SpeedUD < 10000)
    {
        pDC->TextOutA(388, 36, c);
    }
    else
    {
        pDC->TextOutA(384, 36, c);
    }
    pDC->TextOutA(400, 188, c);

    gcvt(data_receive_AirP, 4, c);
    pDC->TextOutA(431, 16, _T("BP"));
    pDC->TextOutA(451, 16, c);

    pDC->TextOutA(431, 36, _T("H"));

    itoa(x, c, 10); // 整数转变为字符串
    if (x < 10)
    {
        pDC->TextOutA(451, 36, c);
    }
    else if (x < 100)
    {
        pDC->TextOutA(447, 36, c);
    }
    else if (x < 1000)
    {
        pDC->TextOutA(443, 36, c);
    }
    else if (x < 10000)
    {
        pDC->TextOutA(439, 36, c);
    }
    else
    {
        pDC->TextOutA(435, 36, c);
    }

    a = x % 500;
    ad = a / 10;

    High_cas = x / 500 * 500;

    itoa(High_cas, c, 10);
    pDC->TextOutA(450, 198 + ad, c);
    pDC->MoveTo(425, 205 + ad);
    pDC->LineTo(445, 205 + ad);

    for (i = 1; i < 5; i++)
    {
        j = i * 10;
        pDC->MoveTo(425, 205 + ad - j);
        pDC->LineTo(435, 205 + ad - j);
    }

    for (i = 1; i < 15; i++)
    {
        j = i * 10;
        pDC->MoveTo(425, 205 + ad - j - (ad / 10) * 10);
        pDC->LineTo(435, 205 + ad - j - (ad / 10) * 10);
    }
    for (i = 1; i < 15; i++)
    {
        j = i * 10;
        pDC->MoveTo(425, 205 + ad + j - (ad / 10) * 10);
        pDC->LineTo(435, 205 + ad + j - (ad / 10) * 10);
    }

    if (a < 100)
    {
        pDC->MoveTo(425, 205 + ad - 50);
        pDC->LineTo(445, 205 + ad - 50);
        High_casU = High_cas + 500;
        itoa(High_casU, c, 10);
        pDC->TextOutA(450, 205 + ad - 50 - text_offset, c);

        pDC->MoveTo(425, 205 + ad - 100);
        pDC->LineTo(445, 205 + ad - 100);
        High_casU = High_cas + 1000;
        itoa(High_casU, c, 10);
        pDC->TextOutA(450, 205 + ad - 100 - text_offset, c);
    }
    else
    {
        pDC->MoveTo(425, 205 + ad - 50);
        pDC->LineTo(445, 205 + ad - 50);
        High_casU = High_cas + 500;
        itoa(High_casU, c, 10);
        pDC->TextOutA(450, 205 + ad - 50 - text_offset, c);

        pDC->MoveTo(425, 205 + ad - 100);
        pDC->LineTo(445, 205 + ad - 100);
        High_casU = High_cas + 1000;
        itoa(High_casU, c, 10);
        pDC->TextOutA(450, 205 + ad - 100 - text_offset, c);

        pDC->MoveTo(425, 205 + ad - 150);
        pDC->LineTo(445, 205 + ad - 150);
        High_casU = High_cas + 1500;
        itoa(High_casU, c, 10);
        pDC->TextOutA(450, 205 + ad - 150 - text_offset, c);
    }
    if (a > 400)
    {
        pDC->MoveTo(435, 205 + ad + 50);
        pDC->LineTo(445, 205 + ad + 50);
        High_casD = High_cas - 500;
        itoa(High_casD, c, 10);
        pDC->TextOutA(450, 205 + ad + 50 - text_offset, c);
    }
    else
    {
        pDC->MoveTo(435, 205 + ad + 50);
        pDC->LineTo(445, 205 + ad + 50);
        High_casD = High_cas - 500;
        itoa(High_casD, c, 10);
        pDC->TextOutA(450, 205 + ad + 50 - text_offset, c);

        pDC->MoveTo(425, 205 + ad + 100);
        pDC->LineTo(445, 205 + ad + 100);
        High_casD = High_cas - 1000;
        itoa(High_casD, c, 10);
        pDC->TextOutA(450, 205 + ad + 100 - text_offset, c);
    }
    pDC->SelectObject(poldPen);
}

// 画速度
void CMainWindow::OnDraw_Speed(int x_offset, int y_offset, int x, CDC *pDC)
{
    char c[80];
    int a;
    unsigned int ad;
    unsigned int V_cas, V_casD, V_casU;
    int i, j;
    int text_offset = 7;
    int amp = 2;

    CPen pNewPen;
    pNewPen.CreatePen(PS_SOLID, 2, RGB(0, 250, 0));
    CPen *poldPen = pDC->SelectObject(&pNewPen);
    pDC->SetTextColor(RGB(0, 255, 0));
    pDC->SetBkMode(TRANSPARENT);

    pDC->MoveTo(100, 205);
    pDC->LineTo(130, 205);

    pDC->TextOutA(52, 376, _T(".CCIL"));

    gcvt(data_receive_Mach, 2, c);
    pDC->TextOutA(52, 36, _T("Ma"));
    pDC->TextOutA(72, 36, c);

    gcvt(data_receive_NormalOverload, 2, c);
    pDC->TextOutA(52, 356, _T("N"));
    pDC->TextOutA(72, 356, c);

    gcvt(data_receive_Attack, 4, c);
    pDC->TextOutA(112, 208, _T("A"));
    pDC->TextOutA(112, 188, c);

    pDC->TextOutA(52, 16, _T("time_counter"));
    itoa(x, c, 10); // x：欲转换的数据；c:目标字符串的地址；10：十进制
    if (x < 10)
    {
        pDC->TextOutA(72, 16, c);
    }
    else if (x < 100)
    {
        pDC->TextOutA(72, 16, c);
    }
    else if (x < 1000)
    {
        pDC->TextOutA(68, 16, c);
    }
    else
    {
        pDC->TextOutA(68, 16, c);
    }

    a = x % 25;
    ad = a / 5;
    V_cas = x / 25 * 25;

    itoa(V_cas, c, 10);
    if (x < 10)
    {
        pDC->TextOutA(64, 198 + a * amp, c);
    }
    else if (x < 100)
    {
        pDC->TextOutA(56, 198 + a * amp, c);
    }
    else if (x < 1000)
    {
        pDC->TextOutA(48, 198 + a * amp, c);
    }
    else
    {
        pDC->TextOutA(40, 198 + a * amp, c);
    }

    pDC->MoveTo(95, 205 + a * amp);
    pDC->LineTo(75, 205 + a * amp);

    for (i = 1; i < 5; i++)
    {
        j = i * 5;
        pDC->MoveTo(95, 205 + (a - j) * amp);
        pDC->LineTo(85, 205 + (a - j) * amp);
    }

    for (i = 1; i < 15; i++)
    {
        j = i * 5;
        pDC->MoveTo(95, 205 + (a - j - ad * 5) * amp);
        pDC->LineTo(85, 205 + (a - j - ad * 5) * amp);
    }
    for (i = 1; i < 15; i++)
    {
        j = i * 5;
        pDC->MoveTo(95, 205 + (a + j - ad * 5) * amp);
        pDC->LineTo(85, 205 + (a + j - ad * 5) * amp);
    }

    if (a < 5)
    {
        pDC->MoveTo(95, 205 + (a - 25) * amp);
        pDC->LineTo(75, 205 + (a - 25) * amp);
        V_casU = V_cas + 25;
        itoa(V_casU, c, 10);
        if (x < 10)
        {
            pDC->TextOutA(56, 205 + (a - 25) * amp - text_offset, c);
        }
        else if (x < 100)
        {
            pDC->TextOutA(48, 205 + (a - 25) * amp - text_offset, c);
        }
        else if (x < 1000)
        {
            pDC->TextOutA(40, 205 + (a - 25) * amp - text_offset, c);
        }
        else
        {
            pDC->TextOutA(32, 205 + (a - 25) * amp - text_offset, c);
        }

        pDC->MoveTo(95, 205 + (a - 50) * amp);
        pDC->LineTo(75, 205 + (a - 50) * amp);
        V_casU = V_cas + 50;
        itoa(V_casU, c, 10);
        if (x < 10)
        {
            pDC->TextOutA(56, 205 + (a - 50) * amp - text_offset, c);
        }
        else if (x < 100)
        {
            pDC->TextOutA(48, 205 + (a - 50) * amp - text_offset, c);
        }
        else if (x < 1000)
        {
            pDC->TextOutA(40, 205 + (a - 50) * amp - text_offset, c);
        }
        else
        {
            pDC->TextOutA(32, 205 + (a - 50) * amp - text_offset, c);
        }
    }
    else
    {
        pDC->MoveTo(95, 205 + (a - 25) * amp);
        pDC->LineTo(75, 205 + (a - 25) * amp);
        V_casU = V_cas + 25;
        itoa(V_casU, c, 10);
        if (x < 10)
        {
            pDC->TextOutA(56, 205 + (a - 25) * amp - text_offset, c);
        }
        else if (x < 100)
        {
            pDC->TextOutA(48, 205 + (a - 25) * amp - text_offset, c);
        }
        else if (x < 1000)
        {
            pDC->TextOutA(40, 205 + (a - 25) * amp - text_offset, c);
        }
        else
        {
            pDC->TextOutA(32, 205 + (a - 25) * amp - text_offset, c);
        }

        pDC->MoveTo(95, 205 + (a - 50) * amp);
        pDC->LineTo(75, 205 + (a - 50) * amp);
        V_casU = V_cas + 50;
        itoa(V_casU, c, 10);
        if (x < 10)
        {
            pDC->TextOutA(56, 205 + (a - 50) * amp - text_offset, c);
        }
        else if (x < 100)
        {
            pDC->TextOutA(48, 205 + (a - 50) * amp - text_offset, c);
        }
        else if (x < 1000)
        {
            pDC->TextOutA(40, 205 + (a - 50) * amp - text_offset, c);
        }
        else
        {
            pDC->TextOutA(32, 205 + (a - 50) * amp - text_offset, c);
        }

        pDC->MoveTo(95, 205 + (a - 75) * amp);
        pDC->LineTo(75, 205 + (a - 75) * amp);
        V_casU = V_cas + 75;
        itoa(V_casU, c, 10);
        if (x < 10)
        {
            pDC->TextOutA(56, 205 + (a - 75) * amp - text_offset, c);
        }
        else if (x < 100)
        {
            pDC->TextOutA(48, 205 + (a - 75) * amp - text_offset, c);
        }
        else if (x < 1000)
        {
            pDC->TextOutA(40, 205 + (a - 75) * amp - text_offset, c);
        }
        else
        {
            pDC->TextOutA(32, 205 + (a - 75) * amp - text_offset, c);
        }
    }
    if (a > 20)
    {
        pDC->MoveTo(95, 205 + (a + 25) * amp);
        pDC->LineTo(75, 205 + (a + 25) * amp);
        V_casD = V_cas - 25;
        itoa(V_casD, c, 10);
        if (x < 10)
        {
            pDC->TextOutA(56, 205 + (a + 25) * amp - text_offset, c);
        }
        else if (x < 100)
        {
            pDC->TextOutA(48, 205 + (a + 25) * amp - text_offset, c);
        }
        else if (x < 1000)
        {
            pDC->TextOutA(40, 205 + (a + 25) * amp - text_offset, c);
        }
        else
        {
            pDC->TextOutA(32, 205 + (a + 25) * amp - text_offset, c);
        }
    }
    else
    {
        pDC->MoveTo(95, 205 + (a + 25) * amp);
        pDC->LineTo(75, 205 + (a + 25) * amp);
        V_casD = V_cas - 25;
        itoa(V_casD, c, 10);
        if (x < 10)
        {
            pDC->TextOutA(50, 205 + (a + 25) * amp - text_offset, c);
        }
        else if (x < 100)
        {
            pDC->TextOutA(50, 205 + (a + 25) * amp - text_offset, c);
        }
        else if (x < 1000)
        {
            pDC->TextOutA(42, 205 + (a + 25) * amp - text_offset, c);
        }
        else
        {
            pDC->TextOutA(34, 205 + (a + 25) * amp - text_offset, c);
        }

        pDC->MoveTo(95, 205 + (a + 50) * amp);
        pDC->LineTo(75, 205 + (a + 50) * amp);
        V_casD = V_cas - 50;
        itoa(V_casD, c, 10);
        if (x < 10)
        {
            pDC->TextOutA(50, 205 + (a + 50) * amp - text_offset, c);
        }
        else if (x < 100)
        {
            pDC->TextOutA(50, 205 + (a + 50) * amp - text_offset, c);
        }
        else if (x < 1000)
        {
            pDC->TextOutA(42, 205 + (a + 50) * amp - text_offset, c);
        }
        else
        {
            pDC->TextOutA(34, 205 + (a + 50) * amp - text_offset, c);
        }
    }
    pDC->SelectObject(poldPen);
}

// 画方位角
void CMainWindow::OnDraw_HXJ(int x_offset, int y_offset, double x, CDC *pDC)
{
    // CDC *pDC = GetDC();
    int HX_int;
    int HX_cas, HX_casL;
    unsigned int a;
    unsigned int al;
    int i, j;
    unsigned int amp = 4;
    char c[80];

    pDC->SetTextColor(RGB(0, 250, 0));
    pDC->SetBkMode(TRANSPARENT);
    CPen pNewPen;
    pNewPen.CreatePen(PS_SOLID, 2, RGB(0, 250, 0));
    CPen *poldPen = pDC->SelectObject(&pNewPen);

    HX_int = (int)x;
    pDC->MoveTo(260, 80);
    pDC->LineTo(260, 60);

    a = x * 4;
    HX_int = (int)a;
    HX_cas = HX_int / 80 * 20;
    a = HX_int % 80;

    pDC->MoveTo(260 - a, 55);
    pDC->LineTo(260 - a, 40);

    al = a / 25; // 左端已画出的线数，范围（0~3）
    for (i = -6; i < 7; i++)
    {
        j = i * 5;
        pDC->MoveTo(260 - a + (al * 5 - j) * amp, 55);
        pDC->LineTo(260 - a + (al * 5 - j) * amp, 45);
    }

    for (i = -1; i < 2; i++)
    {
        pDC->MoveTo(260 - a + 20 * i * amp, 55);
        pDC->LineTo(260 - a + 20 * i * amp, 35);
        if (HX_cas == 0 && i == -2)
        {
            HX_casL = 320;
        }
        else if (HX_cas == 0 && i == -1)
        {
            HX_casL = 340;
        }
        else if (HX_cas == 20 && i == -2)
        {
            HX_casL = 340;
        }
        else if (HX_cas == 340 && i == 1)
        {
            HX_casL = 0;
        }
        else if (HX_cas == 340 && i == 2)
        {
            HX_casL = 20;
        }
        else if (HX_cas == 320 && i == 2)
        {
            HX_casL = 0;
        }
        else
        {
            HX_casL = HX_cas + 20 * i;
        }
        itoa(HX_casL, c, 10);
        if (HX_casL < 10)
        {
            pDC->TextOutA(260 - a + 20 * i * amp - 4, 17, c);
        }
        else if (HX_casL < 100)
        {
            pDC->TextOutA(260 - a + 20 * i * amp - 8, 17, c);
        }
        else
        {
            pDC->TextOutA(260 - a + 20 * i * amp - 12, 17, c);
        }
    }
    pDC->SelectObject(poldPen);
}

// 画滚转角
void CMainWindow::OnDraw_HGKD(int x_offset, int y_offset, double HGJ, CDC *pDC)
{
    // CDC *pDC = GetDC();
    char c[80];
    int i;
    int R = 215;
    int r = 185;
    int dr = 200;
    double x, y;
    double theta;
    int x1, y1;
    int text;

    CPen pNewPen;
    pNewPen.CreatePen(PS_SOLID, 2, RGB(0, 250, 0));
    CPen *poldPen = pDC->SelectObject(&pNewPen);

    HGJ = HGJ / 180 * PI;
    for (i = 0; i < 5; i++)
    {
        x = 260 + R * cos(PI / 3 + i * PI / 12);
        y = 205 + R * sin(PI / 3 + i * PI / 12);
        x1 = (int)x;
        y1 = (int)y;
        pDC->MoveTo(x1, y1);
        x = 260 + r * cos(PI / 3 + i * PI / 12);
        y = 205 + r * sin(PI / 3 + i * PI / 12);
        x1 = (int)x;
        y1 = (int)y;
        pDC->LineTo(x1, y1);
    }
    itoa(-180, c, 10);
    pDC->TextOutA(335, 345, c);
    itoa(-90, c, 10);
    pDC->TextOutA(293, 365, c);
    itoa(0, c, 10);
    pDC->TextOutA(255, 370, c);
    itoa(90, c, 10);
    pDC->TextOutA(205, 365, c);
    itoa(180, c, 10);
    pDC->TextOutA(155, 345, c);
    for (i = 0; i < 13; i++)
    {
        x = 260 + R * cos(PI / 3 + i * PI / 36);
        y = 205 + R * sin(PI / 3 + i * PI / 36);
        x1 = (int)x;
        y1 = (int)y;
        pDC->MoveTo(x1, y1);
        x = 260 + dr * cos(PI / 3 + i * PI / 36);
        y = 205 + dr * sin(PI / 3 + i * PI / 36);
        x1 = (int)x;
        y1 = (int)y;
        pDC->LineTo(x1, y1);
    }

    x = 260 + (R + 5) * cos(PI / 2 + HGJ / 6);
    y = 205 + (R + 5) * sin(PI / 2 + HGJ / 6);
    x1 = (int)(x + 0.5);
    y1 = (int)(y + 0.5);
    pDC->MoveTo(x1, y1);

    x = 252 - 260;
    y = 435 - 205;
    R = sqrt(x * x + y * y);
    theta = atan(x / y);
    x = 260 + R * cos(PI / 2 + HGJ / 6 + theta);
    y = 205 + R * sin(PI / 2 + HGJ / 6 + theta);
    x1 = (int)(x + 0.5);
    y1 = (int)(y + 0.5);
    pDC->LineTo(x1, y1);

    x = 268 - 260;
    y = 435 - 205;
    R = sqrt(x * x + y * y);
    theta = atan(x / y);
    x = 260 + R * cos(PI / 2 + HGJ / 6 + theta);
    y = 205 + R * sin(PI / 2 + HGJ / 6 + theta);
    x1 = (int)(x + 0.5);
    y1 = (int)(y + 0.5);
    pDC->LineTo(x1, y1);

    y = 425 - 205;
    R = (int)y;
    x = 260 + R * cos(PI / 2 + HGJ / 6);
    y = 205 + R * sin(PI / 2 + HGJ / 6);
    x1 = (int)(x + 0.5);
    y1 = (int)(y + 0.5);
    pDC->LineTo(x1, y1);
    pDC->SelectObject(poldPen);
}

void CMainWindow::OnDraw_HG(int x_offset, int y_offset, double HGJ, double FYJ, CDC *pDC)
{
    char c[80];
    int a;
    int i, j, k;
    double x, y, R;
    int x1, y1;
    double theta;
    int FYJ_int;
    int FYJ_cas;
    int amp = 20;
    int text_offset = 12;
    CPen pNewPen;
    pNewPen.CreatePen(PS_SOLID, 2, RGB(0, 250, 0));
    CPen *poldPen = pDC->SelectObject(&pNewPen);
    pDC->SetTextColor(RGB(0, 250, 0));
    pDC->SetBkMode(TRANSPARENT);

    CFont font;
    LOGFONT lf;
    memset(&lf, 0, sizeof(LOGFONT)); // zero out structure
    // 将&if中当前位置后面的sizeof个字节 （typedef unsigned int size_t ）用 0 替换并返回 lf。
    lf.lfHeight = 17; // request a 12-pixel-height font
    lf.lfEscapement = HGJ * 10;
    VERIFY(font.CreateFontIndirect(&lf)); // create the font
    pDC->SelectObject(&font);

    HGJ = -HGJ / 180 * PI;

    FYJ_int = (int)FYJ;
    FYJ_cas = FYJ_int / 5 * 5;
    FYJ_int = FYJ * amp;
    a = FYJ_int % 100;

    for (i = -1; i < 2; i++)
    {
        j = i * 5;
        if (FYJ_cas + j >= 0)
        {
            x = 240 - 260;
            y = -a + j * amp;
            R = x * x + y * y;
            R = sqrt(R);
            theta = atan(y / x);
            if (x < 0 && y < 0)
            {
                theta = theta - PI;
            }
            else if (x < 0 && y >= 0)
            {
                theta = theta + PI;
            }
            x = 260 + R * cos(theta + HGJ);
            y = 205 + R * sin(theta + HGJ);
            x1 = (int)(x + 0.5);
            y1 = (int)(y + 0.5);
            pDC->MoveTo(x1, y1);

            x = 180 - 260;
            y = -a + j * amp;
            R = x * x + y * y;
            R = sqrt(R);
            theta = atan(y / x);
            if (x < 0 && y < 0)
            {
                theta = theta - PI;
            }
            else if (x < 0 && y >= 0)
            {
                theta = theta + PI;
            }
            x = 260 + R * cos(theta + HGJ);
            y = 205 + R * sin(theta + HGJ);
            x1 = (int)(x + 0.5);
            y1 = (int)(y + 0.5);
            pDC->LineTo(x1, y1);

            x = 180 - 260;
            y = -a + j * amp - 10;
            R = x * x + y * y;
            R = sqrt(R);
            theta = atan(y / x);
            if (x < 0 && y < 0)
            {
                theta = theta - PI;
            }
            else if (x < 0 && y >= 0)
            {
                theta = theta + PI;
            }
            x = 260 + R * cos(theta + HGJ);
            y = 205 + R * sin(theta + HGJ);
            x1 = (int)(x + 0.5);
            y1 = (int)(y + 0.5);
            pDC->LineTo(x1, y1);

            x = 280 - 260;
            y = -a + j * amp;
            R = x * x + y * y;
            R = sqrt(R);
            theta = atan(y / x);
            if (x < 0 && y < 0)
            {
                theta = theta - PI;
            }
            else if (x < 0 && y >= 0)
            {
                theta = theta + PI;
            }
            x = 260 + R * cos(theta + HGJ);
            y = 205 + R * sin(theta + HGJ);
            x1 = (int)(x + 0.5);
            y1 = (int)(y + 0.5);
            pDC->MoveTo(x1, y1);

            x = 340 - 260;
            y = -a + j * amp;
            R = x * x + y * y;
            R = sqrt(R);
            theta = atan(y / x);
            if (x < 0 && y < 0)
            {
                theta = theta - PI;
            }
            else if (x < 0 && y >= 0)
            {
                theta = theta + PI;
            }
            x = 260 + R * cos(theta + HGJ);
            y = 205 + R * sin(theta + HGJ);
            x1 = (int)(x + 0.5);
            y1 = (int)(y + 0.5);
            pDC->LineTo(x1, y1);

            x = 340 - 260;
            y = -a + j * amp - 10;
            R = x * x + y * y;
            R = sqrt(R);
            theta = atan(y / x);
            if (x < 0 && y < 0)
            {
                theta = theta - PI;
            }
            else if (x < 0 && y >= 0)
            {
                theta = theta + PI;
            }
            x = 260 + R * cos(theta + HGJ);
            y = 205 + R * sin(theta + HGJ);
            x1 = (int)(x + 0.5);
            y1 = (int)(y + 0.5);
            pDC->LineTo(x1, y1);
        }
        else
        {
            x = 240 - 260;
            y = -a + j * amp;
            R = x * x + y * y;
            R = sqrt(R);
            theta = atan(y / x);
            if (x < 0 && y < 0)
            {
                theta = theta - PI;
            }
            else if (x < 0 && y >= 0)
            {
                theta = theta + PI;
            }
            x = 260 + R * cos(theta + HGJ);
            y = 205 + R * sin(theta + HGJ);
            x1 = (int)(x + 0.5);
            y1 = (int)(y + 0.5);
            pDC->MoveTo(x1, y1);

            for (k = 1; k <= 30; k = k + 2)
            {
                x = 240 - k * 2 - 260;
                y = -a + j * amp;
                R = x * x + y * y;
                R = sqrt(R);
                theta = atan(y / x);
                if (x < 0 && y < 0)
                {
                    theta = theta - PI;
                }
                else if (x < 0 && y >= 0)
                {
                    theta = theta + PI;
                }
                x = 260 + R * cos(theta + HGJ);
                y = 205 + R * sin(theta + HGJ);
                x1 = (int)(x + 0.5);
                y1 = (int)(y + 0.5);
                pDC->LineTo(x1, y1);

                x = 240 - (k + 1) * 2 - 260;
                y = -a + j * amp;
                R = x * x + y * y;
                R = sqrt(R);
                theta = atan(y / x);
                if (x < 0 && y < 0)
                {
                    theta = theta - PI;
                }
                else if (x < 0 && y >= 0)
                {
                    theta = theta + PI;
                }
                x = 260 + R * cos(theta + HGJ);
                y = 205 + R * sin(theta + HGJ);
                x1 = (int)(x + 0.5);
                y1 = (int)(y + 0.5);
                pDC->MoveTo(x1, y1);
            }

            x = 180 - 260;
            y = -a + j * amp - 10;
            R = x * x + y * y;
            R = sqrt(R);
            theta = atan(y / x);
            if (x < 0 && y < 0)
            {
                theta = theta - PI;
            }
            else if (x < 0 && y >= 0)
            {
                theta = theta + PI;
            }
            x = 260 + R * cos(theta + HGJ);
            y = 205 + R * sin(theta + HGJ);
            x1 = (int)(x + 0.5);
            y1 = (int)(y + 0.5);
            pDC->LineTo(x1, y1);

            x = 280 - 260;
            y = -a + j * amp;
            R = x * x + y * y;
            R = sqrt(R);
            theta = atan(y / x);
            if (x < 0 && y < 0)
            {
                theta = theta - PI;
            }
            else if (x < 0 && y >= 0)
            {
                theta = theta + PI;
            }
            x = 260 + R * cos(theta + HGJ);
            y = 205 + R * sin(theta + HGJ);
            x1 = (int)(x + 0.5);
            y1 = (int)(y + 0.5);
            pDC->MoveTo(x1, y1);

            for (k = 1; k <= 30; k = k + 2)
            {
                x = 280 + k * 2 - 260;
                y = -a + j * amp;
                R = x * x + y * y;
                R = sqrt(R);
                theta = atan(y / x);
                if (x < 0 && y < 0)
                {
                    theta = theta - PI;
                }
                else if (x < 0 && y >= 0)
                {
                    theta = theta + PI;
                }
                x = 260 + R * cos(theta + HGJ);
                y = 205 + R * sin(theta + HGJ);
                x1 = (int)(x + 0.5);
                y1 = (int)(y + 0.5);
                pDC->LineTo(x1, y1);

                x = 280 + (k + 1) * 2 - 260;
                y = -a + j * amp;
                R = x * x + y * y;
                R = sqrt(R);
                theta = atan(y / x);
                if (x < 0 && y < 0)
                {
                    theta = theta - PI;
                }
                else if (x < 0 && y >= 0)
                {
                    theta = theta + PI;
                }
                x = 260 + R * cos(theta + HGJ);
                y = 205 + R * sin(theta + HGJ);
                x1 = (int)(x + 0.5);
                y1 = (int)(y + 0.5);
                pDC->MoveTo(x1, y1);
            }

            x = 340 - 260;
            y = -a + j * amp - 10;
            R = x * x + y * y;
            R = sqrt(R);
            theta = atan(y / x);
            if (x < 0 && y < 0)
            {
                theta = theta - PI;
            }
            else if (x < 0 && y >= 0)
            {
                theta = theta + PI;
            }
            x = 260 + R * cos(theta + HGJ);
            y = 205 + R * sin(theta + HGJ);
            x1 = (int)(x + 0.5);
            y1 = (int)(y + 0.5);
            pDC->LineTo(x1, y1);
        }
        itoa(FYJ_cas + j, c, 10);

        // 左侧俯仰角字符
        x = 160 - 260;
        y = -a + j * amp - text_offset;
        R = x * x + y * y;
        R = sqrt(R);
        theta = atan(y / x);
        if (x < 0 && y < 0)
        {
            theta = theta - PI;
        }
        else if (x < 0 && y >= 0)
        {
            theta = theta + PI;
        }
        x = 260 + R * cos(theta + HGJ);
        y = 205 + R * sin(theta + HGJ);
        x1 = (int)(x + 0.5);
        y1 = (int)(y + 0.5);
        pDC->TextOutA(x1, y1, c);

        // 右侧俯仰角字符
        x = 350 - 260;
        y = -a + j * amp - text_offset;
        R = x * x + y * y;
        R = sqrt(R);
        theta = atan(y / x);
        if (x < 0 && y < 0)
        {
            theta = theta - PI;
        }
        else if (x < 0 && y >= 0)
        {
            theta = theta + PI;
        }
        x = 260 + R * cos(theta + HGJ);
        y = 205 + R * sin(theta + HGJ);
        x1 = (int)(x + 0.5);
        y1 = (int)(y + 0.5);
        pDC->TextOutA(x1, y1, c);
    }
    pDC->SelectObject(poldPen);
}
