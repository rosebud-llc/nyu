
# Compiler
CC = g++

# Compiler Flags
CFLAGS = -g -Wall

# Build Target
TARGET = main

# List all source files
# TODO: remove validator_factory
SOURCES = io_handlers/*.cpp validators/*.cpp validator_factory/*.cpp validator_data/*.cpp validator_handlers/*.cpp validator_queue/*.cpp tokenizer/*.cpp

all:$(TARGET)

# TODO: remove validator_factory
$(TARGET): linker.cpp
	$(CC) $(CFLAGS) -o $(TARGET) linker.cpp $(SOURCES) -I . -I io_handlers -I validators -I validator_factory -I validator_data -I validator_handlers -I validator_queue -I tokenizer

run:
	./main -i test_file.txt
	
clean:
	$(RM) $(TARGET)
	$(RM) *.o