#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int ac, char** av)
{
	Mat img = imread("Yami.png", IMREAD_GRAYSCALE);

	// Mat cv::imread(const String & filename, int flags(IMREAD_COLOR))
	// IMREAD_UNCHANGED 알파값 존재하는 변환
	// IMREAD_COLOR 알파값 존재하지 않게 반환
	// IMREAD_GRAYSCALE grayscale로 변환 후 반환

	if (img.empty())
	{
		cout << "이미지가 존재하지 않습니다." << endl;
		return -1;
	}

	namedWindow("My Yami", WND_PROP_FULLSCREEN);
	// 윈도우 창 생성
	setWindowProperty("My Yami", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);

	Canny(img, img, 50, 150);
	
	imshow("My Yami", img);
	
	waitKey(0);
	// 키보드 입력이 있을때까지 대기
	
	return 0;		
}