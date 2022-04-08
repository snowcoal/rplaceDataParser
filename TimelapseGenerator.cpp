#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <inttypes.h>

#include "TimelapseGenerator.h"
#include "DataParser.h"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

TimelapseGenerator::TimelapseGenerator(){
    // cv::Mat img;  // variable image of datatype Matrix
    // img = cv::imread("/mnt/c/users/caleb/projects/rplacebot/fsnplace/final.png");
    //     // For color image i.e. 3 channel
    // Vec3b intensity = img.at<Vec3b>(10, 10);
    // cout << "BGR " << intensity << "\n";

    // // print individual component [B G R]
    // int blue = intensity.val[0];
    // cout << "blue " << blue << "\n";
    // int green = intensity.val[1];
    // cout << "green " << green << "\n";
    // int red = intensity.val[2];
    // cout << "red " << red << "\n";


    // // modify pixel
    // img.at<Vec3b>(10, 10) = (0, 0, 255);
    // // For color image i.e. 3 channel
    // intensity = img.at<Vec3b>(10, 10);
    // cout << "BGR after modification " << intensity << "\n";
}