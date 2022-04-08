#pragma once

#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

class DataParser
{
    public:
        // holds date of pixel change
        struct Date{
            uint8_t month;
            uint8_t day;
        };

        // holds time of pixel change
        struct Time{
            uint8_t hour;
            uint8_t minute;
            uint16_t second;
            uint16_t millisecond;
        };

        // holds positional values of pixel change
        struct Positions{
            uint16_t pos1x;
            uint16_t pos1y;
            uint16_t pos2x;
            uint16_t pos2y;
        };

        // holds color of pixel change
        struct Color{
            uint8_t red;
            uint8_t green;
            uint8_t blue;
            // unused padding byte
            uint8_t padding;
        };
        
        // top level struct to hold all smaller data structs
        struct PixelChange{
            Date date;
            Time time;
            Positions positions;
            Color color;
        };

        // constructor
        DataParser();
        // destructor
        ~DataParser();
        // get the pixel change vector
        vector<PixelChange*>* getData();
        // parse the raw data into PixelChanges
        void parseRawData(string const &filename);
        // save curated data to file
        void saveData(string const &filename);
        // load curated data into data vector
        void loadData(string const &filename);
        // prints ENTRE data vector, used for testing ONLY
        void printData();
    private:
        // stores all pixel changes
        vector<PixelChange*>* data;
        
};