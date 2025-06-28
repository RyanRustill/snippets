# Makefile for Collision Explosions
# Handles SDL2 compilation and linking

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LIBS = -lSDL2 -lm
TARGET = pixel_renderer
SOURCE = pixel_renderer.c

# Default target - build the program
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

# Install SDL2 development libraries (Ubuntu/Debian)
install-deps:
	sudo apt update
	sudo apt install libsdl2-dev

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up compiled files
clean:
	rm -f $(TARGET)

# Build and run in one command
build-run: $(TARGET) run

# Help target
help:
	@echo "Collision Explosions Build System"
	@echo "================================="
	@echo "make          - Build the program"
	@echo "make run      - Run the program" 
	@echo "make clean    - Remove compiled files"
	@echo "make build-run - Build and run in one step"
	@echo "make install-deps - Install SDL2 (Ubuntu/Debian)"

.PHONY: all run clean build-run install-deps help 