#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int gBrigheness = 80;
int gContrast = 80;
Mat image, dst;
const string windowName = "Window";
const string brightnessBarName = "brightnessBar";
const string contrastBarName = "contrastBar";

void onChange(int value, void *data) {
	for (int i = 0; i < image.rows; ++i) {
		for (int j = 0; j < image.cols; ++j) {
			dst.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(gContrast * 0.01 * (image.at<Vec3b>(i, j)[0]) + gBrigheness);
			dst.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(gContrast * 0.01 * (image.at<Vec3b>(i, j)[1]) + gBrigheness);
			dst.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(gContrast * 0.01 * (image.at<Vec3b>(i, j)[2]) + gBrigheness);
		}
	}
	imshow(windowName, dst);
}
//void onChange(int value, void *data) {
//	Mat bw = gBrigheness < 128 ? (image < gBrigheness) : (image > gBrigheness);
//	vector<vector<Point>> contours;
//	vector<Vec4i> hierarchy;
//	findContours(bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
//
//	Mat dst = Mat::zeros(image.size(), CV_8UC1);
//	if (!contours.empty() && !hierarchy.empty()) {
//		int index = 0;
//		while (index >= 0) {
//			Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
//			drawContours(dst, contours, index, color, CV_FILLED, 8, hierarchy);
//			index = hierarchy[index][0];
//		}
//	}
//	imshow(windowName, dst);
//}
int main(int argc, char ** argv)
{
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " image" << endl;
		return -1;
	}
	image = imread(argv[1]);
	if (image.empty()) {
		cout << "read failed " << endl;
		return -1;
	}
	dst = Mat::zeros(image.size(), image.type());
	namedWindow(windowName);
	createTrackbar(brightnessBarName, windowName, &gBrigheness, 300, onChange);
	createTrackbar(contrastBarName, windowName, &gContrast, 300, onChange);
	onChange(gBrigheness, 0);
	onChange(gContrast, 0);
	waitKey(0);
	return 0;
}