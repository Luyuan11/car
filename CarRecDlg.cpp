
// CarRecDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "CarRec.h"
#include "CarRecDlg.h"
#include "afxdialogex.h"
#include "LPR.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>  //resize
#include<opencv2/highgui/highgui_c.h>   //CV_RGB2GRAY
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace cv;
using namespace std;
using namespace ml;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框


char ad[128] = { 0 };

const char id[] = { '0','1','2','3','4',
	'5','6','7','8','9',
	'A','B','C','D','E',
	'F','G','H','J','K',
	'L','M','N','P','Q',
	'R','S','T','U','V',
	'W','X','Y','Z' };
wchar_t xx[][128] = { {L"藏"}, {L"川"} , {L"鄂"}, {L"甘"}, {L"赣"},
	{L"贵"}, {L"桂"} , {L"黑"}, {L"沪"}, {L"吉"},
	{L"冀"}, {L"津"} , {L"晋"}, {L"京"}, {L"辽"},
	{L"鲁"}, {L"蒙"} , {L"闽"}, {L"宁"}, {L"青"},
	{L"琼"}, {L"陕"} , {L"苏"}, {L"皖"}, {L"湘"},
	{L"新"}, {L"渝"} , {L"豫"}, {L"粤"}, {L"云"},
	{L"浙"} };


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCarRecDlg 对话框



CCarRecDlg::CCarRecDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CARREC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCarRecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_EDIT4, m_edit4);
	DDX_Control(pDX, IDC_EDIT5, m_edit5);
	DDX_Control(pDX, IDC_EDIT6, m_edit6);
	DDX_Control(pDX, IDC_EDIT7, m_edit7);
	DDX_Control(pDX, IDC_STATIC3, m_static3);
	DDX_Control(pDX, IDC_STATIC4, m_static4);
	DDX_Control(pDX, IDC_STATIC5, m_static5);
	DDX_Control(pDX, IDC_STATIC6, m_static6);
	DDX_Control(pDX, IDC_STATIC7, m_static7);
	DDX_Control(pDX, IDC_STATIC8, m_static8);
	DDX_Control(pDX, IDC_STATIC9, m_static9);
	DDX_Control(pDX, IDC_STATIC10, m_static10);
	DDX_Control(pDX, IDC_STATIC11, m_static11);
}

