#ifndef _MC_TRACKER_H
#define _MC_TRACKER_H 1

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Tracker {
	public:		
		Tracker() {}
		virtual void startDetect(){

		}	
			
		virtual vector<Rect> detect(const Mat& pre, const Mat& now, vector<Rect> boxes)=0;
		
		virtual ~Tracker() {}
	
};

#endif