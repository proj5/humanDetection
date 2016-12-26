#ifndef _MC_DEFAULT_TRACKER_H
#define _MC_DEFAULT_TRACKER_H 1

#include <opencv2/opencv.hpp>
#include "DefaultDetector.h"

using namespace cv;
using namespace std;

class DefaultTracker : public Tracker {
	private:
		Detector *d = new  DefaultDetector;
	public:		
		DefaultTracker() {}		
		vector<Rect> detect(const Mat& pre, const Mat& now, vector<Rect> boxes) {
			return d->detect(now);
		}
		
		~DefaultTracker() {
			delete d;
		}
	
};

#endif