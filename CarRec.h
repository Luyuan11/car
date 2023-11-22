
// CarRec.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>  //resize
#include<opencv2/highgui/highgui_c.h>   //CV_RGB2GRAY
#include<opencv2/ml/ml.hpp>   //CV_RGB2GRAY
#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主符号


// CCarRecApp:
// 有关此类的实现，请参阅 CarRec.cpp
//

class CCarRecApp : public CWinApp
{
public:
	CCarRecApp();
	cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create();
	cv::Ptr<cv::ml::KNearest> knn_char = cv::ml::KNearest::create();
// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CCarRecApp theApp;
