#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;


int main() {
	Mat query, image, descriptors1, descriptors2; 
	Ptr<ORB> orbF = ORB::create(1000); 
	vector<KeyPoint> keypoints1, keypoints2; 
	vector< vector< DMatch> > matches;
	vector< DMatch > goodMatches;
	BFMatcher matcher(NORM_HAMMING); 
	Mat imgMatches, H;
	vector<Point2f> obj;
	vector<Point2f> scene; 
	vector<Point2f> objP(4); 
	vector<Point2f> sceneP(4);
	int i, k;
	float nndr;

	query = imread("computer_vision/query_samll.jpg");
	image = imread("computer_vision/input_samll.jpg");

	if (query.empty() || image.empty()) return -1;

	//Compute ORB Features resize(image, image, Size(640, 480));
	orbF->detectAndCompute(query, noArray(), keypoints1, descriptors1);
	orbF->detectAndCompute(image, noArray(), keypoints2, descriptors2);

	//KNN Matching 
	k = 2;
	matcher.knnMatch(descriptors1, descriptors2, matches, k);

	nndr = 0.6f;
	for (i = 0; i < matches.size(); i++) {
		if (matches.at(i).size() == 2 			&& matches.at(i).at(0).distance 			<= nndr * matches.at(i).at(1).distance) 
		{
			goodMatches.push_back(matches[i][0]);
		}
	}
	//Draw matching
	drawMatches(query, keypoints1, image, keypoints2, goodMatches, imgMatches, Scalar::all(-1), Scalar(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	if (goodMatches.size() < 4) { cout << "Matching failed" << endl; return 0; }

	//Find perspective transform
	for (i = 0; i < goodMatches.size(); i++) {
		obj.push_back(keypoints1[goodMatches[i].queryIdx].pt); 
		scene.push_back(keypoints2[goodMatches[i].trainIdx].pt);
	}

	H = findHomography(obj, scene, RANSAC); objP[0] = Point2f(0, 0);
	objP[1] = Point2f(query.cols, 0);
	objP[2] = Point2f(query.cols, query.rows); objP[3] = Point2f(0, query.rows);

	perspectiveTransform(objP, sceneP, H);

	for (i = 0; i < 4; i++) sceneP[i] += Point2f(query.cols, 0);
	for (i = 0; i < 4; i++)line(imgMatches, sceneP[i], sceneP[(i + 1) % 4], Scalar(255, 0, 0), 4);


	imshow("20184401 ȫ�伷", imgMatches);

	int ch = waitKey(100000);

}
