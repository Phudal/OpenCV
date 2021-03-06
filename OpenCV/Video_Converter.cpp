#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>


using namespace std;
using namespace cv;

void dummy(int, void*)
{

}

int main()
{
	int currnet_threshold = 30;
	
	namedWindow("Trackbar");
	createTrackbar("currnet_threshold", "Trackbar", &currnet_threshold, 255, dummy);
	setTrackbarPos("currnet_threshold", "Trackbar", 170);
	
	Mat frame;

	VideoCapture cap("Tanjiro no Uta.mp4");
	// 먼저 연결한 카메라부터 0번부터 번호를 부여받음

	if (!cap.isOpened())
	{
		cerr << "카메라를 열 수 없습니다." << endl;
		return -1;
	}

	int fps = cap.get(CAP_PROP_FPS);
	int width = cap.get(CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CAP_PROP_FRAME_HEIGHT);
	int fourcc = VideoWriter::fourcc('M', 'J', 'P', 'G');

	VideoWriter outputVideo;
	outputVideo.open("output.avi", fourcc, fps, Size(width, height), true);
	// outputVideo.open("output.avi", fourcc, fps, Size(width, height), true);
	// 저장할 동영상이 흑백인 경우 fourcc에 -1을 넣음

	if (!outputVideo.isOpened())
	{
		cerr << "동영상 저장을 위한 초기화중 에러" << endl;
		return -1;
	}

	while (true)
	{
		cap.read(frame);
		if (frame.empty())
		{
			cerr << "캡처 실패" << endl;
			return -1;
		}

		currnet_threshold = getTrackbarPos("currnet_threshold", "Trackbar");

		// cvtColor(frame, frame, COLOR_BGR2GRAY);
		//void cv:: cvtColor(InputArray src, OutputArray dst, int code, int dstCn = 0)
		//						입력				출력					변환 코드

		imshow("Before", frame);

		cvtColor(frame, frame, COLOR_BGR2GRAY);
		// cvtColor(frame, frame, COLOR_GRAY2);

		threshold(frame, frame, currnet_threshold, 255, THRESH_BINARY);
		cvtColor(frame, frame, COLOR_GRAY2BGR);

		outputVideo.write(frame);
		imshow("After", frame);
		// 동영상 저장		

		int wait = int(1.0 / fps * 1000);
		if (waitKey(wait) >= 0)
			break;
	}
	return 0;
}