# 🎨 Paint App

I worked on a fully functional paint app that lets you draw smooth lines with different colors and brush sizes, and even save your artwork!

## What you'll see

A clean paint canvas with a color picker, brush size slider, and a live preview of your brush. You can paint smooth, continuous lines by clicking and dragging your mouse across the white canvas. The interface has a sleek dark theme with gradient backgrounds and the canvas has a nice drop shadow effect. When you're done creating, you can save your artwork as a PNG file!

## How to run this

1. Save the `paint_app.html` file to your computer
2. Double-click the file to open it in your web browser
3. Start painting immediately - click and drag to draw!
4. Use the color picker to change colors
5. Adjust the brush size with the slider (1-50 pixels)
6. Click "Save Image" to download your artwork as a PNG file
7. Click "Clear Canvas" to start over

## How it works

The magic happens with HTML5 Canvas and mouse event listeners! When you press the mouse button down, it starts tracking your movements. As you move the mouse, it draws lines connecting each position, creating smooth curves. The key trick is using `lineTo()` and `stroke()` to draw continuous lines instead of individual dots.

The app tracks your drawing state with a boolean `isDrawing` that turns on when you press the mouse down and turns off when you release it or move the mouse outside the canvas. Each mouse movement gets converted to canvas coordinates and draws a line from the last position to the current position.

## Try changing this

- **Line 176**: Change `ctx.lineCap = 'round'` to `'square'` or `'butt'` for different line endings
- **Line 135**: Modify the `max="50"` in the brush size input to allow bigger or smaller brushes
- **Line 130**: Change the default color from `#000000` (black) to any hex color code
- **Line 201**: Add `ctx.globalCompositeOperation = 'multiply'` before drawing for blend modes
- **Line 12**: Customize the background gradient colors to match your style

## What I learned

This was my first time building a drawing application and I learned so much about mouse event handling! The biggest breakthrough was understanding how to track mouse movement and convert screen coordinates to canvas coordinates using `getBoundingClientRect()`. 

I also discovered how to make drawing feel smooth by connecting each mouse position with lines instead of trying to draw individual points. The `lineCap` and `lineJoin` properties make the lines look professional instead of pixelated.

Building the real-time brush preview was super satisfying, watching the preview dot change size and color as you adjust the controls makes the app feel polished and responsive. This project really showed me how you can create professional-looking interfaces with just HTML, CSS, and JavaScript! 