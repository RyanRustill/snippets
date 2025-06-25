# 🔺 Sierpinski Triangle Generator

Today we are going to dig deeper into mathematics and explore the Sierpinski Triangle! It's a fractal that creates infinite complexity from the simplest rule: take a triangle, split it into 4 smaller triangles, throw away the middle one, and repeat forever. I built it with TWO stunning visual modes that really show off the mathematical beauty!

## What you'll see

Choose from two crystal-clear visual modes:
- **Classic Triangles**: The traditional fractal in beautiful rainbow colors  
- **Circle Pattern**: Bold geometric circles forming the same fractal structure

Each mode shows the same mathematical structure but with completely different visual appeal. The patterns emerge naturally from recursion - no complicated drawing code needed!

## How to run this

```bash
cd python/sierpinski_triangle
python3 sierpinski_triangle.py
```

Choose your mode (1-3) and watch the fractal build itself! The "Surprise Me" option picks a random mode for you.

## How it works

This was a lot of fun and really deepened my understanding of how recursion can create complex patterns! The program starts with one big triangle, then:

1. **Find the midpoints** of each side (basic coordinate math)
2. **Split into 3 triangles** using those midpoints (skip the middle one!)
3. **Recursively draw** each of the 3 triangles the same way
4. **Base case**: When we get small enough, draw the actual shape

The different modes just change what shape gets drawn at the base case - triangles or circles. But the fractal structure stays the same!

## Try changing this

- **Change the depth** (line 167): Try `sierpinski_recursive(artist, points, 6, mode)` for more detail, or 4 for faster drawing
- **Add new colors** (line 28): Add your favorite hex colors to the palette
- **Modify the size** (line 159): Make it bigger or smaller by changing `size = 300`
- **Create new modes**: Try drawing other shapes like stars or diamonds in the base case
- **Background colors** (line 15): Change from black to any color you like

## What I learned

Recursion completely blew my mind again! After the fractal tree project, I thought I understood it, but this took it to another level. The Sierpinski Triangle taught me that:

1. **Complex patterns emerge from simple rules** - you don't need complicated code to create something amazing
2. **Mathematics is everywhere in nature** - this pattern shows up in ferns, coastlines, and even lightning!
3. **Different visualizations reveal different aspects** - the same math can look completely different
4. **Fractals have infinite detail** - no matter how far you zoom in, there's always more pattern

The coolest part? This triangle has ZERO area but infinite perimeter. My brain still can't fully process that, but the code doesn't care - it just creates beauty! 