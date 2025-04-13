# Compiler to use
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra -g -O3

# Source directories
DAYS = day1 day2 day3 day4

# Output binaries
EXEC = $(DAYS:%=%/main)

# Default target
all: $(EXEC)

# Rule to build each day's binary
$(DAYS:%=%/main): %/main: %/main.cpp
	$(CC) $(CFLAGS) -o $@ $<

# Automatic dependency generation
DEPFLAGS = -MT $@ -MMD -MP -MF $*.d
COMPILE.cpp = $(CC) $(DEPFLAGS) $(CFLAGS) -c

# Include dependency files
DEPFILES = $(DAYS:%=%/main.d)
-include $(DEPFILES)

# Clean up
clean:
	rm -f $(EXEC) $(DEPFILES)

# Phony targets
.PHONY: all clean

# Ensure dependency files are generated
%.d: ;
.PRECIOUS: %.d