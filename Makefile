# Compiler to use
CC = g++

# Compiler flags
CFLAGS = -Wall -g -O3

# Default target
all: day1/main day2/main day3/main

# Rule for day1 binary
day1/day1_main: day1/main.cpp
	$(CC) $(CFLAGS) -o day1/main day1/main.cpp

# Rule for day2 binary
day2/day2_main: day2/main.cpp
	$(CC) $(CFLAGS) -o day2/main day2/main.cpp

# Rule for day3 binary
day3/day3_main: day3/main.cpp
	$(CC) $(CFLAGS) -o day3/main day3/main.cpp

# Clean up
clean:
	rm -f day1/main day2/main day3/main

# Phony targets
.PHONY: all clean