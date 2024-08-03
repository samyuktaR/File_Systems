# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11 -Wall -Wextra

# Executable name
EXEC = stupidos

# Source files
SRCS = FileSystem_ramkumar.cpp stupidOS_ramkumar.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Dependency files
DEPS = $(OBJS:.o=.d)

# Default rule
all: $(EXEC)

# Compile rule
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Generate dependency files
%.d: %.cpp
	$(CC) -MM -MP -MT '$(<:.cpp=.o) $@' -MF $@ $<

# Include dependency files
-include $(DEPS)

# Clean rule
clean:
	rm -f $(EXEC) $(OBJS) $(DEPS)

# Phony targets
.PHONY: all clean