
# Compiler
CC = g++

# Compiler Flags
CFLAGS = -g -Wall

# Build Target
TARGET = main

# List all source files
SOURCES = io_handlers/*.cpp validators/*.cpp validator_factory/*.cpp tokenizer/*.cpp

all:$(TARGET)

$(TARGET): linker.cpp
	$(CC) $(CFLAGS) -o $(TARGET) linker.cpp $(SOURCES) -I . -I io_handlers -I validators -I validator_factory -I tokenizer
	
clean:
	$(RM) $(TARGET)
	$(RM) *.o