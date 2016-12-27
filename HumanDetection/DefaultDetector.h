#ifndef _MC_DEFAULT_DETECTOR_H
#define _MC_DEFAULT_DETECTOR_H 1

#include "Detector.h"

class DefaultDetector : public Detector {
	private:
		HOGDescriptor hog;				
	
	public:		
		DefaultDetector() {
			hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
		}
		
		virtual vector<Rect> detect(const Mat& img) {
			vector<Rect> result;
			hog.detectMultiScale(img, result, 0, Size(8, 8), Size(32, 32), 1.05, 2);
			nonmaxSuppression(result);
			return result;
		}
	
};

#endif