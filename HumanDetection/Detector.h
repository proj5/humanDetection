#ifndef _MC_DETECTOR_H
#define _MC_DETECTOR_H 1

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Detector {
	public:		
		Detector() {}
		virtual void nonmaxSuppression(vector<Rect>& rec){
			size_t i, j;
			vector<Rect> result;
			for (i = 0; i < rec.size(); i++) {
				Rect r = rec[i];
				for (j = 0; j < rec.size(); j++)
					if (j != i && (r & rec[j]) == r)
						break;
				if (j == rec.size())
					result.push_back(r);
			}
			
			rec.swap(result);
		}
	
		virtual vector<Rect> detect(const Mat& img)=0;
		
		virtual ~Detector() {}
	
};

#endif