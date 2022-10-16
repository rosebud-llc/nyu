
# Compiler
CC = g++

# Compiler Flags
CFLAGS = -g -Wall

# Build Target
TARGET = main

# List all source files
SOURCES = \
events/*.cpp \
process/*.cpp 

all:$(TARGET)

# TODO: remove validator_factory
$(TARGET): main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp $(SOURCES) -I . -I events -I process


run:
	./main
	
clean:
	$(RM) $(TARGET)
	$(RM) *.o
