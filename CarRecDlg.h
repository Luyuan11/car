
// CarRecDlg.h: 头文件
//

#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>  //resize
#include<opencv2/highgui/highgui_c.h>   //CV_RGB2GRAY
#define license_len 8
#define template_len 10
using namespace std;
using namespace cv;
// CCarRecDlg 对话框
class CCarRecDlg : public CDialogEx
{
// 构造
public:
	CCarRecDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CMenu menu;          //目录
	vector<Mat> roiList;//用于储存分割出来的每个字符
	Mat plate;          //原车牌图
	Mat binImg;         //二值图
	int ding;
	int di;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CARREC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpen();
	afx_msg void OnBnClickedZffg();
	afx_msg void OnBnClickedQcby();
	afx_msg void OnBnClickedTqcp();
	afx_msg void OnBnClickedsearch();
	void train_svm();
	afx_msg void OnBnClickedZfsb();
	CEdit m_edit1;
	afx_msg void OnEnChangeEdit3();
	CEdit m_edit2;
	CEdit m_edit3;
	CEdit m_edit4;
	CEdit m_edit5;
	CEdit m_edit6;
	CEdit m_edit7;
	CStatic m_static3;
	CStatic m_static4;
	CStatic m_static5;
	CStatic m_static6;
	CStatic m_static7;
	CStatic m_static8;
	CStatic m_static9;
	CStatic m_static10;
	CStatic m_static11;
};
