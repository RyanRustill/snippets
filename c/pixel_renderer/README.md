# 💥 Collision Explosions - Advanced SDL Graphics

Taking graphics programming to the next level with SDL! This demonstrates real collision detection between moving objects and particle explosion effects. Building on the concepts from my JavaScript fireworks project, but implementing them in C for deeper understanding of game engine fundamentals.

## What you'll see

Eight colorful squares bouncing around the screen, but here's where it gets interesting: when two squares collide, they explode into a burst of 25 colorful particles that fall with gravity and fade out over time! The colliding squares immediately respawn at new positions with fresh colors and velocities. It's like a continuous fireworks show triggered by physics.

## How to run this

```bash
cd c/pixel_renderer

# Install SDL2 if you don't have it (Ubuntu/Debian)
make install-deps

# Build and run
make build-run
```

Press ESC to exit, or any other key to reset the simulation with new colors!

## How it works

This implements several advanced game development concepts in a classic game loop architecture:

1. **Handle Input** - Process keyboard events and user interactions
2. **Update Game State** - Move squares, detect collisions between objects, spawn particle explosions
3. **Update Particles** - Apply gravity, reduce particle life, handle fading effects
4. **Render Graphics** - Draw squares, render particles with alpha blending, present frame
5. **Frame Rate Control** - Maintain 60 FPS for smooth animation

The collision detection uses bounding box intersection - when two squares overlap, they explode into particles using the same trigonometric spread pattern from my JavaScript fireworks, but implemented in C with proper memory management.

## Try changing this

- **Number of squares** (line 25): Change `NUM_SQUARES` to 4 or 12 for different collision frequencies
- **Particle count** (line 26): Adjust `MAX_PARTICLES` for more/fewer explosion effects
- **Explosion size** (line 27): Modify `PARTICLE_LIFE` for longer/shorter particle trails
- **Square size** (line 28): Change `SQUARE_SIZE` to alter collision probability
- **Explosion intensity** (line 94): Modify the particle count in `create_explosion` (currently 25)
- **Gravity strength** (line 170): Adjust the `0.1f` value for different particle physics
- **Speed range** (lines 48-49): Change velocity calculations for faster/slower movement

## What I learned

This project taught me advanced game development concepts that go well beyond basic graphics:

1. **Object collision systems** - Implementing proper bounding box detection between multiple moving entities
2. **Particle system architecture** - Managing hundreds of short-lived objects with different lifespans
3. **Memory management patterns** - Using fixed-size arrays and active flags for efficient object pooling
4. **Multi-system coordination** - Squares create particles, particles respond to physics, all rendering in sync
5. **Performance optimization** - Handling 200+ particles at 60 FPS requires efficient update loops

What's exciting is seeing how this connects to my JavaScript fireworks project - the same mathematical concepts (trigonometry, gravity, fading) work in both languages, but C gives me direct control over memory layout and performance. This is exactly the foundation I need for building game engines where managing thousands of sprites and particles efficiently matters. 