BEGIN_MESSAGE_MAP(CCarRecDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &CCarRecDlg::OnOpen)
	ON_BN_CLICKED(IDC_ZFFG, &CCarRecDlg::OnBnClickedZffg)
	ON_BN_CLICKED(IDC_QCBY, &CCarRecDlg::OnBnClickedQcby)
	ON_BN_CLICKED(IDC_TQCP, &CCarRecDlg::OnBnClickedTqcp)
	ON_BN_CLICKED(IDC_search, &CCarRecDlg::OnBnClickedsearch)
	ON_BN_CLICKED(IDC_ZFSB, &CCarRecDlg::OnBnClickedZfsb)
	ON_EN_CHANGE(IDC_EDIT3, &CCarRecDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CCarRecDlg 消息处理程序

BOOL CCarRecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CFont my_Font;//定义新的字体实例
	my_Font.CreatePointFont(320, L"Arial");//创建字体和大小
	m_edit1.SetFont(&my_Font);
	m_edit2.SetFont(&my_Font);
	m_edit3.SetFont(&my_Font);
	m_edit4.SetFont(&my_Font);
	m_edit5.SetFont(&my_Font);
	m_edit6.SetFont(&my_Font);
	m_edit7.SetFont(&my_Font);

	m_static3.SetFont(&my_Font);
	m_static4.SetFont(&my_Font);
	m_static5.SetFont(&my_Font);
	m_static6.SetFont(&my_Font);
	m_static7.SetFont(&my_Font);
	m_static8.SetFont(&my_Font);
	m_static9.SetFont(&my_Font);
	m_static10.SetFont(&my_Font);
	m_static11.SetFont(&my_Font);
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	//添加目录
	menu.LoadMenuW(IDR_MENU1);//菜单栏ID
	SetMenu(&menu);


	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	
	
	
	// WCHAR 转换为 std::string
	
	Mat traindata_char, trainlabel_char;
	int k_char = 32;
	for (int i = 0; i < 31; i++)
	{
		string pre = "data2\\train_28_28\\";
		LPCWSTR pwszSrc = xx[i];

		int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
		//if (nLen <= 0)
		//	return std::string("");

		char* pszDst = new char[nLen];
		//if (NULL == pszDst)
		//	return string("");

		WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
		pszDst[nLen - 1] = 0;

		std::string strTmp(pszDst);
		delete[] pszDst;

		

		pre += strTmp;
		pre += "\\";
		pre += strTmp;
		pre += "_";
		for (int j = 1;; j++)
		{
			string path(pre);

			path += to_string(j);
			path += ".jpg";
			CString tmp(path.c_str());
			//MessageBox(tmp);
			Mat in = imread(path);
			if (in.empty())
			{
				//MessageBox(_T("!!!"));
				break;
			}
			in = in.reshape(1, 1);
			traindata_char.push_back(in);
			trainlabel_char.push_back(i);
			//imshow("123", in);
			//waitKey(0);
		}
	}
	traindata_char.convertTo(traindata_char, CV_32F);
	theApp.knn_char->setDefaultK(k_char);
	theApp.knn_char->setIsClassifier(true);
	theApp.knn_char->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
	theApp.knn_char->train(traindata_char, cv::ml::ROW_SAMPLE, trainlabel_char);

	

	Mat traindata, trainlabel;
	int k = 32;
	//读取训练数据
	for (int i = 0; i < 34; i++)
	{
		for (int j = 1; ; j++)
		{
			sprintf_s(ad, "data\\train_28_28\\%c\\%c_%d.jpg", id[i], id[i], j);
			//cout << ad << endl;
			Mat srcimage = imread(ad);
			
			if (srcimage.empty())
				break;
			//imshow("111",srcimage);
			//waitKey(0);
			srcimage = srcimage.reshape(1, 1);
			traindata.push_back(srcimage);
			trainlabel.push_back(i);
		}
	}
	//system("pause");
	//waitKey(0);
	traindata.convertTo(traindata, CV_32F);
	
	theApp.knn->setDefaultK(k);
	theApp.knn->setIsClassifier(true);
	theApp.knn->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
	theApp.knn->train(traindata, cv::ml::ROW_SAMPLE, trainlabel);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCarRecDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCarRecDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCarRecDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCarRecDlg::OnOpen()                                     //打开！！！
{
	CString filename;
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("ALL(*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //弹出对话框
	{
		filename = fileDlg.GetPathName();
	}

	USES_CONVERSION;
	String filename1 = W2A(filename);

	if (filename1 != "")
	{
		//注意，实际上寻找车牌区域和提取车牌是在这里调用LPR类内函数完成的
		LPR lpr(filename1);
		lpr.processing();
		Mat tmp;
		imwrite("lpr\\srcImg.bmp", lpr.srcImage);
		imwrite("lpr\\ranged.bmp", lpr.rangedImage);
		imwrite("lpr\\plate.bmp", lpr.finalpic);
	
		//显示图片
		CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC111);
		pWnd->SetBitmap((HBITMAP)::LoadImage(NULL,
			CString("lpr\\srcImg.bmp"),  //资源号或本地文件名
			IMAGE_BITMAP,       //装载位图 IMAGE_CURSOR光标 IMAGE_ICON图标
			400,                  //宽度 0为默认大小
			300,                  //高度 像素为单位
			LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	}
	

}
void CCarRecDlg::OnBnClickedsearch()                        //寻找车牌区域
{
	
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC2);
	//显示图片
	pWnd->SetBitmap((HBITMAP)::LoadImage(NULL,
		CString("lpr\\ranged.bmp"),  //资源号或本地文件名
		IMAGE_BITMAP,       //装载位图 IMAGE_CURSOR光标 IMAGE_ICON图标
		400,                  //宽度 0为默认大小
		300,                  //高度 像素为单位
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	/*Ptr<ml::SVM> svm = ml::SVM::load("car.xml");
	Mat svMat = svm->getSupportVectors();*/
}
void CCarRecDlg::OnBnClickedTqcp()                       //提取车牌
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATICplate);
	//显示图片
	pWnd->SetBitmap((HBITMAP)::LoadImage(NULL,
		CString("lpr\\plate.bmp"),  //资源号或本地文件名
		IMAGE_BITMAP,       //装载位图 IMAGE_CURSOR光标 IMAGE_ICON图标
		0,                  //宽度 0为默认大小
		0,                  //高度 像素为单位
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
}








void CCarRecDlg::OnBnClickedQcby()                                         //去除边缘
{
	// TODO: 在此添加控件通知处理程序代码
	Mat srcImg = imread("lpr\\plate.bmp");
	cvtColor(srcImg, srcImg, CV_BGR2GRAY);   //转为灰度图
	threshold(srcImg, binImg, 150, 255, THRESH_OTSU); //
	

	//去除小区域放后边了
	//去除小区域   这里转了个3通道绕圈了，无所谓了，懒得改了，能用就行
	//Mat labels, img_color, stats, centroids;
	//int i, nccomps = cv::connectedComponentsWithStats(

	//	binImg, labels,

	//	stats, centroids

	//);
	//vector<cv::Vec3b> colors(nccomps + 1);

	//colors[0] = Vec3b(0, 0, 0); // background pixels remain black.

	//for (i = 1; i < nccomps; i++) {

	//	colors[i] = Vec3b(255, 255, 255);

	//	if (stats.at<int>(i, cv::CC_STAT_AREA) < 25)//面积小于25干掉了

	//		colors[i] = Vec3b(0, 0, 0); // small regions are painted with black too.

	//}
	//img_color = Mat::zeros(binImg.size(), CV_8UC3);

	//for (int y = 0; y < img_color.rows; y++)
	//	for (int x = 0; x < img_color.cols; x++)
	//	{
	//		int label = labels.at<int>(y, x);

	//		CV_Assert(0 <= label && label <= nccomps);
	//		img_color.at<cv::Vec3b>(y, x) = colors[label];
	//	}

	//imwrite("connectedComponentsWithStats.bmp", img_color);
	/*---------------------------------------------------------------------*/


	//去除小区域 方法2
	//cvtColor(img_color, binImg, CV_BGR2GRAY);

	//std::vector<std::vector<cv::Point>> contours;
	//cv::findContours(imgHSVMask, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
	//contours.erase(std::remove_if(contours.begin(), contours.end(),
	//	[](const std::vector<cv::Point>& c) {return cv::contourArea(c) < 30; }), contours.end());
	//https://www.cnblogs.com/zi-wang/p/9800141.html
	//imwrite("binImg.bmp", binImg);
	/*---------------------------------------------------------------------*/


	//radon变换进行倾斜矫正
	//进行radon变换找直线
	vector<Vec4i> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合  
	HoughLinesP(binImg, lines, 1, CV_PI / 180, 80, 50, 10);
	Mat tbin;
	cvtColor(binImg,tbin,CV_GRAY2BGR);
	long long maxlen = 0;
	int remder;
	//找最长的线段求倾斜角度
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		if ((long long)(l[2] - l[0]) * (long long)(l[2] - l[0]) + (long long)(l[3] - l[1]) * (long long)(l[3] - l[1]) > maxlen)
		{
			maxlen = (long long)(l[2] - l[0]) * (long long)(l[2] - l[0]) + (long long)(l[3] - l[1]) * (long long)(l[3] - l[1]);
			remder = i;
		}
	}
	Vec4i l = lines[remder];
	line(tbin, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, CV_AA);
	imwrite("step2\\lines.bmp", tbin);
	//radon
	double kLine = ((double)l[3] - (double)l[1]) / ((double)l[2] - (double)l[0]);
	double lines_arctan = atan(kLine);
	lines_arctan=lines_arctan * 180.0 / 3.1415926;
	

	//指定旋转中心
	cv::Point2f center(binImg.cols / 2., binImg.rows / 2.);
	//获取旋转矩阵（2x3矩阵）
	Mat rot_mat = getRotationMatrix2D(center, lines_arctan,1.0);
	//根据旋转矩阵进行仿射变换
	Mat rotateImg= binImg.clone();
	cv::warpAffine(binImg, rotateImg, rot_mat, binImg.size());
	imwrite("step2\\beforeRotBinImg.bmp", binImg);
	imwrite("step2\\rotateImg.bmp", rotateImg);
	threshold(rotateImg, binImg, 1, 255, CV_THRESH_BINARY);
	//
	//imwrite("binImg.bmp", binImg);
	/*---------------------------------------------------------------------*/
	//这里尝试了去除小区域后用radon变换找到边缘直线，求其倾斜角度，并用此角度进行反向旋转以达到倾斜矫正的目低
	//但是旋转变换会引起各种插值问题，导致旋转后的图像由于插值不利于后续处理
	//另外在我们应用场景也假设摄像头获取的车辆图像就比较正，所以干脆省了吧OvO
	//好烦啊这玩意，优化起来没完没了
	//还是加上了OvO

	/*FILE* fp;
	fp = freopen("jiaodu.txt", "w+", stdout);
	cout << binImg << endl;
	fclose(fp);*/


	imwrite("step2\\binImg.bmp", binImg);
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_BY1);
	pWnd->SetBitmap((HBITMAP)::LoadImage(NULL,
		CString("step2\\binImg.bmp"),  //资源号或本地文件名
		IMAGE_BITMAP,       //装载位图 IMAGE_CURSOR光标 IMAGE_ICON图标
		0,                  //宽度 0为默认大小
		0,                  //高度 像素为单位
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	
	

	//以下为去除上下的横边缘和铆钉
	//注释掉的是原始的方案，以上边缘为例，是从上到下找到跳变次数大于等于7次的最下一行行号，找到就break
	//但是这样有一个问题，遇到那行有多于7个零碎的点就出问题了，如图，行号会记录成虚假的字符区域边缘
	/*
	                         《-第0行
	000000000000000000000    《-上边缘，
	 0    000000000 0  

       0 0 0 0 0 0 00 0      《-虚假的字符区域边缘       原方法

	                         《-最下的跃变次数不足7次的行   新方法
	  0 0 0 0 0 0 0          《-真正的字符区域边缘
	  0 0 0 0 0 0 0 
	  0 0 0 0 0 0 0 
	  0 0 0 0 0 0 0
      0 0 0 0 0 0 0          《-假设是7个1，此行为正中央行
	*/
	//所有想了个改进的办法，以上边缘为例，从第0行开扫，到正中央行为止，记录最下面的跃变次数小于7次的行的行号
	//这样找到的就是真正的字符区域边缘的行号了

	ding = 0;
	//for (int i = 0; i < binImg.rows*0.5; i++) {
	//	int x = 0;
	//	CString str;

	//	//MessageBox(str, _T("title"), MB_OK);

	//	for (int j = 0; j < binImg.cols - 1; j++) {
	//		if (binImg.at<uchar>(i, j) == 255 && binImg.at<uchar>(i, j + 1) == 0)
	//			x++;
	//	}

	//	//str.Format(_T("%d"), x);
	//	//MessageBox(str, _T("title"), MB_OK);
	//	//cout << i << " " << x << endl;
	//	if (x < 7) {
	//		for (int k = 0; k < binImg.cols; k++)
	//			binImg.at<uchar>(i, k) = 0;
	//	}
	//	if (x >= 7&&ding==0) {
	//		ding = i;
	//		/*file* fp;
	//	fp = freopen("file.txt", "w+", stdout);
	//	cout << ding << endl;
	//	cout << "$$$" << endl;
	//	fclose(fp);*/
	//	}
	//	
	//}
	for (int i = 0; i < binImg.rows * 0.5; i++) {
		int x = 0;
		for (int j = 0; j < binImg.cols - 1; j++) {
					if (binImg.at<uchar>(i, j) == 255 && binImg.at<uchar>(i, j + 1) == 0)
						x++;
				}
		if (x < 7)
		{
			ding = i;
		}
	}
	for (int i = 0; i <= ding; i++) {
		for (int j = 0; j < binImg.cols - 1; j++) {
					binImg.at<uchar>(i, j) = 0;
				}
	}
	
	di = 0;
	/*for (int i = binImg.rows - 1; i > binImg.rows - binImg.rows * 0.50; i--) {
		int x = 0;
		for (int j = 0; j < binImg.cols - 1; j++) {
			if (binImg.at<uchar>(i, j) == 255 && binImg.at<uchar>(i, j + 1) == 0)
				x++;
		}
		if (x < 7) {
			for (int k = 0; k < binImg.cols; k++)
				binImg.at<uchar>(i, k) = 0;
		}
		if (x >= 7 && di == 0) {
			di = i;
			
		}
	}*/

	for (int i = binImg.rows - 1; i > binImg.rows - binImg.rows * 0.50; i--) {
		int x = 0;
		for (int j = 0; j < binImg.cols - 1; j++) {
			if (binImg.at<uchar>(i, j) == 255 && binImg.at<uchar>(i, j + 1) == 0)
				x++;
		}
		if (x < 7)
		{
			di = i;
		}
	}
	for (int i = binImg.rows - 1; i >= di; i--) {
		for (int j = 0; j < binImg.cols - 1; j++) {
			binImg.at<uchar>(i, j) = 0;
		}
	}

	//去竖边缘
	//没什么好办法，左边缘为例，直接看最左边20列，如果这20列内有联通区域宽度不足阈值，干掉
	int width = binImg.cols;
	int height = binImg.rows;


	int perPixelValue;                    //每个像素的值
	int* projectValArry = new int[width];//创建一个用于储存每列白色像素个数的数组
	memset(projectValArry, 0, width * 4);//初始化数组
	/*for (int i = 0; i < width; i++) {
		projectValArry[i] = 0;
	}*/
	//遍历每一列的图像灰度值，查找每一行255的值，（统计每一列白色像素值）
	for (int col = 0; col < width; ++col)
	{
		for (int row = 0; row < height; ++row)
		{
			perPixelValue = binImg.at<uchar>(row, col);
			if (perPixelValue == 255)
			{
				projectValArry[col]++;
			}
		}
	}
	//去左侧竖直边缘
	int s = 0;//记录进入字符区的索引
	int e = 0;//记录进入空白区域的索引
	bool inblock = false;//是否遍历到了字符区内
	for (int i = 0; i < 20; i++)
	{
		if (!inblock && projectValArry[i] != 0)//进入字符区了
		{
			inblock = true;
			s = i;
		}
		else if (projectValArry[i] == 0 && inblock)//进入空白区了  
		{
			e = i;
			inblock = false;
			if (e - s < 15) {
				for (int k = 0; k < e; k++) {
					for (int l = 0; l < height; l++)
						binImg.at<uchar>(l, k) = 0;
				}
				//break;
			}
		}
	}
	//去右侧竖直边缘
	s = 0;//记录进入字符区的索引
	e = 0;//记录进入空白区域的索引
	inblock = false;//是否遍历到了字符区内
	for (int i = binImg.cols - 1; i > binImg.cols - 21; i--)
	{
		if (!inblock && projectValArry[i] != 0)//进入字符区了
		{
			inblock = true;
			s = i;
		}
		else if (projectValArry[i] == 0 && inblock)//进入空白区了  
		{
			e = i;
			inblock = false;
			if (s - e < 15) {
				for (int k = binImg.cols - 1; k > e; k--) {
					for (int l = 0; l < height; l++)
						binImg.at<uchar>(l, k) = 0;

				}
				//break;
			}
		}
	}

	

	//去一下小噪点,以便后续投影法分割字符
	Mat labels, img_color, stats, centroids;
	int i, nccomps = cv::connectedComponentsWithStats(

		binImg, labels,

		stats, centroids

	);
	vector<cv::Vec3b> colors(nccomps + 1);

	colors[0] = Vec3b(0, 0, 0); // background pixels remain black.

	for (i = 1; i < nccomps; i++) {

		colors[i] = Vec3b(255, 255, 255);

		if (stats.at<int>(i, cv::CC_STAT_AREA) < 15)//面积小于25干掉了

			colors[i] = Vec3b(0, 0, 0); // small regions are painted with black too.

	}
	img_color = Mat::zeros(binImg.size(), CV_8UC3);

	for (int y = 0; y < img_color.rows; y++)
		for (int x = 0; x < img_color.cols; x++)
		{
			int label = labels.at<int>(y, x);

			CV_Assert(0 <= label && label <= nccomps);
			img_color.at<cv::Vec3b>(y, x) = colors[label];
		}

	imwrite("step2\\connectedComponentsWithStats.bmp", img_color);
	cvtColor(img_color, binImg, CV_BGR2GRAY);
	

	imwrite("step2\\edgeED.bmp", binImg);
	//显示图片
	CStatic* pWnd1 = (CStatic*)GetDlgItem(IDC_BY2);
	pWnd1->SetBitmap((HBITMAP)::LoadImage(NULL,
		CString("step2\\edgeED.bmp"),  //资源号或本地文件名
		IMAGE_BITMAP,       //装载位图 IMAGE_CURSOR光标 IMAGE_ICON图标
		0,                  //宽度 0为默认大小
		0,                  //高度 像素为单位
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
}












void CCarRecDlg::OnBnClickedZffg()         //字符分割
{
	
	// TODO: 在此添加控件通知处理程序代码
	roiList.clear();

	int width = binImg.cols;
	int height = binImg.rows;                                       //Otsu处理能够根据图像给出最佳的分割阈值。
	threshold(binImg, binImg, 150, 255, THRESH_OTSU); //值设置多少合适
	//imshow("threshold", binImg);

	int perPixelValue;                    //每个像素的值
	int* projectValArry = new int[width];//创建一个用于储存每列白色像素个数的数组
	memset(projectValArry, 0, width * 4);//初始化数组
	/*for (int i = 0; i < width; i++) {
		projectValArry[i] = 0;
	}*/
	//遍历每一列的图像灰度值，查找每一行255的值，（统计每一列白色像素值）
	for (int col = 0; col < width; ++col)
	{
		for (int row = 0; row < height; ++row)
		{
			perPixelValue = binImg.at<uchar>(row, col);
			if (perPixelValue == 255)
			{
				projectValArry[col]++;
			}
		}
	}

	//vector<Mat> roiList;//用于储存分割出来的每个字符
	int startIndex = 0;//记录进入字符区的索引
	int endIndex = 0;//记录进入空白区域的索引
	bool inBlock = false;//是否遍历到了字符区内
	int num = 10;
	int flag = 0;
	for (int i = binImg.cols - 1; i > 0; i--)      //从右往左  针对类似“川”字的
	{
		if (!inBlock && projectValArry[i] != 0)//进入字符区了
		{
			inBlock = true;
			startIndex = i;
		}
		else if (projectValArry[i] == 0 && inBlock)//进入空白区了  
		{
			endIndex = i;
			inBlock = false;

			Mat roiImg;
			roiImg = binImg(Range(ding, di), Range(endIndex - 3, startIndex + 1 + 3));//行是从15行到最末，列是从进入字符区的列号到空白区的列号
			roiList.push_back(roiImg);
			flag++;
		}
		if (flag == license_len - 1) {
			Mat roiImg = binImg(Range(ding,di), Range(6, endIndex - 3));
			roiList.push_back(roiImg);
			break;
		}

	}


	//处理“1”
	for (int i = 0; i < roiList.size(); i++)
	{
		if (roiList[i].cols < 20) 
			copyMakeBorder(roiList[i], roiList[i], 0, 0, 4, 4, BORDER_REPLICATE);
	}


	//储存分割后的字符

	for (int i = 0; i < roiList.size(); i++)
	{
		string file_name = "step2\\fg" + to_string(i) + ".bmp";
		imwrite(file_name, roiList[i]);
	}
	for (int i = 0; i < roiList.size(); i++)
	{
		CStatic* pWnd = (CStatic*)GetDlgItem(1013 - i);

		String road = "step2\\fg" + to_string(i) + ".bmp";
		CString roadC;
		roadC = road.c_str();
		pWnd->SetBitmap((HBITMAP)::LoadImage(NULL,
			roadC,  //资源号或本地文件名
			IMAGE_BITMAP,       //装载位图 IMAGE_CURSOR光标 IMAGE_ICON图标
			0,                  //宽度 0为默认大小
			0,                  //高度 像素为单位
			LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	}
}






void CCarRecDlg::OnBnClickedZfsb() //字符识别
{
	// TODO: 在此添加控件通知处理程序代码
	
	
	int k = 32;
	cv::Mat nearests(1, k, CV_32F);
	//cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create();
	//Ptr<cv::ml::KNearest> knn = cv::ml::StatModel::load<cv::ml::KNearest>("d:\\model.xml");

	Mat tmp;
	for (int i = 0; i < license_len-1; i++)
	{
		if (i == 5)
			continue;

		tmp= imread("step2\\fg"+to_string(i)+".bmp");
		resize(tmp, tmp, Size(28, 28));
		//imshow("resize", tmp);
		imwrite("step2\\ff" + to_string(i) + ".bmp", tmp);
		tmp = tmp.reshape(1, 1);
		tmp.convertTo(tmp, CV_32F);
		

		//knn模型用来识别字母数字
		int  response = theApp.knn->findNearest(tmp,k, nearests);
		
		CString str;
		str.Format(_T("%c"), id[response]);
		//m_edit1.SetWindowTextW(str);
		//MessageBox(str);
		if (i < 5)
		{
			CStatic* pWnd = (CStatic*)GetDlgItem(1024 - i);
			pWnd->SetWindowTextW(str);
		}
		else
		{
			CStatic* pWnd = (CStatic*)GetDlgItem(1024 - i+1);
			pWnd->SetWindowTextW(str);
		}
	}
	tmp = imread("step2\\fg7.bmp");
	resize(tmp, tmp, Size(28, 28));
	//imshow("resize", tmp);
	imwrite("step2\\ff7.bmp", tmp);
	tmp = tmp.reshape(1, 1);
	tmp.convertTo(tmp, CV_32F);


	//knn_char模型用来识别汉字
	int  response = theApp.knn_char->findNearest(tmp, k, nearests);
	
	//MessageBox(xx[response]);
	CStatic* pWnd = (CStatic*)GetDlgItem(1024 - 7 + 1);
	pWnd->SetWindowTextW(xx[response]);
}





void CCarRecDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
