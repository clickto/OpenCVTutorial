#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
using namespace std;
using namespace cv;
int main(int argc, char **argv) 
{
	if (argc != 2) {
		cout << "Usage: display_image ImageLoadAndDisplay" << endl;
		return -1;
	}
	Mat image;
	image = imread(argv[1], IMREAD_COLOR);
	if (!image.data) {
		cout << "Could not open or find image " << argv[1] << endl;
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);

	waitKey(0);
	return 0;
}