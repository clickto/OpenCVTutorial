#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
void help()
{
	cout 
		<< "-----------------------------------------------------" << endl
		<< "This is a test program for the Image Watcher Debugger " << endl
		<< "plug-in for Visual Studio. The program load an image " << endl
		<< "image from a file and runs the Canny edge detector." << endl
		<< "No output is displayed or written to disk." << endl
		<< "Usage: ImageWatcher inputImage" << endl
		<< "-----------------------------------------------------" << endl;
}
int main(int argc, char ** argv)
{
	help();
	if (argc != 2) {
		cout << "Usage: ImageWatcher inputImage" << endl;
		return -1;
	}
	cout << "load image" << argv[1] << endl;
	Mat input;
	input = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	cout << "detector edges in input image" << endl;
	Mat edges;
	Canny(input, edges, 10, 100);
	namedWindow("edge",CV_WINDOW_AUTOSIZE);
	imshow("edge", edges);
	waitKey(0);
	return 0;
}