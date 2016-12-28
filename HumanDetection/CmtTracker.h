#ifndef _MC_CMT_TRACKER_H
#define _MC_CMT_TRACKER_H 1

#include "Tracker.h"

#include "CppMT/CMT.h"
#include "CppMT/gui.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

#ifdef __GNUC__
#include <getopt.h>
#else
#include "getopt/getopt.h"
#endif

using cmt::CMT;
using cv::imread;
using cv::namedWindow;
using cv::Scalar;
using cv::VideoCapture;
using cv::waitKey;
using std::cerr;
using std::istream;
using std::ifstream;
using std::stringstream;
using std::ofstream;
using std::cout;
using std::min_element;
using std::max_element;
using std::endl;
using ::atof;

static string WIN_NAME = "CMT";
static string OUT_FILE_COL_HEADERS =
    "Frame,Timestamp (ms),Active points,"\
    "Bounding box centre X (px),Bounding box centre Y (px),"\
    "Bounding box width (px),Bounding box height (px),"\
    "Bounding box rotation (degrees),"\
    "Bounding box vertex 1 X (px),Bounding box vertex 1 Y (px),"\
    "Bounding box vertex 2 X (px),Bounding box vertex 2 Y (px),"\
    "Bounding box vertex 3 X (px),Bounding box vertex 3 Y (px),"\
    "Bounding box vertex 4 X (px),Bounding box vertex 4 Y (px)";

using namespace cv;
using namespace std;

class CmtTracker : public Tracker{
	private: 
		//CMT cmt;
		//Rect curBox;
		vector<CMT> cmts;
		vector<Rect> curBoxes;
		Mat curIm; // Default is grayscale
		bool reInit;
	public:
		CmtTracker() {
			CMT cmt;
			reInit = true;
		}

		void startDetect(){
			reInit = true;
		}

		Rect getRect(CMT & cmt) {
		    return cmt.bb_rot.boundingRect();
		}

		Mat imToGray(const Mat& im) {
			Mat im_gray;
			if (im.channels() > 1) {
				cvtColor(im, im_gray, CV_BGR2GRAY);
			} else {
				im_gray = im;
			}
			return im_gray;
		}		

		void initImage(const Mat& im0) {
			Mat im0_gray = imToGray(im0);
		    curIm = im0_gray;
		}

		void initCmt(CMT& cmt, const Rect& curBox) {
			cmt.initialize(curIm, curBox);			
		}

		void init(const Rect& _box) {
			CMT cmt;
			cmts.push_back(cmt);
			FILELog::ReportingLevel() = logINFO;
			cmts.back().consensus.estimate_scale = false;			
			initCmt(cmts.back(), _box);
		}

		Rect process(CMT& cmt, const Mat& im_gray) {			
			cmt.processFrame(im_gray);
			Rect curBox = getRect(cmt);
			return curBox;
		}

		vector<Rect> detect(const Mat& pre, const Mat& now, vector<Rect> boxes){
			if (boxes.empty())
				return boxes;
			if (reInit) {
				cmts.clear();
				curBoxes.clear();
				
				initImage(pre);
				for(const Rect& box: boxes)
					init(box);
				
				reInit = false;
			}
			
			Mat im_gray = imToGray(now);
			vector<Rect> result;
			
			for(int i = 0; i < (int)boxes.size(); ++i)
				result.push_back(process(cmts[i], im_gray));
			return result;
		}
	
};

#endif