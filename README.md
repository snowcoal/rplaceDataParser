# rplaceDataParser
Parses the Raw data from reddit's r/place into an easy to use data structure that is only 3Gb in size vs the original 20Gb

See example code on how to parse the raw data

Also includes a timelapse generator (under development) and other features

timelapse generator currently requires openCV to be installed, but the dataParser itself does not depend on anything.

IF timelapse generator is NOT wanted, replace the default makefile with the one located in the alternate_makefile, which will
ONLY compile the parser and main.cpp

# example

````

    int main(){
        // example

        // location of raw data
        const string filename = "/mnt/d/rPlace/2022_place_canvas_history.csv";
        // location of 3Gb output file
        const string output = "/mnt/d/rPlace/binary.data";

        // create a DataParser object
        DataParser parser;

        // parse the raw data (takes a while and should only be done one time ever)
        parser.parseRawData(filename);
        // dump the parsed data into an output file
        parser.saveData(output);

        // load the parsed data from the file (done instead of parsing the data again)
        parser.loadData(output);

        return 0;
    }

````