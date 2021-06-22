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
	// ���� ������ ī�޶���� 0������ ��ȣ�� �ο�����

	if (!cap.isOpened())
	{
		cerr << "ī�޶� �� �� �����ϴ�." << endl;
		return -1;
	}

	int fps = cap.get(CAP_PROP_FPS);
	int width = cap.get(CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CAP_PROP_FRAME_HEIGHT);
	int fourcc = VideoWriter::fourcc('M', 'J', 'P', 'G');

	VideoWriter outputVideo;
	outputVideo.open("output.avi", fourcc, fps, Size(width, height), true);
	// outputVideo.open("output.avi", fourcc, fps, Size(width, height), true);
	// ������ �������� ����� ��� fourcc�� -1�� ����

	if (!outputVideo.isOpened())
	{
		cerr << "������ ������ ���� �ʱ�ȭ�� ����" << endl;
		return -1;
	}

	while (true)
	{
		cap.read(frame);
		if (frame.empty())
		{
			cerr << "ĸó ����" << endl;
			return -1;
		}

		currnet_threshold = getTrackbarPos("currnet_threshold", "Trackbar");

		// cvtColor(frame, frame, COLOR_BGR2GRAY);
		//void cv:: cvtColor(InputArray src, OutputArray dst, int code, int dstCn = 0)
		//						�Է�				���					��ȯ �ڵ�

		imshow("Before", frame);

		cvtColor(frame, frame, COLOR_BGR2GRAY);
		// cvtColor(frame, frame, COLOR_GRAY2);

		threshold(frame, frame, currnet_threshold, 255, THRESH_BINARY);
		cvtColor(frame, frame, COLOR_GRAY2BGR);

		outputVideo.write(frame);
		imshow("After", frame);
		// ������ ����		

		int wait = int(1.0 / fps * 1000);
		if (waitKey(wait) >= 0)
			break;
	}
	return 0;
}