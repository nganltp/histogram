#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;


/*Draw histogram for B, G, R*/
void drawHis(Mat src, Mat &histImage)
{
	vector<Mat> bgr_planes;
	int hist_w = 1024; int hist_h = 300, histSize = 512;
	int bin_w = cvRound((double)hist_w / histSize);
	split(src, bgr_planes);
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true; bool accumulate = false;
	Mat hist;
	calcHist(&bgr_planes[0], 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}
	
}
int main()
{
	Mat src, dst;
	int hist_w = 1024; int hist_h = 300, histSize = 512;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat hisImgSrc(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	Mat hisImgDst(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	//const char* source_window = "Source image";
	//const char* equalized_window = "Equalized Image";
	src = imread("girl.jpg");
	resize(src, src, Size(480, 360), 0, 0, INTER_CUBIC);
	if (src.empty())
	{
		cout << "Usage: ./EqualizeHist_Demo <path_to_image>" << endl;
		return -1;
	}
	cvtColor(src, src, COLOR_BGR2GRAY);

	drawHis(src, hisImgSrc);
	equalizeHist(src, dst);
	drawHis(dst, hisImgDst);

	//namedWindow(source_window, WINDOW_AUTOSIZE);
	//namedWindow(equalized_window, WINDOW_AUTOSIZE);
	imshow("source_window", src);
	imshow("equalized_window", dst);
	//namedWindow("calcHist Demo", WINDOW_AUTOSIZE);
	imshow("calcHist Src", hisImgSrc);
	imshow("calcHist Dst", hisImgDst);
	waitKey(0);
	return 0;
}