/*
 * Collision Explosions - Advanced SDL Graphics
 * 
 * Advanced graphics programming with SDL demonstrating:
 * - Object collision detection
 * - Particle explosion systems
 * - Real-time multi-object physics
 * - Game engine fundamentals
 */

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Screen dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TARGET_FPS 60

// Pattern configuration
#define NUM_SQUARES 8
#define SQUARE_SIZE 50
#define MAX_PARTICLES 200
#define PARTICLE_LIFE 60  // frames

// Color definitions for our rainbow effect
typedef struct {
    Uint8 r, g, b, a;
} Color;

// Square structure - this is like a game object!
typedef struct {
    float x, y;           // Position (using float for smooth movement)
    float dx, dy;         // Velocity
    Color color;          // RGB color
    float rotation;       // Rotation angle
    float rotation_speed; // How fast it spins
    bool active;          // Is this square still alive?
} MovingSquare;

// Particle structure for explosion effects!
typedef struct {
    float x, y;           // Position
    float dx, dy;         // Velocity
    Color color;          // Color that fades over time
    int life;             // Remaining life (frames)
    bool active;          // Is this particle alive?
} Particle;

// Initialize our moving squares with random properties
void init_squares(MovingSquare squares[]) {
    for (int i = 0; i < NUM_SQUARES; i++) {
        // Start at random positions
        squares[i].x = rand() % (SCREEN_WIDTH - SQUARE_SIZE);
        squares[i].y = rand() % (SCREEN_HEIGHT - SQUARE_SIZE);
        
        // Random velocities (movement speed and direction)
        squares[i].dx = ((rand() % 300) - 150) / 50.0f; // -3.0 to +3.0 (faster!)
        squares[i].dy = ((rand() % 300) - 150) / 50.0f;
        
        // Create rainbow colors based on position in array
        float hue = (float)i / NUM_SQUARES; // 0.0 to 1.0
        squares[i].color.r = (Uint8)(255 * (0.5 + 0.5 * sin(hue * 6.28)));
        squares[i].color.g = (Uint8)(255 * (0.5 + 0.5 * sin(hue * 6.28 + 2.09)));
        squares[i].color.b = (Uint8)(255 * (0.5 + 0.5 * sin(hue * 6.28 + 4.18)));
        squares[i].color.a = 255;
        
        // Random rotation properties
        squares[i].rotation = 0;
        squares[i].rotation_speed = ((rand() % 100) - 50) / 100.0f; // -0.5 to +0.5
        squares[i].active = true; // All start active
    }
}

// Initialize particle system
void init_particles(Particle particles[]) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].active = false;
    }
}

// Check if two squares are colliding
bool squares_colliding(MovingSquare* a, MovingSquare* b) {
    return (a->x < b->x + SQUARE_SIZE &&
            a->x + SQUARE_SIZE > b->x &&
            a->y < b->y + SQUARE_SIZE &&
            a->y + SQUARE_SIZE > b->y);
}

// Create explosion at given position with given color
void create_explosion(Particle particles[], float x, float y, Color color) {
    int created = 0;
    for (int i = 0; i < MAX_PARTICLES && created < 25; i++) {
        if (!particles[i].active) {
            particles[i].x = x + SQUARE_SIZE / 2; // Center of explosion
            particles[i].y = y + SQUARE_SIZE / 2;
            
            // Random direction and speed (like fireworks!)
            float angle = ((float)rand() / RAND_MAX) * 6.28f; // 0 to 2π
            float speed = ((float)rand() / RAND_MAX) * 4.0f + 1.0f; // 1 to 5
            particles[i].dx = cos(angle) * speed;
            particles[i].dy = sin(angle) * speed;
            
            particles[i].color = color;
            particles[i].life = PARTICLE_LIFE;
            particles[i].active = true;
            created++;
        }
    }
}

// Update square positions and handle collisions
void update_squares(MovingSquare squares[], Particle particles[]) {
    for (int i = 0; i < NUM_SQUARES; i++) {
        if (!squares[i].active) continue;
        
        // Update position based on velocity
        squares[i].x += squares[i].dx;
        squares[i].y += squares[i].dy;
        
        // Bounce off walls
        if (squares[i].x <= 0 || squares[i].x >= SCREEN_WIDTH - SQUARE_SIZE) {
            squares[i].dx = -squares[i].dx;
        }
        if (squares[i].y <= 0 || squares[i].y >= SCREEN_HEIGHT - SQUARE_SIZE) {
            squares[i].dy = -squares[i].dy;
        }
        
        // Keep within bounds
        if (squares[i].x < 0) squares[i].x = 0;
        if (squares[i].x > SCREEN_WIDTH - SQUARE_SIZE) squares[i].x = SCREEN_WIDTH - SQUARE_SIZE;
        if (squares[i].y < 0) squares[i].y = 0;
        if (squares[i].y > SCREEN_HEIGHT - SQUARE_SIZE) squares[i].y = SCREEN_HEIGHT - SQUARE_SIZE;
        
        // Update rotation
        squares[i].rotation += squares[i].rotation_speed;
        
        // Check collisions with other squares
        for (int j = i + 1; j < NUM_SQUARES; j++) {
            if (!squares[j].active) continue;
            
            if (squares_colliding(&squares[i], &squares[j])) {
                // Create explosion at collision point!
                float explosion_x = (squares[i].x + squares[j].x) / 2;
                float explosion_y = (squares[i].y + squares[j].y) / 2;
                
                // Mix their colors for the explosion
                Color explosion_color;
                explosion_color.r = (squares[i].color.r + squares[j].color.r) / 2;
                explosion_color.g = (squares[i].color.g + squares[j].color.g) / 2;
                explosion_color.b = (squares[i].color.b + squares[j].color.b) / 2;
                explosion_color.a = 255;
                
                create_explosion(particles, explosion_x, explosion_y, explosion_color);
                
                // Respawn both squares at new positions
                squares[i].x = rand() % (SCREEN_WIDTH - SQUARE_SIZE);
                squares[i].y = rand() % (SCREEN_HEIGHT - SQUARE_SIZE);
                squares[j].x = rand() % (SCREEN_WIDTH - SQUARE_SIZE);
                squares[j].y = rand() % (SCREEN_HEIGHT - SQUARE_SIZE);
                
                // Give them new random velocities and colors
                squares[i].dx = ((rand() % 300) - 150) / 50.0f;
                squares[i].dy = ((rand() % 300) - 150) / 50.0f;
                squares[j].dx = ((rand() % 300) - 150) / 50.0f;
                squares[j].dy = ((rand() % 300) - 150) / 50.0f;
                
                // New random colors
                float hue_i = ((float)rand() / RAND_MAX);
                float hue_j = ((float)rand() / RAND_MAX);
                squares[i].color.r = (Uint8)(255 * (0.5 + 0.5 * sin(hue_i * 6.28)));
                squares[i].color.g = (Uint8)(255 * (0.5 + 0.5 * sin(hue_i * 6.28 + 2.09)));
                squares[i].color.b = (Uint8)(255 * (0.5 + 0.5 * sin(hue_i * 6.28 + 4.18)));
                squares[j].color.r = (Uint8)(255 * (0.5 + 0.5 * sin(hue_j * 6.28)));
                squares[j].color.g = (Uint8)(255 * (0.5 + 0.5 * sin(hue_j * 6.28 + 2.09)));
                squares[j].color.b = (Uint8)(255 * (0.5 + 0.5 * sin(hue_j * 6.28 + 4.18)));
            }
        }
    }
}

