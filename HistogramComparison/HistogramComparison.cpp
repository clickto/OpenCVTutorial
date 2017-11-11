#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char **argv)
{
	if (argc < 4) {
		cout << "Usage: " << argv[1] << " image1" << " image2" << " image3" << endl;
		return -1;
	}
	Mat img1, img2, img3;
	Mat hsv1, hsv2, hsv3;
	Mat hsvHalfDown;
	img1 = imread(argv[1]);
	img2 = imread(argv[2]);
	img3 = imread(argv[3]);

	cvtColor(img1, hsv1, COLOR_BGR2HSV);
	cvtColor(img2, hsv2, COLOR_BGR2HSV);
	cvtColor(img3, hsv3, COLOR_BGR2HSV);

	hsvHalfDown = hsv1(Range(img1.rows / 2, hsv1.rows - 1), Range(0, hsv1.cols - 1));
	int hBins = 50;
	int sBins = 60;
	int histSize[] = { hBins, sBins };
	float hRanges[] = {0, 180};
	float sRanges[] = { 0, 256 };
	const float *ranges[] = { hRanges, sRanges };
	int channels[] = { 0, 1 };
	MatND hist1, hist2, hist3, histHalfDown;
	calcHist(&hsv1, 1, channels, Mat(), hist1, 2, histSize, ranges, true, false);
	normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsvHalfDown, 1, channels, Mat(), histHalfDown, 2, histSize, ranges, true, false);
	normalize(histHalfDown, histHalfDown, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsv2, 1, channels, Mat(), hist2, 2, histSize, ranges, true, false);
	normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&hsv3, 1, channels, Mat(), hist3, 2, histSize, ranges, true, false);
	normalize(hist3, hist3, 0, 1, NORM_MINMAX, -1, Mat());
	
	for (int i = 0; i < 4; ++i) {
		
		double vHist1 = compareHist(hist1, hist1, i);
		double vHist2 = compareHist(hist1, hist2, i);
		double vHist3 = compareHist(hist1, hist3, i);
		double vHist4 = compareHist(hist1, histHalfDown, i);
		cout << "Method" << i << " " << vHist1 << " " << vHist2 << " " << vHist3 << " " << vHist4 << endl;
	}

	return 0;
}