
# Compiler
CC = g++

# Compiler Flags
CFLAGS = -g -Wall

# Build Target
TARGET = main

# List all source files
SOURCES = \
io_handlers/*.cpp \
rands/*.cpp \
events/*.cpp \
process/*.cpp  

all:$(TARGET)

# TODO: remove validator_factory
$(TARGET): main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp $(SOURCES) -I . -I io_handlers -I rands -I events -I process


run:
	./main -sR10 -v lab2_assign/input0 lab2_assign/rfile
	
clean:
	$(RM) $(TARGET)
	$(RM) *.o
