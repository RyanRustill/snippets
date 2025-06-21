# ⚽ Bouncing Ball Physics

I just figured out how to make things bounce realistically on a screen and honestly, it's so much cooler than I expected!

## What you'll see
A glowing ball that bounces around the screen with actual gravity and physics, it speeds up when falling, slows down when going up, and loses energy when it hits the walls just like a real ball would. Click anywhere to add more balls and watch them all bounce around together!

## How to run this
```bash
# Just open the HTML file in any web browser
open bouncing_ball.html
# or double-click it in your file manager
```

## How it works
This was my first time programming actual physics! The ball has velocity (speed and direction) and I add gravity to the vertical velocity every frame, which makes it accelerate downward just like real gravity. When it hits a wall, I multiply the velocity by -0.8, which makes it bounce back but with less energy (so it eventually settles down).

The coolest part is the `requestAnimationFrame` function, it runs 60 times per second and recalculates where each ball should be. That's what makes the movement look smooth instead of jumpy.

I also borrowed the glowing effect from my neon cube project because regular circles looked boring!

## Try changing this
- **Gravity value (0.5)**: Make it 0.2 for moon gravity, or 1.0 for super heavy gravity
- **Energy loss (-0.8)**: Change to -0.9 for bouncier balls, or -0.6 for balls that settle faster
- **Random speed range (10)**: Make it 20 for crazy fast balls, or 5 for gentle floating
- **Ball size range (10-30)**: Try (5-15) for tiny balls or (20-50) for giant ones
- **Challenge**: Can you make balls bounce off each other when they collide?

## What I learned
Physics programming is way more fun than I thought it would be! I learned that making things look "natural" on screen is all about applying the same rules that work in real life, gravity, energy loss, momentum. 

The hardest part was figuring out the collision detection with the walls. I kept getting bugs where balls would get stuck outside the boundaries until I added the `Math.max/Math.min` clamping.

Also discovered that `hsl()` colors are perfect for random bright colors, way better than trying to pick random RGB values!

## Related concepts
- Vector math (velocity as x/y components)
- Game physics loops
- Canvas animation techniques
- Event handling for interactivity 