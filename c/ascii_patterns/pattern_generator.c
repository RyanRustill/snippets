#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Pattern dimensions
#define WIDTH 60
#define HEIGHT 30

// Pattern types
typedef enum {
    MANDELBROT,
    SPIRAL,
    WAVE,
    DIAMOND
} pattern_type;

// Function prototypes
void generate_mandelbrot(char grid[HEIGHT][WIDTH]);
void generate_spiral(char grid[HEIGHT][WIDTH]);
void generate_wave(char grid[HEIGHT][WIDTH]);
void generate_diamond(char grid[HEIGHT][WIDTH]);
void print_grid(char grid[HEIGHT][WIDTH]);
void print_menu(void);

int main(int argc, char *argv[])
{
    char grid[HEIGHT][WIDTH];
    pattern_type choice = MANDELBROT;
    
    // Clear the grid
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            grid[y][x] = ' ';
        }
    }
    
    // Handle command line arguments (CS50 style!)
    if (argc == 2)
    {
        if (strcmp(argv[1], "mandelbrot") == 0) choice = MANDELBROT;
        else if (strcmp(argv[1], "spiral") == 0) choice = SPIRAL;
        else if (strcmp(argv[1], "wave") == 0) choice = WAVE;
        else if (strcmp(argv[1], "diamond") == 0) choice = DIAMOND;
        else
        {
            printf("Usage: %s [mandelbrot|spiral|wave|diamond]\n", argv[0]);
            return 1;
        }
    }
    else if (argc > 2)
    {
        printf("Usage: %s [mandelbrot|spiral|wave|diamond]\n", argv[0]);
        return 1;
    }
    
    // Show what we're generating
    printf("\n🎨 ASCII Pattern Generator\n");
    printf("===========================\n");
    
    // Generate the chosen pattern
    switch (choice)
    {
        case MANDELBROT:
            printf("Generating Mandelbrot set...\n\n");
            generate_mandelbrot(grid);
            break;
        case SPIRAL:
            printf("Generating spiral pattern...\n\n");
            generate_spiral(grid);
            break;
        case WAVE:
            printf("Generating wave pattern...\n\n");
            generate_wave(grid);
            break;
        case DIAMOND:
            printf("Generating diamond pattern...\n\n");
            generate_diamond(grid);
            break;
    }
    
    // Display the pattern
    print_grid(grid);
    
    // Show menu for next time
    if (argc == 1)
    {
        print_menu();
    }
    
    return 0;
}

// This is where the magic happens! Mandelbrot set in ASCII
void generate_mandelbrot(char grid[HEIGHT][WIDTH])
{
    // ASCII characters ordered by "density" for the fractal
    char density[] = " .:-=+*#%@";
    int density_len = strlen(density);
    
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            // Map screen coordinates to complex plane
            double real = (x - WIDTH/2.0) * 4.0 / WIDTH;
            double imag = (y - HEIGHT/2.0) * 4.0 / HEIGHT;
            
            // Mandelbrot iteration
            double z_real = 0, z_imag = 0;
            int iterations = 0;
            int max_iterations = density_len - 1;
            
            // Keep iterating until we escape or max out
            while (z_real * z_real + z_imag * z_imag < 4 && iterations < max_iterations)
            {
                double temp = z_real * z_real - z_imag * z_imag + real;
                z_imag = 2 * z_real * z_imag + imag;
                z_real = temp;
                iterations++;
            }
            
            // Pick character based on how quickly it escaped
            grid[y][x] = density[iterations];
        }
    }
}

// Create a cool spiral pattern using polar coordinates
void generate_spiral(char grid[HEIGHT][WIDTH])
{
    char spiral_chars[] = "*+=-.:";
    int chars_len = strlen(spiral_chars);
    
    int center_x = WIDTH / 2;
    int center_y = HEIGHT / 2;
    
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            // Calculate distance from center
            int dx = x - center_x;
            int dy = y - center_y;
            double distance = sqrt(dx * dx + dy * dy);
            
            // Calculate angle
            double angle = atan2(dy, dx);
            
            // Create spiral equation: r = a * theta
            double spiral_radius = angle * 3 + distance * 0.3;
            
            // Use modulo to create the spiral pattern
            int pattern_index = ((int)(spiral_radius * 2)) % chars_len;
            
            // Only draw if we're on the spiral "line"
            if (((int)(distance + angle * 5)) % 4 == 0)
            {
                grid[y][x] = spiral_chars[pattern_index];
            }
        }
    }
}

// Generate a sine wave pattern
void generate_wave(char grid[HEIGHT][WIDTH])
{
    char wave_chars[] = "~-_.:*+=@";
    int chars_len = strlen(wave_chars);
    
    for (int x = 0; x < WIDTH; x++)
    {
        // Create multiple sine waves with different frequencies
        double wave1 = sin(x * 0.2) * 8 + HEIGHT / 3;
        double wave2 = sin(x * 0.1) * 6 + HEIGHT * 2 / 3;
        double wave3 = sin(x * 0.15 + 1) * 4 + HEIGHT / 2;
        
        // Draw the waves
        for (int y = 0; y < HEIGHT; y++)
        {
            int char_index = 0;
            
            // Check if we're close to any wave
            if (abs(y - (int)wave1) < 2) char_index = x % chars_len;
            else if (abs(y - (int)wave2) < 2) char_index = (x + 2) % chars_len;
            else if (abs(y - (int)wave3) < 2) char_index = (x + 4) % chars_len;
            
            if (char_index > 0)
            {
                grid[y][x] = wave_chars[char_index];
            }
        }
    }
}

// Create a diamond/rhombus pattern
void generate_diamond(char grid[HEIGHT][WIDTH])
{
    char diamond_chars[] = ".:-=+*#@";
    int chars_len = strlen(diamond_chars);
    
    int center_x = WIDTH / 2;
    int center_y = HEIGHT / 2;
    
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            // Calculate Manhattan distance (diamond shape)
            int distance = abs(x - center_x) + abs(y - center_y);
            
            // Create concentric diamonds
            int layer = distance / 3;
            
            if (layer < chars_len && distance % 3 == 0)
            {
                grid[y][x] = diamond_chars[layer];
            }
        }
    }
}

// Print the generated pattern to the terminal
void print_grid(char grid[HEIGHT][WIDTH])
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            printf("%c", grid[y][x]);
        }
        printf("\n");
    }
}

// Show available patterns
void print_menu(void)
{
    printf("\nAvailable patterns:\n");
    printf("  ./pattern_generator mandelbrot  - Classic fractal set\n");
    printf("  ./pattern_generator spiral      - Mathematical spiral\n");
    printf("  ./pattern_generator wave        - Sine wave pattern\n");
    printf("  ./pattern_generator diamond     - Concentric diamonds\n");
    printf("\nTry them all! Each one uses different math concepts.\n");
} 