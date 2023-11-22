#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;

class LPR
{
public:
	LPR();
	LPR(String path);
	void load(String path);//加载图像
	void showSrc();//显示原图
	void closeOperation();//闭运算
	void processing();//处理
	void test();//处理
	void detectTwice();
	~LPR();

	Mat srcImage;//原图
	Mat rangedImage;//
	Mat closeImage;//闭运算后图像
	Mat finalpic;//闭运算后图像

	
};
