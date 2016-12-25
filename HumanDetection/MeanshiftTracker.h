#ifndef _MC_MEANSHIFT_TRACKER_H
#define _MC_MEANSHIFT_TRACKER_H 1

#include <opencv2/opencv.hpp>
#include "DefaultDetector.h"

using namespace cv;
using namespace std;

class MeanshiftTracker : public Tracker {
	private:		
	public:		
		MeanshiftTracker() {}
		
		void nor(const Mat& img, Rect& box){
			if (box.x + box.width > img.cols)
				box.width = img.cols - box.x;
			if (box.y + box.height > img.rows)
				box.height = img.rows - box.y;
		}
		
		void run(const Mat& preImg, const Mat& img, Rect& selection){
			nor(img, selection);
			int hsize = 16;
			float hranges[] = {0,180};
			const float* phranges = hranges;
			int vmin = 10, vmax = 256, smin = 30;
			int trackObject = -1;
			
			Rect trackWindow;
			Mat frame, hsv, hue, mask, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;
			int _vmin = vmin, _vmax = vmax;
			
			for (int i = 0; i < 2; ++i){
				if (i == 0)
					cvtColor(preImg, hsv, COLOR_BGR2HSV);
				else
					cvtColor(img, hsv, COLOR_BGR2HSV);
				inRange(hsv, Scalar(0, smin, MIN(_vmin,_vmax)),
						Scalar(180, 256, MAX(_vmin, _vmax)), mask);
				int ch[] = {0, 0};
				hue.create(hsv.size(), hsv.depth());
				mixChannels(&hsv, 1, &hue, 1, ch, 1);

				 if( trackObject < 0 )
				 {
					 Mat roi(hue, selection), maskroi(mask, selection);
					 calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
					 normalize(hist, hist, 0, 255, NORM_MINMAX);

					 trackWindow = selection;
					 trackObject = 1;

					 histimg = Scalar::all(0);
					 int binW = histimg.cols / hsize;
					 Mat buf(1, hsize, CV_8UC3);
					 for( int i = 0; i < hsize; i++ )
						 buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180./hsize), 255, 255);
					 cvtColor(buf, buf, COLOR_HSV2BGR);

					 for( int i = 0; i < hsize; i++ )
					 {
						 int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);
						 rectangle( histimg, Point(i*binW,histimg.rows),
									Point((i+1)*binW,histimg.rows - val),
									Scalar(buf.at<Vec3b>(i)), -1, 8 );
					 }
				 }

				 calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
				 backproj &= mask;
				 meanShift(backproj, trackWindow,
									 TermCriteria( TermCriteria::EPS | TermCriteria::COUNT, 10, 1 ));
				 if( trackWindow.area() <= 1 )
				 {
					 int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5)/6;
					 trackWindow = Rect(trackWindow.x - r, trackWindow.y - r,
										trackWindow.x + r, trackWindow.y + r) &
								   Rect(0, 0, cols, rows);
				 }
			}
			
			selection = trackWindow;

			 //if( backprojMode ) cvtColor( backproj, image, COLOR_GRAY2BGR );
			 //ellipse( image, trackBox, Scalar(0,0,255), 3);
			 //rectangle(image, trackWindow.tl(), trackWindow.br(), cv::Scalar(0, 255, 0), 2);
		}
		
		vector<Rect> detect(const Mat& pre, const Mat& now, vector<Rect> boxes) {
			for(auto& box: boxes)
				run(pre, now, box);
			return boxes;
		}
		
		~MeanshiftTracker() {			
		}
	
};

#endif