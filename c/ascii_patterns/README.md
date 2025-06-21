# 🎨 ASCII Pattern Generator

I just figured out how to turn math equations into actual visual art using nothing but text characters! Coming from basic C programs to generating fractals feels incredible.

## What you'll see
Four different mathematical patterns rendered in ASCII art, from the famous Mandelbrot set to spirals and waves. Each pattern uses different math concepts like complex numbers, polar coordinates, and trigonometry to create surprisingly beautiful terminal art.

## How to run this
```bash
# Compile the program (needs math library)
make

# Generate the default pattern (Mandelbrot set)
./pattern_generator

# Try specific patterns
./pattern_generator mandelbrot    # Classic fractal
./pattern_generator spiral        # Polar coordinate spiral  
./pattern_generator wave          # Sine wave interference
./pattern_generator diamond       # Manhattan distance pattern

# See all patterns at once
make demo
```

## How it works
This was my first time working with 2D arrays and complex mathematical functions in C! The Mandelbrot set blew my mind - you iterate a simple equation (z = z² + c) for each point and the number of iterations determines which character to draw.

The spiral uses polar coordinates (converting x,y to distance and angle), while the wave pattern layers multiple sine functions with different frequencies. The diamond pattern uses Manhattan distance instead of Euclidean distance to create that sharp geometric look.

The coolest part is mapping mathematical concepts to ASCII characters - I use different characters to represent different "densities" or "distances" which creates the visual patterns.

## Try changing this
- **WIDTH/HEIGHT** (lines 7-8): Make bigger patterns (try 80x40 for wide screens)
- **density[] characters** (line 93): Try different character sets like "░▒▓█" for block patterns
- **wave frequencies** (lines 180-182): Change the 0.2, 0.1, 0.15 values for different wave effects
- **spiral equation** (line 158): Modify the "3" and "0.3" values to change spiral tightness
- **Challenge**: Add a new pattern type! Maybe try cellular automata or L-systems

## What I learned
Math and programming together create something way more beautiful than I expected! I learned about:
- Complex number arithmetic (for Mandelbrot set)
- Polar vs Cartesian coordinates (for spiral patterns)
- How trigonometric functions create visual patterns
- Mapping continuous math to discrete character grids
- Why the `-lm` flag is needed (math library linking)

Going from Caesar cipher string manipulation to generating fractals feels like a huge leap, but it's really just applying the same C fundamentals to more complex problems.

## Related concepts
- Fractal geometry and chaos theory
- Computer graphics and rasterization
- Mathematical visualization
- ASCII art and text-based graphics 