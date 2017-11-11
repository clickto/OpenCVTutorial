#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
const string sourceWindowName = "SrcWindow";
const string equalizedWindowName = "Equalized Window";
int main(int argc, char ** argv)
{
	if (argc != 2) {
		cout << "Usage:" << argv[0] << " image" << endl;
		return -1;
	}
	Mat src, dst;

	src = imread(argv[1], 1);
	if (!src.data) {
		cout << "read failed "<< endl;
		return -1;
	}
	cvtColor(src, src, CV_BGR2GRAY);
	equalizeHist(src, dst);
	namedWindow(sourceWindowName);
	namedWindow(equalizedWindowName);
	imshow(sourceWindowName, src);
	imshow(equalizedWindowName, dst);
	waitKey(0);
	return 0;
}