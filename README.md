# rplaceDataParser
Parses the Raw data from reddit's r/place into an easy to use data structure that is only 3Gb in size vs the original 20Gb

See example code on how to parse the raw data

Also includes a timelapse generator (under development) and other features

timelapse generator currently requires openCV to be installed, but the dataParser itself does not depend on anything.

IF timelapse generator is NOT wanted, replace the default makefile with the one located in the alternate_makefile, which will
ONLY compile the parser and main.cpp