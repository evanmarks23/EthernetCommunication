CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

SRCS = main.cpp EthernetDriver.cpp EthernetFrame.cpp Protocol.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	del /Q *.o 2>nul
	del /Q $(TARGET) 2>nul
else
	rm -f *.o
	rm -f $(TARGET)
endif

# Phony targets
.PHONY: all clean test
