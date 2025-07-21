# Makefile for Load Balancer Simulation
# Author: Your Name
# Date: 2024

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
DEBUGFLAGS = -std=c++17 -Wall -Wextra -g -DDEBUG

# Source files
SOURCES = main.cpp Request.cpp WebServer.cpp RequestQueue.cpp LoadBalancer.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Target executable
TARGET = loadbalancer

# Default target
all: $(TARGET)

# Debug build
debug: CXXFLAGS = $(DEBUGFLAGS)
debug: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET) loadbalancer_log.txt

# Run the program
run: $(TARGET)
	./$(TARGET)

# Install dependencies (for Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install -y build-essential g++

# Generate Doxygen documentation
docs:
	doxygen Doxyfile

# Create distribution package
dist: clean
	mkdir -p loadbalancer_dist
	cp *.cpp *.h Makefile README.md loadbalancer_dist/
	tar -czf loadbalancer.tar.gz loadbalancer_dist/
	rm -rf loadbalancer_dist

# Help target
help:
	@echo "Available targets:"
	@echo "  all        - Build the load balancer simulation (default)"
	@echo "  debug      - Build with debug information"
	@echo "  clean      - Remove build files and logs"
	@echo "  run        - Build and run the simulation"
	@echo "  install-deps - Install build dependencies (Ubuntu/Debian)"
	@echo "  docs       - Generate Doxygen documentation"
	@echo "  dist       - Create distribution package"
	@echo "  help       - Show this help message"

.PHONY: all debug clean run install-deps docs dist help 