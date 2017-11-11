#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
Mat src, templ, result;
const string srcName = "Source";
const string templateName = "Template";
const string resultName = "Result";
const string trackBarLabel = "Method: \n 0:SQDIFF \n 1:SQDIFF NORMED \n 2:TM CCORR \n 3:TM CCORR NORMED \n 4:TM COEFF";
int matchMethod;
int maxTrackbar = 5;
void onMatchMethod(int value, void *) 
{
	Mat srcCopy;
	src.copyTo(srcCopy);
	int resultCols = src.cols;
	int resultRows = src.rows;
	result.create(resultRows, resultCols, CV_32FC1);
	auto start = (double)getTickCount();
	matchTemplate(src, templ, result, matchMethod);
	auto end = (double)getTickCount();
	auto cost = (end - start) * 1000. / getTickFrequency();
	cout << "method: " << matchMethod <<  " cost:" << cost << endl;
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	double minValue, maxValue;
	Point minLoc, maxLoc;
	Point matchLoc;
	minMaxLoc(result, &minValue, &maxValue, &minLoc, &maxLoc, Mat());

	if (matchMethod == CV_TM_SQDIFF || matchMethod == CV_TM_SQDIFF_NORMED) {
		matchLoc = minLoc;
	} else {
		matchLoc = maxLoc;
	}
	rectangle(srcCopy, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
	rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
	imshow(srcName, srcCopy);
	imshow(resultName, result);

	return;
}
int main(int argc, char ** argv)
{
	if (argc != 3) {
		cout << "Usage:" << argv[0] << " image1 image2" << endl;
		return -1;
	}
	src = imread(argv[1]);
	templ = imread(argv[2]);
	namedWindow(srcName);
	namedWindow(resultName);
	namedWindow(templateName);
	
	imshow(templateName, templ);
	imshow(srcName, src);
	createTrackbar(trackBarLabel, srcName, &matchMethod, maxTrackbar, onMatchMethod);

	waitKey(0);
	return 0;
}