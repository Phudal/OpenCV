#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

int main(int argc, const char** argv)
{
	Mat frame;
	vector<Rect> found;
	int i;
	char ch;

	// open the video file 
	VideoCapture cap("c:\\mitsubishi_768x576.avi");

	if (!cap.isOpened()) {
		cout << "can't open video file" << endl;
		return 0;
	}

	// detector (48x96 template) 
	HOGDescriptor hog(Size(48, 96), Size(16, 16), Size(8, 8), Size(8, 8), 9);
	
	hog.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());

	while (1) {
		// input image
		cap >> frame;
		if (frame.empty()) break;

		// detect 
		hog.detectMultiScale(frame, found, 1.2, Size(8, 8), Size(32, 32), 1.05, 6);

		// draw results (bounding boxes)
		for (i = 0; i < (int)found.size(); i++) 
		{
			rectangle(frame, found[i], Scalar(0, 255, 0), 2);
			putText(frame, std::to_string(i + 1), Point(found[i].x - 30 ,found[i].y + 60), 2, 1.2, Scalar::all(255));
		}

		// display
		imshow("20184401 ȫ�伷 Pedestrian Detection", frame);
		ch = waitKey(10);
		if (ch == 27) break;	// ESC Key
		else if (ch == 32)	// SPACE Key
		{
			while ((ch = waitKey(10)) != 32 && ch != 27); if (ch == 27) break;
		}
	}
}