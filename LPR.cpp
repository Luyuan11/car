#include "pch.h"
#include "LPR.h"
#include <opencv2\imgproc\types_c.h>
#include <opencv2/imgproc/imgproc_c.h>


LPR::LPR(String path)
{
	this->load(path);
}
LPR::LPR()
{

}
LPR::~LPR()
{
	destroyAllWindows();
}
void LPR::showSrc()
{
	//显示原图
	imshow("原图", srcImage);
}
void LPR::load(String path)
{
	//读取车牌图片
	srcImage = imread(path);
	if (srcImage.empty())
	{
		MessageBox(NULL,TEXT("错误!获得的图像为空！"), TEXT("错误!获得的图像为空！"),MB_OK);
		exit(-1);
	}

	//resize(srcImage, srcImage, Size(srcImage.cols / 2, srcImage.rows / 2));

}

void LPR::test()
{
	Mat hsvImg;
	cvtColor(srcImage,hsvImg,CV_BGR2HSV_FULL);
	//inRange(hsvImg, Scalar(145, 128, 153), Scalar(163, 255,180 ), rangedImage1); 
	inRange(hsvImg, Scalar(145, 128, 100), Scalar(163, 255, 255), rangedImage);   //车牌蓝色对应BGR范围
	//108, 119, 213,
	imwrite("lpr\\hsvED.bmp", rangedImage);

}
void LPR::closeOperation()
{
	//定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(17, 17));
	//进行形态学操作
	morphologyEx(rangedImage, rangedImage, MORPH_CLOSE, element);
	//imshow("【效果图】闭运算", rangedImage);

}
void LPR::detectTwice()
{

	//取轮廓
	vector< vector< Point> > contours;
	findContours(rangedImage,
		contours, // a vector of contours
		CV_RETR_EXTERNAL, // 提取外部轮廓
		CV_CHAIN_APPROX_NONE); // all pixels of each contours


	int cnt = 0;
	int largest_contour_index = 0;
	vector<Point> maxArea;//
	for (size_t i = 0; i < contours.size(); i++)                   //找边缘最多的区域
	{
		if (contourArea(contours[i])<200)                        //如果某个轮廓面积不足200，直接跳过
			continue;

		Mat tmp = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC1);  //tmp保存当前轮廓
		drawContours(tmp, contours, i, Scalar(255), CV_FILLED);
		Mat tmpSrc=srcImage.clone();
		//erode(tmp,tmp, getStructuringElement(MORPH_CROSS, Size(10, 10)));
		imwrite("lpr\\contour" + to_string(i) + ".bmp", tmp);
		Mat tres;
		tmpSrc.copyTo(tres,tmp);
		

		cvtColor(tres,tres,CV_BGR2GRAY);
		
		Sobel(tres,tres,CV_8UC1,1,1);
		
		//FILE* fp;
		//fp = freopen("file.txt", "w+", stdout);
		//cout << tres << endl;
		//fclose(fp);

		imwrite("lpr\\sobelED" + to_string(i) + ".bmp", tres);
		
		//统计边缘像素点个数
		int tcnt = 0;
		for (int k = 0; k < tres.rows; k++)
		{
			for (int l = 0; l < tres.cols; l++)
			{
				
				if (tres.at<uchar>(k, l) > 0)
				{
					tcnt++;
					//tres.at<uchar>(k, l) = 255;
				}
					
			}
		}

		

		if (tcnt > cnt)
		{
			cnt = tcnt;
			largest_contour_index = i;
			maxArea = contours[i];
		}

		
	}

	RotatedRect minRect;//最小外接矩形
	Point2f P[4];//矩形的顶点

	//绘制最小外接矩形
	minRect = minAreaRect(maxArea);
	minRect.points(P);


	finalpic = srcImage(minRect.boundingRect());   //用外接矩形进行掩膜
	//imshow("【效果图】",finalpic);


}





void LPR::processing()
{
	test();  //基于HSV一次定位
	closeOperation();
	detectTwice();   //使用边缘特征进行二次定位
}





