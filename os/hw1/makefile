
# Compiler
CC = g++

# Compiler Flags
CFLAGS = -g -Wall

# Build Target
TARGET = main

# List all source files
SOURCES = io_handlers/*.cpp validators/*.cpp  validator_data/*.cpp validator_handlers/*.cpp processor_handlers/*.cpp validator_queue/*.cpp symbol_table/*.cpp module_data/*.cpp tokenizer/*.cpp

all:$(TARGET)

# TODO: remove validator_factory
$(TARGET): linker.cpp
	$(CC) $(CFLAGS) -o $(TARGET) linker.cpp $(SOURCES) -I . -I io_handlers -I validators -I validator_data -I validator_handlers -I processor_handlers -I validator_queue -I symbol_table -I module_data -I tokenizer

run:
	./main -i lab1_assign/input-11

	
clean:
	$(RM) $(TARGET)
	$(RM) *.o
