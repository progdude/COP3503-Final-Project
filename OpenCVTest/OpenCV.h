//
//  recognize.h
//  OpenCVTest
//
//  Created by Archit Rathi on 4/17/16.
//  Copyright © 2016 Archit Rathi. All rights reserved.
//

#ifndef recognize_h
#define recognize_h
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "User.h"

using namespace std;

using namespace cv;

class OpenCV 
{
private:
    vector<string> label;
    void detectNewUser(Mat &frame, int &j, string name);
    string TRAINEDMODEL = "trainedmodel.yaml";
    
public:
    string recognize(vector<User> users);
    
    void addNewUser(string name, vector<User> users);
    
    
};

#endif /* recognize_h */