// Update particle system
void update_particles(Particle particles[]) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!particles[i].active) continue;
        
        // Update position
        particles[i].x += particles[i].dx;
        particles[i].y += particles[i].dy;
        
        // Apply gravity (just like our JavaScript fireworks!)
        particles[i].dy += 0.1f;
        
        // Reduce life
        particles[i].life--;
        
        // Fade out color as particle dies
        float life_ratio = (float)particles[i].life / PARTICLE_LIFE;
        particles[i].color.a = (Uint8)(255 * life_ratio);
        
        // Deactivate if dead or off screen
        if (particles[i].life <= 0 || particles[i].y > SCREEN_HEIGHT) {
            particles[i].active = false;
        }
    }
}

// Render all squares to the screen
void render_squares(SDL_Renderer* renderer, MovingSquare squares[]) {
    for (int i = 0; i < NUM_SQUARES; i++) {
        if (!squares[i].active) continue;
        
        // Set the color for this square
        SDL_SetRenderDrawColor(renderer, 
                              squares[i].color.r, 
                              squares[i].color.g, 
                              squares[i].color.b, 
                              squares[i].color.a);
        
        // Create the square structure for SDL
        SDL_Rect rect = {
            (int)squares[i].x,
            (int)squares[i].y,
            SQUARE_SIZE,
            SQUARE_SIZE
        };
        
        // Draw the filled square
        SDL_RenderFillRect(renderer, &rect);
        
        // Add a white border for definition
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
    }
}

// Render particle explosion effects
void render_particles(SDL_Renderer* renderer, Particle particles[]) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!particles[i].active) continue;
        
        // Set particle color with alpha for fading
        SDL_SetRenderDrawColor(renderer, 
                              particles[i].color.r, 
                              particles[i].color.g, 
                              particles[i].color.b, 
                              particles[i].color.a);
        
        // Draw particle as a small rectangle (2x2 pixels)
        SDL_Rect particle_rect = {
            (int)particles[i].x - 1,
            (int)particles[i].y - 1,
            3,
            3
        };
        
        SDL_RenderFillRect(renderer, &particle_rect);
    }
}



int main(int argc, char* argv[]) {
    printf("Pixel Renderer - Collision Explosions!\n");
    printf("Created by Ryan Rustill\n");
    printf("Watch squares collide and explode into fireworks!\n");
    printf("Press ESC to exit, any other key to randomize!\n\n");
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    
    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "Collision Explosions",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    // Create renderer for drawing
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // Initialize our moving squares and particle system
    MovingSquare squares[NUM_SQUARES];
    Particle particles[MAX_PARTICLES];
    init_squares(squares);
    init_particles(particles);
    
    // Main game loop - this is the heart of any game engine!
    bool quit = false;
    SDL_Event e;
    Uint32 frame_start, frame_time;
    const int frame_delay = 1000 / TARGET_FPS; // Milliseconds per frame
    
    printf("Graphics window opened! Watch the squares collide and explode!\n");
    printf("Advanced collision detection + particle explosions = game engine magic!\n\n");
    
    while (!quit) {
        frame_start = SDL_GetTicks();
        
        // Handle events (input processing)
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
                else {
                    // Any other key resets everything - interactive feature!
                    printf("Resetting simulation with new colors!\n");
                    init_squares(squares);
                    init_particles(particles); // Clear any existing particles
                }
            }
        }
        
        // Update game state
        update_squares(squares, particles);
        update_particles(particles);
        
        // Clear screen with black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // Render everything (squares first, then particles on top)
        render_squares(renderer, squares);
        render_particles(renderer, particles);
        
        // Present the rendered frame to screen
        SDL_RenderPresent(renderer);
        
        // Frame rate limiting - keep it smooth!
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {
            SDL_Delay(frame_delay - frame_time);
        }
    }
    
    printf("\nAdvanced collision detection and particle systems mastered!\n");
    printf("Ready to build that RPG game engine!\n");
    
    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
} 