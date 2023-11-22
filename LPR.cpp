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
	//��ʾԭͼ
	imshow("ԭͼ", srcImage);
}
void LPR::load(String path)
{
	//��ȡ����ͼƬ
	srcImage = imread(path);
	if (srcImage.empty())
	{
		MessageBox(NULL,TEXT("����!��õ�ͼ��Ϊ�գ�"), TEXT("����!��õ�ͼ��Ϊ�գ�"),MB_OK);
		exit(-1);
	}

	//resize(srcImage, srcImage, Size(srcImage.cols / 2, srcImage.rows / 2));

}

void LPR::test()
{
	Mat hsvImg;
	cvtColor(srcImage,hsvImg,CV_BGR2HSV_FULL);
	//inRange(hsvImg, Scalar(145, 128, 153), Scalar(163, 255,180 ), rangedImage1); 
	inRange(hsvImg, Scalar(145, 128, 100), Scalar(163, 255, 255), rangedImage);   //������ɫ��ӦBGR��Χ
	//108, 119, 213,
	imwrite("lpr\\hsvED.bmp", rangedImage);

}
void LPR::closeOperation()
{
	//�����
	Mat element = getStructuringElement(MORPH_RECT, Size(17, 17));
	//������̬ѧ����
	morphologyEx(rangedImage, rangedImage, MORPH_CLOSE, element);
	//imshow("��Ч��ͼ��������", rangedImage);

}
void LPR::detectTwice()
{

	//ȡ����
	vector< vector< Point> > contours;
	findContours(rangedImage,
		contours, // a vector of contours
		CV_RETR_EXTERNAL, // ��ȡ�ⲿ����
		CV_CHAIN_APPROX_NONE); // all pixels of each contours


	int cnt = 0;
	int largest_contour_index = 0;
	vector<Point> maxArea;//
	for (size_t i = 0; i < contours.size(); i++)                   //�ұ�Ե��������
	{
		if (contourArea(contours[i])<200)                        //���ĳ�������������200��ֱ������
			continue;

		Mat tmp = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC1);  //tmp���浱ǰ����
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
		
		//ͳ�Ʊ�Ե���ص����
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

	RotatedRect minRect;//��С��Ӿ���
	Point2f P[4];//���εĶ���

	//������С��Ӿ���
	minRect = minAreaRect(maxArea);
	minRect.points(P);


	finalpic = srcImage(minRect.boundingRect());   //����Ӿ��ν�����Ĥ
	//imshow("��Ч��ͼ��",finalpic);


}





void LPR::processing()
{
	test();  //����HSVһ�ζ�λ
	closeOperation();
	detectTwice();   //ʹ�ñ�Ե�������ж��ζ�λ
}





