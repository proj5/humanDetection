#ifndef _MC_TEST_DETECTOR_H
#define _MC_TEST_DETECTOR_H 1

#include "detector.h"

class TestDetector : public Detector {
	private:
		CascadeClassifier  classifier;				
	
	public:		
		TestDetector() {
			classifier.load("Models/test.xml");
		}
		
		virtual vector<Rect> detect(const Mat& img) {
			vector<Rect> result;
			classifier.detectMultiScale(img, result, 1.7, 3, 0, Size(5,5), Size(100, 100));
			nonmaxSuppression(result);
			return result;
		}
	
};

#endif