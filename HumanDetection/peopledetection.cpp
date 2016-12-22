#include <iostream>
#include <opencv2/opencv.hpp>
#include <ctime>

using namespace std;
using namespace cv;

double getTime(clock_t start, clock_t end) {
	return double(end - start) / CLOCKS_PER_SEC;
}

const int WIDTH = 240;
const int HEIGHT = 180;

int main(int argc, const char * argv[]) {
	VideoCapture cap;
	cap.open("C:\\Users\\XuanDuc\\Desktop\\VIDEO0042.mp4");
	cout << cap.get(CV_CAP_PROP_FRAME_WIDTH); cout << " "; cout << cap.get(CV_CAP_PROP_FRAME_HEIGHT); cout << endl;
	cap.set(CV_CAP_PROP_FRAME_WIDTH , 320);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT , 240);
	cout << cap.get(CV_CAP_PROP_FRAME_WIDTH); cout << " "; cout << cap.get(CV_CAP_PROP_FRAME_HEIGHT); cout << endl;
	if (!cap.isOpened())
		return -1;

	Mat img;
	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	namedWindow("video capture", CV_WINDOW_AUTOSIZE);
	while (true) {
		clock_t start = clock();
		cap >> img;
	
		resize(img, img, Size(WIDTH, HEIGHT), 0, 0, INTER_CUBIC);
		cout << img.cols << " " << img.rows << endl;
		if (!img.data)
			continue;

		vector<Rect> found, found_filtered;
		hog.detectMultiScale(img, found, 0, Size(8, 8), Size(32, 32), 1.05, 2);

		size_t i, j;
		for (i = 0; i < found.size(); i++) {
			Rect r = found[i];
			for (j = 0; j < found.size(); j++)
				if (j != i && (r & found[j]) == r)
					break;
			if (j == found.size())
				found_filtered.push_back(r);
		}
		for (i = 0; i < found_filtered.size(); i++) {
			Rect r = found_filtered[i];
			r.x += cvRound(r.width * 0.1);
			r.width = cvRound(r.width * 0.8);
			r.y += cvRound(r.height * 0.06);
			r.height = cvRound(r.height * 0.9);
			rectangle(img, r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);
		}
		//resize(img, img, Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT)), 0, 0, INTER_CUBIC);
		imshow("video capture", img);
		clock_t end = clock();
		cout << getTime(start, end) << endl;
		if (waitKey(20) >= 0)
			break;


	}
	return 0;
}