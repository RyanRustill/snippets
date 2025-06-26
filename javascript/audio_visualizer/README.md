# 🎵 Audio Visualizer

This was my first time programming something that responds to actual music in real-time. Watching sound waves turn into a sliding rainbow that flows like liquid light is pretty cool!

## What you'll see
A mesmerizing rainbow spectrum that slides across the screen while responding to music - imagine liquid aurora flowing from left to right! The frequency bars dance to the beat with a full 360° color spectrum that continuously shifts, creating a hypnotic flowing effect. Rainbow particles burst from intense beats, and a pulsing circle in the top area shows overall volume. The colors never stay the same - they're always sliding to create new combinations!

## How to run this
```bash
# Just open the HTML file in your browser
open audio_visualizer.html

# Or if you're in the directory:
# Double-click the file to open in your default browser
```

**Important**: You'll need to allow microphone access when the browser asks - that's how it "hears" the music to visualize it!

## How it works
The magic happens with the Web Audio API - it's like having a tiny sound engineer inside your browser! The code grabs audio from your microphone, breaks it down into different frequency ranges (like bass, mids, treble), then maps each frequency to a visual bar. But here's the cool part: instead of static colors, I added a sliding rainbow effect that makes colors flow across the screen over time. Each bar gets a hue that shifts continuously, creating the illusion of liquid rainbow. The layout splits the 600x600 area - circle in the top 20% so it never gets lost, and the flowing spectrum in the bottom 80%.

## Try changing this
- **`analyser.fftSize`**: Try 256, 512, 1024, or 2048 for different frequency detail levels (line 145)
- **Rainbow slide speed**: Change `(time * 30)` to `(time * 60)` for faster flow, or `(time * 10)` for slower (line 193)
- **Bar count**: Modify `desiredBars = 300` to 150-500 for different smoothness levels (line 178)
- **Layout split**: Change `reservedTop = canvas.height * 0.2` to 0.1-0.3 for different compositions (line 174)
- **Particle threshold**: Adjust `frequency > 0.5` to 0.3-0.7 and spawn chance `0.4` to 0.1-0.8 (line 202)
- **Challenge**: Make the circle color sync with the dominant frequency instead of time-based cycling!

## What I learned
This project taught me that programming isn't just about making things move on screen - you can actually interact with real-world data like sound waves! The Web Audio API opened up a whole new world where I can grab frequency data and turn math into art. The breakthrough moment was discovering how to make colors flow using time-based calculations - adding `Date.now()` to color equations creates that liquid rainbow effect. I also learned about smart layout design: reserving space for important elements (like the circle) prevents them from getting lost in the chaos.

## Related concepts
- Web Audio API for real-time audio processing
- Frequency analysis and FFT (Fast Fourier Transform)  
- Time-based animation and color cycling
- Canvas composition and layout strategies
- HSL color space for smooth gradients 