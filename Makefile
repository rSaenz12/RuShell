# Makefile for RuShell Project
# Author: Russell Saenz

CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = RuShell
OBJS = main.o parser.o commandExecuter.o

.PHONY: all clean distclean run

# Default target: compile everything
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp parser.h commandExecuter.h
	$(CXX) $(CXXFLAGS) -c main.cpp

parser.o: parser.cpp parser.h
	$(CXX) $(CXXFLAGS) -c parser.cpp

commandExecuter.o: commandExecuter.cpp commandExecuter.h parser.h
	$(CXX) $(CXXFLAGS) -c commandExecuter.cpp

# Clean up object files and core dumps
clean:
	rm -f $(OBJS) core

# Full clean: also remove the binary
distclean: clean
	rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
