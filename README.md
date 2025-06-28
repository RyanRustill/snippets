# snippets

A collection of programming stuff I've been working on. Each project is something I thought was cool enough to save and share.

Everything here actually runs and has instructions if you want to try it yourself.

---

## [🐍 Spiral Galaxy Generator](python/spirals) `Python` `turtle`
**Just figured out how to create galaxy-like spirals with Python's turtle graphics**

The math behind this blew my mind - just two simple variables create this incredible expanding spiral pattern. Takes about 30 seconds to watch it draw itself.

## [🌈 Rainbow Spiral Generator](python/rainbow_spiral) `Python` `turtle` `color`
**Figured out how to make spirals that cycle through every color in the rainbow using math**

This was my first time combining color theory with programming! I discovered you can use trigonometric functions to calculate smooth color transitions. The same spiral pattern as before, but now it flows through the entire color spectrum.

## [🌪️ Canvas Spiral](javascript/spirals) `JavaScript` `Canvas`
**Same spiral pattern but in the browser with real-time animation**

This one's cool because you can watch it being drawn in real-time. Same math as the Python version but using HTML5 canvas instead of turtle graphics.

## [🟨 Neon Cube Animation](javascript/neon_cube) `JavaScript` `Canvas`
**Built this cube that draws itself line-by-line with glowing neon effects**

Pure HTML5 canvas and JavaScript - no frameworks needed. The cube appears stroke by stroke and then pulses with this cool glow effect before starting over.

## [⚽ Bouncing Ball Physics](javascript/bouncing_ball) `JavaScript` `Physics`
**Figured out how to make things bounce realistically with actual gravity and physics**

This was my first time programming real physics! The balls bounce with gravity, lose energy when they hit walls, and you can click to add more. Way cooler than I expected physics programming to be.

## [🌧️ Digital Rain Animation](javascript/digital_rain) `JavaScript` `Particles`
**Matrix-style falling code rain with Japanese characters and interactive effects**

My first real particle system! Green characters fall like in The Matrix, with realistic trailing effects and interactive features. Click anywhere to create burst effects, or press 'N' for Neo mode. Learning about alpha compositing and performance optimization was amazing.

## [🎨 ASCII Pattern Generator](c/ascii_patterns) `C` `Mathematics`
**Turning math equations into visual art using nothing but text characters**

Four different mathematical patterns including the famous Mandelbrot fractal set! Going from basic C programs to generating complex mathematical visualizations feels incredible. Each pattern uses different math concepts like complex numbers and polar coordinates.

## [🌳 Fractal Tree Generator](python/fractal_tree) `Python` `recursion`
**Today I learned how to grow realistic trees using recursion!**

This can be a mind-bender to understand but the secret is recursion - a function that calls itself! Each branch creates two smaller branches, and those create more branches, until you get these tiny green leaves. This felt like unlocking a superpower, now I understand how computer graphics can simulate nature.

## [🎆 Interactive Fireworks Display](javascript/fireworks_display) `JavaScript` `Physics` `Interaction`
**Click anywhere to launch fireworks that explode into colorful sparks with realistic gravity!**

This was my first time combining mouse events with multi-stage particle physics! Rockets shoot up from where you click, then explode into 30 sparks arranged in a perfect circle using trigonometry. The sparks fall with gravity and fade out over time. Learning how objects can create other objects (rockets creating sparks) felt like unlocking a whole new level of programming.

## [🔺 Sierpinski Triangle Generator](python/sierpinski_triangle) `Python` `fractals` `recursion`
**Today I discovered one of the most mind-blowing things in mathematics - the Sierpinski Triangle!**

This fractal creates infinite complexity from the simplest rule: take a triangle, split it into 4 smaller triangles, throw away the middle one, and repeat forever. I built it with two stunning visual modes - classic triangles and bold circle patterns. The coolest part? This triangle has zero area but infinite perimeter. My brain still can't fully process that, but the code doesn't care - it just creates beauty!

## [🎵 Audio Visualizer](javascript/audio_visualizer) `JavaScript` `WebAudio` `Visualization`
**Created my first real-time music visualizer with a sliding rainbow that flows like liquid light across the screen!**

This was my breakthrough into audio programming! The Web Audio API lets me grab live microphone data and break it into frequency components, then I map each frequency to a colored bar. But the magic happens with the sliding rainbow effect, colors continuously flow across the spectrum creating this hypnotic liquid light animation. The layout design splits the canvas perfectly: pulsing circle in the top area, flowing rainbow bars below. Watching sound waves become visual art in real-time completely changed how I think about programming!

## [💥 Collision Explosions](c/pixel_renderer) `C` `SDL` `Graphics`
**Advanced collision detection with explosive particle effects - building real game engine fundamentals!**

Eight colorful squares bounce around the screen, but when two collide they explode into 25 particles with realistic gravity physics! This combines collision detection between moving objects, particle system architecture, and efficient memory management. Every collision creates a burst of colorful sparks that fall and fade like fireworks. Learning how to coordinate multiple game systems (squares create particles, particles respond to physics, everything renders at 60 FPS) feels like the foundation for building actual game engines.
