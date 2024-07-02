# CXX Make variable for compiler
CC=gcc
# -std=c++11  C/C++ variant to use, e.g. C++ 2011
# -Wall       show the necessary warning files
# -g3         include information for symbolic debugger e.g. gdb 
CFLAGS=-std=c11 -Wall -g3

# object files
OBJS = tree.o countsubstrings.o 

# Program name
PROGRAM = countsubstrings

# Rules format:
# target : dependency1 dependency2 ... dependencyN
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target
# $^ is an example of a special variable.  It substitutes all dependencies
all: $(PROGRAM)
%.o: %.c tree.h
	$(CC) $(CFLAGS) -c $< -o $@
$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	
clean :
	rm -f $(OBJS) $(PROGRAM)

