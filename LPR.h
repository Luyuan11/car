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
	void load(String path);//����ͼ��
	void showSrc();//��ʾԭͼ
	void closeOperation();//������
	void processing();//����
	void test();//����
	void detectTwice();
	~LPR();

	Mat srcImage;//ԭͼ
	Mat rangedImage;//
	Mat closeImage;//�������ͼ��
	Mat finalpic;//�������ͼ��

	
};
