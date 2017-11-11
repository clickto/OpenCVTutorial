#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char ** argv)
{
	if (argc != 2) {
		cout << "Usage:" << argv[0] << " image" << endl;
		return -1;
	}
	Mat src;
	src = imread(argv[1]);
	if (!src.data) {
		return -1;
	}
	vector<Mat> bgrPlane;
	split(src, bgrPlane);
	int histSize = 256;
	float range[] = { 0, 256 };
	const float *histRange = { range };
	bool uniform = true;
	bool accumulate = false;
	Mat bHist, gHist, rHist;
	calcHist(&bgrPlane[0], 1, 0, Mat(), bHist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgrPlane[1], 1, 0, Mat(), gHist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgrPlane[2], 1, 0, Mat(), rHist, 1, &histSize, &histRange, uniform, accumulate);
	int histW = 512, histH = 400;

	int binW = cvRound((double)histW / histSize);
	Mat histImage(histH, histW, CV_8UC3, Scalar(0, 0, 0));
	
	normalize(bHist, bHist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(gHist, gHist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(rHist, rHist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; ++i) {
		line(histImage, Point(binW * (i - 1), histH - cvRound(bHist.at<float>(i - 1))),
			Point(binW * i, histH - cvRound(bHist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(binW * (i - 1), histH - cvRound(gHist.at<float>(i - 1))),
			Point(binW * i, histH - cvRound(gHist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(binW * (i - 1), histH - cvRound(rHist.at<float>(i - 1))),
			Point(binW * i, histH - cvRound(rHist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}
	namedWindow("hist");
	imshow("hist", histImage);
	waitKey(0);
	return 0;
}