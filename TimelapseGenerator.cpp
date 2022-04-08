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

TimelapseGenerator::TimelapseGenerator(DataParser* parser){
    vector<DataParser::PixelChange*>* data = parser->getData();

    uint16_t x1 = 0;
    uint16_t y1 = 950;
    uint16_t x2 = 199;
    uint16_t y2 = 1149;

    uint32_t growthFactor = 20;

    uint32_t imageSpacing = 0x000007FF;

    uint32_t startImage = 900;

    uint16_t width = x2 - x1 + 1;
    uint16_t height = y2 - y1 + 1;

    const string front = "output_images/image";
    const string end = ".png";

    // create matrix for timelapse image
    Mat img(height, width, CV_8UC3, Vec3b(255, 255, 255));

    uint32_t changeCount = 0;
    uint32_t imageCount = 0;

    for(auto pixelChange: *data){
        // skip all admin edits
        if(pixelChange->positions.pos2x != 0){
            continue;
        }

        uint16_t posX = pixelChange->positions.pos1x;
        uint16_t posY = pixelChange->positions.pos1y;
        // if pixel in range
        if(posX >= x1 && posX <= x2 && posY >= y1 && posY <= y2){

            img.at<Vec3b>(posY - y1, posX - x1) = Vec3b((uchar) pixelChange->color.blue, (uchar) pixelChange->color.green, (uchar) pixelChange->color.red);
            // assert(posX - x1 >= 0 && posX - x1 < width);
            // assert(posY - y1 >= 0 && posY - y1 < height);
            // cout << "posX: " << posX - x1<< "posY: " << posY - y1 << endl;

            // write image sometimes
            if((changeCount & imageSpacing) == 0){
                // dont start making images until start
                if(imageCount < startImage){
                    imageCount++;
                    changeCount++;
                    continue;
                }

                uint32_t bigHeight = (uint32_t) height * growthFactor;
                uint32_t bigWidth = (uint32_t) width * growthFactor;
                Mat* bigImg = new Mat(bigHeight, bigWidth, CV_8UC3);

                // create larger image
                for(uint32_t i = 0; i < (uint32_t) height; i++){
                    for(uint32_t j = 0; j < (uint32_t) width; j++){
                        // get pixel
                        Vec3b pixel = img.at<Vec3b>(i, j);
                        // loop through box of larger image
                        for(uint32_t k = 0; k < growthFactor; k++){
                            for(uint32_t l = 0; l < growthFactor; l++){
                                // set pixel of large image
                                bigImg->at<Vec3b>(i*growthFactor + k, j*growthFactor + l) = pixel;
                            }
                        }
                    }
                }

                // write the image
                imwrite(front + to_string(imageCount) + end, *bigImg);
                imageCount ++;

                // free mem
                delete bigImg;
            }
            changeCount ++;
        }
    }

    cout << "number of pixel changes to image: " << changeCount << endl;
    cout << "number of images saved: " << imageCount << endl;
}

TimelapseGenerator::~TimelapseGenerator(){

}