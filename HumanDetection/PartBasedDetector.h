#ifndef _MC_PARTBASED_DETECTOR_H
#define _MC_PARTBASED_DETECTOR_H 1

#include "DPM/dpm.hpp"
#include "Detector.h"

class PartBasedDetector : public Detector {
private:
	string model_path;
public:
	PartBasedDetector() {

	}

	PartBasedDetector(string _model_path) {		
		model_path = _model_path;
	}

	virtual vector<Rect> detect(const Mat& img) {
		cv::Ptr<dpm::DPMDetector> detector = dpm::DPMDetector::create(vector<string>(1, model_path));
		vector<dpm::DPMDetector::ObjectDetection> ds;
		Mat image = img;
		detector->detect(image, ds);
		vector<Rect> result;
		for (int i = 0; i < ds.size(); ++i) {
			result.push_back(ds[i].rect);
		}
		nonmaxSuppression(result);
		return result;
	}
};

#endif // !_MC_PARTBASED_DETECTOR_H
