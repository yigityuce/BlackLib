CXX=arm-linux-gnueabi-g++

INCLUDES=-I/usr/arm-linux-gnueabi/include/c++/4.6.3

CPPFLAGS=-D__GXX_EXPERIMENTAL_CXX0X__ -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1 -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2 -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4 -D__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8

CXXFLAGS=-std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -pthread $(CPPFLAGS) $(INCLUDES)

LDFLAGS=-lpthread

LDLIBS=-L/usr/arm-linux-gnueabi/lib

RM=rm -f

SOURCES=./BlackADC/BlackADC.cpp ./BlackDirectory/BlackDirectory.cpp  ./BlackGPIO/BlackGPIO.cpp ./BlackI2C/BlackI2C.cpp ./BlackMutex/BlackMutex.cpp ./BlackPWM/BlackPWM.cpp ./BlackSPI/BlackSPI.cpp ./BlackThread/BlackThread.cpp ./BlackTime/BlackTime.cpp  ./BlackUART/BlackUART.cpp ./BlackCore.cpp ./examples.cpp

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=BlackLib-executable


all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDLIBS) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS)

