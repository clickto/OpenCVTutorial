#include <opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
Mat src, img1, img2, img3;
int gBoxFilterValue = 3;
int gMeanBlurValue = 3;
int gGaussianBlurValue = 3;


const char windowName[] = {"Filter"};
const char boxFilterName[] = {"boxFilter"};
const char meanBlurName[] = {"meanBlur"};
const char gaussianBlurName[] = {"gaussianBlur"};

void onBoxFilter(int value, void *)
{
    boxFilter(src, img1, -1, Size(gBoxFilterValue + 1, gBoxFilterValue + 1));
    imshow(windowName, img1);

}
void onMeanBlur(int value, void *)
{
    blur(src, img2, Size(gMeanBlurValue + 1, gMeanBlurValue + 1), Point(-1, -1));
    imshow(windowName, img2);
}
void onGaussianBlur(int value, void *)
{
    GaussianBlur(src, img3, Size(gGaussianBlurValue * 2 + 1, gGaussianBlurValue * 2 + 1), 0, 0);
    imshow(windowName, img3);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " image" << endl;
        return -1;
    }
    src  = imread(argv[1]);
    if (src.empty()) {
        cout << "read image failed" << endl;
        return -1;
    }
    img1 = Mat::zeros(src.size(), src.type());
    img2 = Mat::zeros(src.size(), src.type());
    img3 = Mat::zeros(src.size(), src.type());
    namedWindow(windowName);
    imshow(windowName, src);

    createTrackbar(boxFilterName, windowName, &gBoxFilterValue, 40, onBoxFilter);
    createTrackbar(meanBlurName, windowName, &gMeanBlurValue, 40, onMeanBlur);
    createTrackbar(gaussianBlurName, windowName, &gGaussianBlurValue, 40, onGaussianBlur);
    waitKey(0);
    return 0;
}
