FILES = HumanDetection/peopledetection.cpp *.o

ifeq ($(OS),Windows_NT)
	LIB = -I D:/Development/Opencv/opencv/build/include/opencv -I D:/Development/Opencv/opencv/build/include/ -L D:\Development/opencv-2.4.13/build/lib -lopencv_core2413 -lopencv_highgui2413 -lopencv_imgproc2413 -lopencv_legacy2413 -lopencv_objdetect2413 -lopencv_video2413
else
	LIB = `pkg-config --cflags --libs opencv`
endif

ifneq ("$(wildcard dpm_nms.o)","")
	PRE_COMMAND = echo compile dpm
else
	PRE_COMMAND = g++ -c HumanDetection/DPM/*.cpp $(LIB)
endif


COMMAND = g++ $(FILES) -o run $(LIB)


all:
	$(PRE_COMMAND)
	$(COMMAND)
