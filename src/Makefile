# Simple Makefile example
CXX      := clang++
CXXFLAGS := -std=c++20 -Wall
EXEC     := watopoly

# Collect all .cc files from the project (top-level and subdirectories)
SOURCES := $(wildcard *.cc) \
           $(wildcard Buildings/*.cc) \
           $(wildcard Commands/*.cc) \
           $(wildcard Board/*.cc) \
           $(wildcard Dice/*.cc)

# Generate corresponding .o files
OBJECTS := $(SOURCES:.cc=.o)

# Default target
all: $(EXEC)

# Link the final executable
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cc into an .o
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJECTS) $(EXEC)

.PHONY: all clean
