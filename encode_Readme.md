# 程序逻辑整理

## BOOL CMainWindow::OnInitDialog()  //demo

1. CDialog::OnInitDialog(); 父类的初始化函数
2. 加载系统菜单，不重要
2. 设置图标，调用 `SetIcon()` 函数
2. 设置四个输入通道和两个输出通道的触发等级为 `0`
2. 跳过之后内容

## Coding() 函数

在发送时调用 `coding()` 函数，这个逻辑大概就是把需要发送的东西依次填入

整理一下变量：