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

## [🔍 Python Code Detective](python/python_detective) `Python` `Functions` `DataStructures`
**Ever see those Twitter posts asking "What will this code output?" Now I can figure them out with the detective method!**

This interactive quiz teaches step-by-step code analysis using a 6-step detective method. Instead of just testing knowledge, every explanation breaks down the thinking process for analyzing any Python code. I learned so much about structuring data with lists and dictionaries, and discovered that good programming isn't about syntax, it's about developing systematic thinking patterns. When you have to explain something clearly to someone else, you really understand it yourself!

## [🧙 Terminal RPG Engine](c/terminal_rpg_engine) `C` `RPG` `GameDev`
**A fully playable text-based RPG engine in C with dynamic memory, NPCs, combat, and exploration!**

This was my first full-featured game system in C: players can explore a world of five connected rooms, pick up items, talk to friendly and hostile NPCs, engage in combat, and save/load their progress. Everything is built with modular files and fully dynamic memory allocation. I even added color-coded terminal output and ASCII UI. Feels like building the bones of an actual RPG system from scratch!

## [🎨 Paint App](javascript/paint_app) `JavaScript` `Canvas` `UI`
**Built a fully functional paint app with smooth drawing, color picker, brush controls, and PNG export!**

I had a lot of fun building this Paint App! you can pick any color, change brush sizes, and draw smooth lines just by moving your mouse around. The coolest part is clicking "Save Image" downloads your drawing as a PNG file with transparent backgrounds. I also added this little preview dot that shows you exactly what your brush will look like before you draw. The whole thing feels really responsive and fun to use!

## [🌐 HTTP Web Server](c/http_web_server) `C` `Networking` `Berkeley Sockets`
**Today I rebuilt an earlier attempt at a HTTP web server from scratch using C and Berkeley sockets!**

This was my second time diving into low-level network programming, and seeing a web browser actually connect to my C program feels incredible. The server handles real HTTP requests with a cyberpunk-themed web interface, source code viewer, and 404 error demo. The coolest part is watching the terminal output as your browser makes requests - you can see the actual HTTP parsing happening in real-time! This is exactly how real web servers work under the hood, from socket creation to request routing.

## [🧠 Memory Card Game](javascript/memory_game) `JavaScript` `3D Transforms` `Game State`
**Built my first memory game with 3D card flips and rainbow gradients - each matched pair lights up in its own color!**

This morning I discovered CSS 3D transforms and the results are pretty neat! Click any card and it flips in actual 3D space using `transform: rotateY(180deg)`. But the best part is when you find a match, each emoji pair has its own gradient color, so the completed board looks like a rainbow checkerboard! Managing game state was tricky (had a bug where clicking too fast would flip three cards!) but learning about `data-` attributes and CSS attribute selectors opened up so many possibilities. The victory screen slides over everything with your stats when you win!