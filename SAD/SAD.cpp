
// MySAD.cpp : 定义控制台应用程序的入口点。
//

#include"SAD.h"
int main()
{
	Mat Img_L = imread("G:\\opencvcode\\SAD\\Data\\Cloth3\\view1.png", 0);
	Mat Img_R = imread("G:\\opencvcode\\SAD\\Data\\Cloth3\\view5.png", 0);
	Mat Disparity;    //视差图

	//SAD mySAD;
	SAD mySAD(7, 100);
	Disparity = mySAD.computerSAD(Img_L, Img_R);

	imshow("Img_L", Img_L);
	imshow("Img_R", Img_R);
	imshow("Disparity", Disparity);
	waitKey();
	return 0;
}