# 🎆 Interactive Fireworks Display

Click anywhere on the screen and watch rockets shoot up and explode exactly where you clicked with gorgeous colorful sparks that fall with realistic gravity!

## What you'll see
A night sky gradient background where you can click to launch firework rockets. Each rocket leaves a white trail as it shoots directly toward your click point, then explodes exactly where you clicked into 30 colorful sparks that spread out in a perfect circle and fall down with gravity effects. Every firework has a random bright color - hot pink, orange, yellow, lime green, cyan, blue, or purple!

## How to run this
```bash
# Just open the HTML file in any browser
open fireworks_display.html
```

## How it works
This builds on particle systems but adds mouse interaction and multi-stage physics! When you click, it creates a Rocket object that moves upward with a trail of fading particles behind it. When the rocket reaches its target height, it "explodes" by creating 30 Spark objects arranged in a perfect circle using trigonometry (2π radians divided by 30 gives even spacing).

Each spark has its own velocity vector pointing outward from the explosion center, plus gravity that pulls it downward over time. The sparks also fade out gradually using an alpha transparency that decreases each frame. The canvas uses a slight trail effect instead of completely clearing each frame, which makes the fireworks look more magical!

## Try changing this
- **Number of sparks** (line 95): Change `i < 30` to `i < 50` for denser explosions
- **Rocket speed** (line 60): Change `this.velocityY = -8` to `-12` for faster rockets  
- **Gravity strength** (line 144): Change `this.gravity = 0.1` to `0.2` for faster falling sparks
- **Trail length** (line 70): Change `> 10` to `> 20` for longer rocket trails
- **Challenge**: Add different explosion patterns - try making heart shapes or star bursts instead of circles!

## What I learned
This was my first time combining mouse events with multi-stage particle physics and it completely blew my mind! Learning how to make objects that create other objects (rockets creating sparks) felt like unlocking a whole new level of programming. The trigonometry for spreading the explosion particles evenly in a circle was super satisfying to figure out - using `Math.cos(angle) * speed` and `Math.sin(angle) * speed` to convert polar coordinates into x/y velocities is pure magic.

The gravity simulation also taught me how to make particle systems feel realistic - just adding a small amount to the Y velocity each frame makes the sparks arc and fall naturally like real fireworks! The precision click-to-explode functionality made the interaction so much more satisfying - now the fireworks go exactly where you want them instead of random heights. 