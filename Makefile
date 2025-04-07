# Compiler to use
CC = g++

# Compiler flags
CFLAGS = -Wall -g

# Default target
all: day1/day1_main

# Rule for day1 binary
day1/day1_main: day1/main.cpp
	$(CC) $(CFLAGS) -o day1/day1_main day1/main.cpp

# Rule for day2 binary
day2/day2_main: day2/main.cpp
	$(CC) $(CFLAGS) -o day2/day2_main day2/main.cpp

# Clean up
clean:
	rm -f day1/day1_main day2/day2_main

# Phony targets
.PHONY: all clean