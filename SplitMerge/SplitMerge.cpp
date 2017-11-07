#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char ** argv)
{
	if (argc != 2) {
		cout << "Usage: SplitMerge image" << endl;
		return -1;
	}
	Mat img = imread(argv[1]);
	if (img.empty()) {
		cout << "read image failed" << endl;
		return -1;
	}
	vector<Mat> images;
	split(img, images);
	char names[][4] = { "B", "G", "R" };
	int index = 0;
	for (auto i : images) {
		namedWindow(names[index]);
		imshow(names[index], i);
		index++;
	}
	waitKey(0);
	Mat out;
	merge(images, out);
	namedWindow("out");
	imshow("out", out);
	waitKey(0);
	return 0;
}