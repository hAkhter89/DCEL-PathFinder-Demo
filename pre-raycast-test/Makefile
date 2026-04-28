# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Project files
TARGET = dcel_test
SRCS = dceltest.cpp DCEL.cpp DCELBuilder.cpp DCELpath.cpp SandboxSeeker.cpp

# Default rule: build the game directly from source
all: $(TARGET)

# Compile everything straight into the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

# Clean rule to wipe just the executable
clean:
	rm -f $(TARGET)