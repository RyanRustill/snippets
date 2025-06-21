# Simple Makefile for ASCII Pattern Generator
# Just like CS50 but with math library support!

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lm

# Main target
pattern_generator: pattern_generator.c
	$(CC) $(CFLAGS) -o pattern_generator pattern_generator.c $(LIBS)

# Clean up compiled files
clean:
	rm -f pattern_generator

# Run all patterns (for testing)
demo: pattern_generator
	@echo "🎨 ASCII Pattern Generator Demo"
	@echo "================================"
	@echo "\n1. Mandelbrot Set:"
	@./pattern_generator mandelbrot
	@echo "\n2. Spiral Pattern:"
	@./pattern_generator spiral
	@echo "\n3. Wave Pattern:"
	@./pattern_generator wave
	@echo "\n4. Diamond Pattern:"
	@./pattern_generator diamond

# Default pattern (no arguments)
run: pattern_generator
	./pattern_generator

.PHONY: clean demo run 