#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char ** argv)
{
	if (argc != 3) {
		cout << "Usage: blend image1 image2" << endl;
		return -1;
	}

	Mat image1 = imread(argv[1]);
	Mat image2 = imread(argv[2]);
	if (image1.empty() || image2.empty()) {
		cout << "image read failed " << endl;
		return -1;
	}
	//namedWindow("Image1");
	//imshow("Image1", image1);
	//namedWindow("Image2");
	//imshow("Image2", image2);
	Mat roi;
	//选定Image1 380， 380 作为ROI区域
    roi = image1(Rect(0, 0, image2.cols, image2.rows));
	//对 ROI进行混合
	addWeighted(roi, 0.0, image2, 1.0, 128, roi);
	//显示
	namedWindow("Blend");
	imshow("Blend", image1);
	waitKey(0);
	return 0;
}
