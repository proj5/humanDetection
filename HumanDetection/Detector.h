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
			//cout << "Enter";
			for (i = 0; i < rec.size(); i++) {
				Rect r = rec[i];
				for (j = 0; j < result.size(); j++){
					Rect overlap = rec[i] & result[j];
					Rect out = rec[i] | result[j];
					double now = overlap.width * overlap.height;
					double next = r.width * r.height + result[j].width * result[j].height - now;
					//cout << "--------------------------" << now << " " << next << endl;	
					if (now * 10 > next * 3)
						break;
				}

				if (j == result.size())
					result.push_back(r);
			}
			
			rec.swap(result);
		}
	
		virtual vector<Rect> detect(const Mat& img)=0;
		
		virtual ~Detector() {}
	
};

#endif