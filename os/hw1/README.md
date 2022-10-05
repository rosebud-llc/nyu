# Lab1: Linker

## Instructions
* compile: `make all`
* run: `./main -i <input_file>`
* test: `./runit.sh <output_dir> <executable> <optional_input_args>`
* evaluate tests: `./gradeit.sh . <output_dir>`

## PassOne and PassTwo Functions
* tokenizer/tokenizer.cpp -> `tokenizerPassOne()`
* tokenizer/tokenizer.cpp -> `tokenizerPassTwo()`

## Code Flow
* linker.cpp runs main() by reading in file and processing as filestream
* tokenizer.cpp tokenizes the stream one line at a time
* first pass validates tokenizers using `/validator_handlers` and `/validators`
*  - upon syntax error, program raises error and stops
*  - upon success, symbol table is generated
* second pass processes tokenes using `/processor_handlers`
* - for each line, memory map is generated with associated warnings/errors
* file streams are closed and program ends

## Why is code structured this way?
* I originally wrote a Factory model whereby there was one virtual function
defined by each derived class - one for each validation step Definition, Use, and Program.
However, it turnned out that having a single function to 'process' the data for both
PassOne and PassTwo was not helpful since their requirements are functionally different.
Rather than throw out all the code, I changed the classes such that their member functions
were static and could easily be reused for only PassOne valdiation. Hence, the word 
'validators' is overused.

## Areas for Improvment
* Replace naked pointers with unique pointers; however, this is not available until C++11
* Remove 'validator' from _data/ and _queue/ folders - they are used on both PassOne and PassTwo and do not perform validation.
* Refactor ModuleData by creating PassOneModuleData and PassTwoModuleData since the use cases are mutually exclusive
* Replace cout with proper debug/info/error logging to file
* Create unit tests

