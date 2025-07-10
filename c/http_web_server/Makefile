# Simple HTTP Web Server Makefile
# Created by Ryan Rustill

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = server
SOURCE = server.c

# Default target - build the server
all: $(TARGET)

# Build the server executable
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)
	@echo "HTTP Server compiled successfully!"
	@echo "Run with: ./$(TARGET)"
	@echo "Visit: http://localhost:8080"

# Clean up compiled files
clean:
	rm -f $(TARGET)
	@echo "Cleaned up compiled files"

# Run the server (for convenience)
run: $(TARGET)
	@echo "Starting HTTP Server..."
	./$(TARGET)

# Show help
help:
	@echo "Available commands:"
	@echo "   make       - Compile the server"
	@echo "   make run   - Compile and run the server"
	@echo "   make clean - Remove compiled files"
	@echo "   make help  - Show this help"

.PHONY: all clean run help 