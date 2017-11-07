#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int gBrigheness = 160;
const string windowName = "Window";
const string brightnessBarName = "brightnessBar";
const string contrastBarName = "contrastBar";
Mat image;
void onChange(int value, void *data) {
	Mat bw = gBrigheness < 128 ? (image < gBrigheness) : (image > gBrigheness);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	Mat dst = Mat::zeros(image.size(), CV_8UC1);
	if (!contours.empty() && !hierarchy.empty()) {
		int index = 0;
		while (index >= 0) {
			Scalar color((rand() & 255), (rand() & 255), (rand() & 255));
			drawContours(dst, contours, index, color, CV_FILLED, 8, hierarchy);
			index = hierarchy[index][0];
		}
	}
	imshow(windowName, dst);
}
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
	
	namedWindow(windowName);
	createTrackbar(brightnessBarName, windowName, &gBrigheness, 255, onChange);
	onChange(gBrigheness, 0);
	waitKey(0);
	return 0;
}