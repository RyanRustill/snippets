# 🟨 Neon Cube Animation

I wanted to create something that felt like watching a hologram form in the air - this cube draws itself line by line and then pulses with this sick cyan glow!

## What you'll see
A 3D wireframe cube materializes from nothing, drawing each edge one at a time with a bright cyan glow. Once complete, it pulses with varying intensity, then fades out and starts over. The whole thing loops forever, which is oddly hypnotic.

## How to run this
```bash
# Just open the HTML file in any web browser
# Double-click neon_cube.html
# Or open it from your browser: File -> Open
```

Everything's in one file - no external dependencies or server needed!

## How it works
This was such a fun challenge! I had to figure out the exact order to draw the cube edges so it actually looks like a 3D cube being constructed.

The magic happens in several steps:
1. **Point mapping**: I defined all 16 points that make up the cube's wireframe in the exact order they should be drawn
2. **Progressive drawing**: Each frame, I draw a little more of the current line using `requestAnimationFrame()` 
3. **Line interpolation**: Math calculates the in-between points: `x = startX + (endX - startX) * progress`
4. **Glow effects**: CSS `shadowBlur` and `shadowColor` create that neon effect
5. **Pulse animation**: After completion, the cube pulses using `rgba()` for transparency and `Math.sin()` for the oscillating line thickness

The trickiest part was figuring out the point order. You can't just connect them randomly - it has to trace a path that makes sense visually, like you're actually drawing a cube in the air.

## Try changing this
- **progress += 0.01**: Make it 0.02 for faster drawing, or 0.005 for super slow
- **shadowBlur = 15**: Try 30 for a bigger glow, or 5 for sharp lines
- **strokeStyle = "cyan"**: Try "magenta", "lime", "yellow", or any color you want
- **Math.sin(pulse * 10)**: Change the 10 to make the pulse faster or slower
- **Challenge**: Add multiple cubes at different positions, or make them rotate!

## What I learned
Understanding `requestAnimationFrame()` was huge - it's so much smoother than using `setTimeout()`. Also learned that animation is really just math over time, and that sometimes the presentation is more important than complex algorithms.

The point coordinates took forever to get right, but it taught me to think more carefully about how 3D shapes work in 2D space. Plus, the glow effects showed me how powerful CSS can be even inside canvas drawings!
