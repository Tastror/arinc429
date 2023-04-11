# 架构与函数介绍

## 架构

首先是 GUI 部分。

主函数：`arinc429.cpp` 的 `BOOL CArinc429App::InitInstance()`。

`CArinc429App` 是在 `arinc429.h` 中定义的 `CWinApp`[<sup>1</sup>](#refer-anchor-1) 的子类，用于创建一个用户窗口。接下来的所有代码都是对这个窗口进行处理。

在 `InitInstance()` 的具体实现中，我们的内容显示是由 `CArinc429Dlg` 实现的。它定义在 `arinc429Dlg.h` 以及 `.cpp` 中，继承自 `CDialog`[<sup>2</sup>](#refer-anchor-2)，是用于在屏幕上显示对话框的基类。

接着是底层。

软硬件接口（用于调用驱动的 API）在 `DLL429D42_lib.h` 中，具体功能可以查看手册[<sup>3</sup>](#refer-anchor-3)。我们需要在 `CArinc429Dlg` 的实现中大量使用这些接口，来达到我们的最终目的。

本次任务的难点一方面在 GUI 本身，因为 `CWinApp` 我们可能都不太熟；另一方面就是底层 `DLL429D42_lib.h` 中库函数的使用和性质的把握。

## 函数介绍

> 以下回答均引用自 ChatGPT-3.5

`CWinApp::InitInstance()`

在 MFC 应用程序中，通常需要将一个 CDialog 对象作为应用程序主窗口，这时需要在 CWinApp 的 InitInstance 函数中创建并显示该 CDialog 对象，以便将其作为主窗口启动应用程序。

`CDialog::DoModal()`

启动对话框，将其作为模态对话框运行，直到用户关闭对话框才返回。

`CDialog::OnInitDialog()`

当对话框被创建时，OnInitDialog()被调用。该函数通常用于初始化控件的值、设置控件的属性等。

`CDialog::OnOK()`

当用户点击对话框的OK按钮时，将调用OnOK()。在该函数中，通常可以验证用户输入的数据是否正确，然后将数据传递给主程序。

`CDialog::OnCancel()`

当用户点击对话框的Cancel按钮时，将调用OnCancel()。在该函数中，通常可以释放对话框的资源，并将对话框关闭。

`CDialog::OnClose()`

当对话框被关闭时，将调用OnClose()。在该函数中，通常可以释放对话框的资源，并将对话框关闭。

`CDialog::EndDialog()`

该函数使对话框结束，并关闭对话框窗口。如果对话框作为模态对话框运行，则DoModal()函数将返回该函数的参数值。如果对话框作为非模态对话框运行，则窗口将关闭。

`CDialog::GetDlgItem()`

获取对话框中指定控件的句柄，可以通过该句柄对控件进行操作。

`CDialog::SetDlgItemText()`

设置对话框中指定控件的文本。

`CDialog::GetDlgItemText()`

获取对话框中指定控件的文本。

`CDialog::UpdateData()`

将对话框中的控件的值更新到关联的变量中。

`CDialog::DoDataExchange()`

在OnInitDialog()中，将对话框控件的值与变量进行关联。在UpdateData()中，将变量的值更新到对话框控件中。

关于库函数的用法，请参考手册[<sup>3</sup>](#refer-anchor-3)。

## 参考文献

<div id="refer-anchor-1"></div>

[1] [CWinApp 类](https://learn.microsoft.com/zh-cn/cpp/mfc/reference/cwinapp-class?view=msvc-170)

<div id="refer-anchor-2"></div>

[2] [CDialog 类](https://learn.microsoft.com/zh-cn/cpp/mfc/reference/cdialog-class?view=msvc-170)

<div id="refer-anchor-3"></div>

[3] [ARINC429-PCI-42 用户手册](./ARINC429-PCI-42%20manual.pdf)
