ifeq ($(OS),Windows_NT)
	COMMAND = g++ -Wall -o run humanDetection/peopledetection.cpp -I D:/Development/Opencv/opencv/build/include/opencv -I D:/Development/Opencv/opencv/build/include/ -L D:\Development/opencv-2.4.13/build/lib -lopencv_core2413 -lopencv_highgui2413 -lopencv_imgproc2413 -lopencv_legacy2413 -lopencv_objdetect2413
else
	COMMAND = g++ humanDetection/peopledetection.cpp -o run `pkg-config --cflags --libs opencv`
endif

all:
	$(COMMAND)
