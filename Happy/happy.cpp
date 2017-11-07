#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
int main(int argc, char ** argv)
{
	if (argc != 2) {
		cout << "args error" << endl
			<< "Usage: Happy imageFilePath" << endl;
		return -1;
	}
	char *imageName = argv[1];
	Mat image;
	image = imread(imageName, 1);
	if (!image.data) {
		cout << "no image data " << endl;
		return -1;
	}
	Mat gray_image;
	cvtColor(image, gray_image, CV_BGR2GRAY);

	imwrite("gray_image.jpg", gray_image);

	namedWindow(imageName, CV_WINDOW_AUTOSIZE);
	namedWindow("Gray image", CV_WINDOW_AUTOSIZE);

	imshow(imageName, image);
	imshow("Gray image", gray_image);
	waitKey(0);
	return 0;
}