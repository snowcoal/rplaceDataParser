EXENAME = rPlaceDataViewer
OBJS = main.o DataParser.o TimelapseGenerator.o

CXX = g++
CXXFLAGS = -std=c++1y -c -g -O0 -Wall -Wextra -pedantic
LD = g++
LDFLAGS = -std=c++1y -lc++abi -lm

CXXFLAGS += -c -Wall $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs --static opencv)

.PHONY: clean output_msg

all : $(EXENAME)

$(EXENAME) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

# main:
	
main.o : main.cpp DataParser.h TimelapseGenerator.h
	$(CXX) $(CXXFLAGS) main.cpp
 
# DataParser:

DataParser.o: DataParser.cpp DataParser.h
	$(CXX) $(CXXFLAGS) DataParser.cpp

# TimelapseGenerator:

TimelapseGenerator.o: TimelapseGenerator.cpp TimelapseGenerator.h DataParser.h
	$(CXX) $(CXXFLAGS) TimelapseGenerator.cpp

clean :
	-rm -f *.o