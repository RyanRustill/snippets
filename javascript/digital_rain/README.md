# Digital Rain Animation

A Matrix-style digital rain effect with falling green characters, built with HTML5 Canvas and JavaScript.

## Features

- **Full-screen Animation**: Responsive canvas that adapts to window size
- **Authentic Matrix Characters**: Mix of Japanese katakana, numbers, and letters
- **Trailing Effect**: Characters fade as they fall, creating realistic trails
- **Interactive Elements**: Click to create burst effects
- **Easter Egg**: Press 'N' to activate Neo mode
- **Smooth Performance**: Optimized rendering at 20 FPS

## How It Works

### Core Animation Loop
```javascript
function draw() {
    // Semi-transparent overlay creates trailing effect
    ctx.fillStyle = 'rgba(0, 0, 0, 0.05)';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    
    // Draw falling characters
    for (let i = 0; i < drops.length; i++) {
        // Random character selection
        const char = charArray[Math.floor(Math.random() * charArray.length)];
        ctx.fillText(char, i * fontSize, drops[i]);
        drops[i] += fontSize;
    }
}
```

### Key Techniques

1. **Column-Based System**: Screen divided into vertical columns for organized dropping
2. **Alpha Blending**: Semi-transparent rectangles create fading trail effect
3. **Random Reset**: Drops restart at top with probabilistic timing
4. **Dynamic Resizing**: Canvas adjusts to window dimensions automatically

## Technical Concepts Learned

- **Canvas Animation**: Frame-based rendering and timing
- **Particle Systems**: Managing multiple animated objects
- **Alpha Compositing**: Layering transparent elements for effects
- **Event Handling**: Mouse and keyboard interaction
- **Performance Optimization**: Efficient rendering techniques
- **Responsive Design**: Dynamic canvas sizing

## Interactive Features

- **Click**: Create burst effects at cursor location
- **Press 'N'**: Toggle Neo mode (changes background tint)
- **Window Resize**: Animation adapts automatically

## Files

- `digital_rain.html` - Complete standalone animation

## Character Set

Uses authentic Matrix-style characters:
- Japanese Katakana: アイウエオカキクケコ...
- Numbers: 0123456789
- Letters: ABCDEFGHIJKLMNOPQRSTUVWXYZ

## Browser Compatibility

Works in all modern browsers with HTML5 Canvas support:
- Chrome/Chromium
- Firefox
- Safari
- Edge

## Next Steps

This project builds foundation skills for:
- More complex particle systems
- WebGL shader programming
- 3D graphics with Three.js
- Advanced visual effects 