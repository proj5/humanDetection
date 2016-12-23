#ifndef _MC_CONFIG
#define _MC_CONFIG 1

#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "Detector.h"
#include "DefaultDetector.h"
#include "TestDetector.h"

using namespace std;

struct Config {
	static const string VIDEO;
	static const string WIDTH;
	static const string HEIGHT;
	static const string DETECTOR;
		
	map<string, string> config;
	int width = 640;
	int height = 480;
	string video = "0";
	string detector = "DEFAULT_DETECTOR";
	
	bool checkConfig(string key){
		return config.find(key) != config.end();
	}
	
		
	Config(string name = "config.txt") {
		ifstream fi(name);
		string line;
		while (getline(fi, line)){
			stringstream ss(line);
			string key, value;
			getline(ss, key, '=');
			getline(ss, value);
			config[key] = value;
		}
		
		if (checkConfig(VIDEO))
			video = config[VIDEO];
		
		if (checkConfig(WIDTH))
			width = atoi(config[WIDTH].c_str());
		
		if (checkConfig(HEIGHT))
			height = atoi(config[HEIGHT].c_str());
		
		if (checkConfig(DETECTOR))
			detector = config[DETECTOR];
		
		
		//cout << video << " " << width << " " << height << endl;
	}
	
	int getWidth(){
		return width;		
	}
	
	int getHeight(){
		return height;		
	}
	
	string getVideo(){
		return video;
	}
	
	Detector* getDetector(){
		if (detector == "DEFAULT_DETECTOR")
			return new DefaultDetector;
		
		if (detector == "TEST_DETECTOR")
			return new TestDetector;
		
		return new DefaultDetector;
	}
	
};

const string Config::VIDEO = "VIDEO";
const string Config::WIDTH = "WIDTH";
const string Config::HEIGHT = "HEIGHT";
const string Config::DETECTOR = "DETECTOR";

#endif