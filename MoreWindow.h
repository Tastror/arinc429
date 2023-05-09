#ifndef _MOREWINDOW_H_
#define _MOREWINDOW_H_

#include "stdafx.h"
#include "resource.h"

class CMoreWindow : public CDialog
{
public:
	CMoreWindow();
	enum
	{
		IDD = IDD_More
	};

protected:
	afx_msg void On_RADIO_SelfSend();
	afx_msg void On_RADIO_Normal();
	afx_msg void On_RADIO_100K();
	afx_msg void On_RADIO_48K();
	afx_msg void On_RADIO_12p5K();
	afx_msg void On_RADIO_NoCheck();
	afx_msg void On_RADIO_OddCheck();
	afx_msg void On_RADIO_EvenCheck();

	DECLARE_MESSAGE_MAP();
	virtual void DoDataExchange(CDataExchange *pDX);
};

#endif