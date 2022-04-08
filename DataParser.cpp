#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <inttypes.h>

#include "DataParser.h"

using namespace std;

/*
* Constructor
*
* allocates data vector
*/
DataParser::DataParser(){
    data = new vector<DataParser::PixelChange*>;
}


/*
* parseRawData
*
* parses the raw data into a data structure that is much smaller (20Gb -> 3Gb)
* 
* filename - Reddit's is "2022_place_canvas_history.csv" by default
* 
*/
void DataParser::parseRawData(string const &filename){
    ifstream fp;
    bool firstLine = true;

    // counter keeps track of which line of raw data is being read
    // skips the first line, which is a header
    int lineCount = 0;

    try{
        fp.open(filename, ios::in);

        if(!fp || !fp.is_open()){
            cout << "File not found" << endl;
            return;
        }

        // loop through lines
        while(!fp.eof()){
            string rawLine;
            getline(fp, rawLine);

            // skip first line as this is a header
            if(!rawLine.compare("") || firstLine){
                firstLine = false;
                continue;
            }

            // print status occasionally
            int lowBits = lineCount & 0x000FFFFF;
            if(lowBits == 0){
                cout << "current count: " << lineCount << endl;
            }

            // preprocess line of data
            string line;
            for(size_t i = 0; i < rawLine.size(); ++i){
                switch(rawLine[i]){
                    case '\"':
                    case '\n':
                    case '#':
                        break;
                    case ':':
                    case '.':
                    case ' ':
                        line += '-';
                        break;
                    default:
                        line += rawLine[i];
                        break;
                }
            }
            line += ',';

            size_t pos = 0;
            int count = 0;
            string val;
            // make new PixelChange
            DataParser::PixelChange* pixelChange = new PixelChange;
            // set initial values
            pixelChange->positions.pos2x = 0;
            pixelChange->positions.pos2y = 0;
            pixelChange->color.padding = 0;

            // loop through comma separated substring and get each value of it
            while ((pos = line.find(',')) != string::npos) {
                // get substring
                val = line.substr(0, pos);
                
                size_t valPos = 0;
                string valSplit;
                int valCount = 0;
                uint32_t color;

                string zeros = "00";

                // place substring into specific spot in struct
                switch(count){
                    case 0:
                        // split val string by '-'
                        while((valPos = val.find('-')) != string::npos){
                            valSplit = val.substr(0,valPos);
                            // parse split string into its separate values
                            switch(valCount){
                                case 1:
                                    pixelChange->date.month = (uint8_t) stoi(valSplit);
                                    break;
                                case 2:
                                    pixelChange->date.day = (uint8_t) stoi(valSplit);
                                    break;
                                case 3:
                                    pixelChange->time.hour = (uint8_t) stoi(valSplit);
                                    break;
                                case 4:
                                    pixelChange->time.minute = (uint8_t) stoi(valSplit);
                                    break;
                                case 5:
                                    pixelChange->time.second = (uint16_t) stoi(valSplit);
                                    break;
                                case 6:
                                    pixelChange->time.millisecond = (uint16_t) stoi(valSplit);
                                    break;
                                default:
                                    break;
                            }
                            val.erase(0, valPos + 1);
                            valCount ++;
                        }
                        break;
                    case 1:
                        break;
                    case 2:
                        // split color into R G B values
                        color = (uint32_t) stoi(zeros + val,nullptr,16);
                        pixelChange->color.red = (uint8_t) (color >> 16);
                        pixelChange->color.green = (uint8_t) ((color >> 8) & 0xFF);
                        pixelChange->color.blue = (uint8_t) (color & 0xFF);
                        break;
                    case 3:
                        pixelChange->positions.pos1x = (uint16_t) stoi(val);
                        break;
                    case 4:
                        pixelChange->positions.pos1y = (uint16_t) stoi(val);
                        break;
                    case 5:
                        pixelChange->positions.pos2x = (uint16_t) stoi(val);
                        break;
                    case 6:
                        pixelChange->positions.pos2y = (uint16_t) stoi(val);
                        break;
                }
                // set the value in the array
                line.erase(0, pos + 1);
                count++;
            }
            data->push_back(pixelChange);
            
            // cout << (uint32_t) pixelChange->time.millisecond << endl;

            lineCount++;
        }
    }
    catch (const ifstream::failure& e) {
        cout << "ERROR: could not open or read input file" << endl;
        return;
    }

    cout << "Raw Data successfully read. " << data->size() << " pixel changes were processed" << endl;
}


/*
* saveData
*
* saves the 3Gb data into a file so parsing doesnt always need to happen
*
* filename - name of file to save to. This file is completely overwritten.
*/
void DataParser::saveData(string const &filename){
    if(remove(filename.c_str()) != 0){
        cout << "Failed to remove existing file (it may have been non-existent)" << endl;
    }

    ofstream fp;
    fp.open(filename, ios::app);

    for(auto pixelChange: *data){
        fp.write((char *) pixelChange, sizeof(PixelChange));
    }

    cout << data->size() << " pixel changes were saved to "<< filename << endl;
}


/*
* loadData
*
* loads the 3Gb data from a file into memory
*
* filename - name of file to load from
*/
void DataParser::loadData(string const &filename){
    ifstream fp;
    fp.open(filename, ios::binary);
    // check if it exists
    if(!fp){
        cout << "File not found" << endl;
        return;
    }

    // clear memory of current data vector
    for(auto pixelChange: *data){
        delete pixelChange;
    }
    // clear vector
    data->clear();

    while(!fp.eof()){
        // allocate new pixelChange
        DataParser::PixelChange* pixelChange = new PixelChange;
        // read from file
        fp.read((char *) pixelChange, sizeof(PixelChange));
        // add to vector
        data->push_back(pixelChange);
    }

    // delete last element
    delete data->back();
    data->pop_back();

    cout << data->size() << " pixel changes were loaded from "<< filename << endl;
}


/*
* getData
*
* returns a pointer to the data vector that stores the 3Gb data
*/
vector<DataParser::PixelChange*>* DataParser::getData(){
    return data;
}


/*
* printData
*
* prints the 3Gb data.
* should ONLY be used for testing.
*/
void DataParser::printData(){
    cout << "Data Size: " << data->size() << endl;

    for(auto pixelChange: *data){
        cout << (uint32_t) pixelChange->time.millisecond << endl;
    }
}


/*
* Destructor
*
* frees memory
*/
DataParser::~DataParser(){
    for(auto pixelChange: *data){
        delete pixelChange;
    }

    delete data;
}