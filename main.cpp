#include "DataParser.h"
#include "TimelapseGenerator.h"

#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

int main(){
    // example

    // location of raw data
    const string filename = "/mnt/d/rPlace/2022_place_canvas_history.csv";
    // location of 3Gb output file
    const string output = "/mnt/d/rPlace/binary.data";

    // create a DataParser object
    DataParser parser;

    // // parse the raw data (takes a while and should only be done one time ever)
    // parser.parseRawData(filename);
    // // dump the parsed data into an output file
    // parser.saveData(output);

    // load the parsed data from the file (done instead of parsing the data again)
    parser.loadData(output);

    TimelapseGenerator tm(&parser);

    return 0;
}