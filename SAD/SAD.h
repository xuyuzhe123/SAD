#include"iostream"
#include"opencv2/opencv.hpp"
#include"iomanip"
using namespace std;
using namespace cv;

class SAD
{
public:
	SAD() :winSize(7), DSR(30) {}
	SAD(int _winSize, int _DSR) :winSize(_winSize), DSR(_DSR) {}
	Mat computerSAD(Mat &L, Mat &R); //计算SAD
private:
	int winSize; //卷积核的尺寸
	int DSR;     //视差搜索范围

};

Mat SAD::computerSAD(Mat &L, Mat &R)
{
	int Height = L.rows;
	int Width = L.cols;
	Mat Kernel_L(Size(winSize, winSize), CV_8U, Scalar::all(0));
	Mat Kernel_R(Size(winSize, winSize), CV_8U, Scalar::all(0));
	Mat Disparity(Height, Width, CV_8U, Scalar(0)); //视差图

	for (int i = 0; i < Width - winSize; i++)  //左图从DSR开始遍历
	{
		for (int j = 0; j < Height - winSize; j++)
		{
			Kernel_L = L(Rect(i, j, winSize, winSize));
			Mat MM(1, DSR, CV_32F, Scalar(0)); //

			for (int k = 0; k < DSR; k++)
			{
				int x = i - k;
				if (x >= 0)
				{
					Kernel_R = R(Rect(x, j, winSize, winSize));
					Mat Dif;
					absdiff(Kernel_L, Kernel_R, Dif);//
					Scalar ADD = sum(Dif);
					float a = ADD[0];
					MM.at<float>(k) = a;
				}

			}
			Point minLoc;
			Point maxLoc;
			minMaxLoc(MM, NULL, NULL, &minLoc, &maxLoc);

			int loc = minLoc.x;
			//int loc=DSR-loc;
			Disparity.at<char>(j, i) = loc*16 ;

		}
		//double rate = double(i) / (Width);
		//cout << "已完成" << setprecision(2) << rate * 100 << "%" << endl; //处理进度
	}
	return Disparity;
}