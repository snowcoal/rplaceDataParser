EXENAME = rPlaceDataViewer
OBJS = main.o DataParser.o

CXX = g++
CXXFLAGS = -std=c++1y -c -g -O0 -Wall -Wextra -pedantic
LD = g++
LDFLAGS = -std=c++1y -lc++abi -lm

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

clean :
	-rm -f *.o