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
		CMT cmt;
		Rect curBox;
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

		void initBox(const Rect& _box) {
			curBox = _box;
		}

		void initImage(const Mat& im0) {
			Mat im0_gray = imToGray(im0);
		    curIm = im0_gray;
		}

		void initCmt() {
			cmt.initialize(curIm, curBox);
		}

		void init(const Rect& _box, const Mat& _im) {
			CMT newCmt;
			cmt = newCmt;
			FILELog::ReportingLevel() = logINFO;
			cmt.consensus.estimate_scale = false;
			initBox(_box);
			initImage(_im);
			initCmt();
		}

		Rect process(const Mat& im) {
			Mat im_gray = imToGray(im);
			cmt.processFrame(im_gray);
			curBox = getRect(cmt);
			return curBox;
		}

		vector<Rect> detect(const Mat& pre, const Mat& now, vector<Rect> boxes){
			if (boxes.empty())
				return boxes;
			if (reInit) {
				init(boxes[0], pre);
				reInit = false;
			}
			vector<Rect> result;
			result.push_back(process(now));
			return result;
		}
	
};

#endif