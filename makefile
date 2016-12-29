FILES = HumanDetection/peopledetection.cpp *.o

ifeq ($(OS),Windows_NT)
    # LIB = -I D:/Development/Opencv/opencv/build/include/opencv -I D:/Development/Opencv/opencv/build/include/ -L D:\Development/opencv-2.4.13/build/lib -lopencv_core2413 -lopencv_highgui2413 -lopencv_imgproc2413 -lopencv_legacy2413 -lopencv_objdetect2413 -lopencv_video2413 -lopencv_features2d2413
	LIB = -I "F:/DaiHoc/2016-2017/MultimediaCommunication/opencv/build/include" -I "F:/DaiHoc/2016-2017/MultimediaCommunication/opencv/build/include/opencv" -L "F:/DaiHoc/2016-2017/MultimediaCommunication/Duc/my_build/lib" -llibopencv_core310 -llibopencv_highgui310 -llibopencv_imgproc310 -llibopencv_objdetect310 -llibopencv_video310 -llibopencv_videoio310 -llibopencv_features2d310
else
	LIB = `pkg-config --cflags --libs opencv`
endif

ifneq ("$(wildcard dpm_nms.o)","")
	PRE_DPM = echo compile dpm
else
	PRE_DPM = g++ -O3 -c HumanDetection/DPM/*.cpp $(LIB)
endif

ifneq ("$(wildcard Fusion.o)","")
	PRE_CMT = echo compile CppMT
else
	PRE_CMT = g++ -O3 -c HumanDetection/CppMT/*.cpp HumanDetection/CppMT/fastcluster/*.cpp -I HumanDetection/CppMT $(LIB)
endif


COMMAND = g++ -O3 -std=c++11 $(FILES) -o run $(LIB)


all:
	$(PRE_DPM)
	$(PRE_CMT)
	$(COMMAND)
