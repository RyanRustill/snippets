#!/usr/bin/env python3
"""
Sierpinski Triangle Generator with Multiple Visual Modes
Created by Ryan Rustill (@RyanRustill)

This program generates the famous Sierpinski Triangle fractal using recursion
with four different stunning visual modes to choose from!
"""

import turtle
import random
import math

def setup_screen():
    """Set up the turtle graphics window for maximum visual impact"""
    screen = turtle.Screen()
    screen.bgcolor("black")  # Black background makes colors pop!
    screen.setup(width=800, height=800)
    screen.title("Sierpinski Triangle Generator")
    return screen

def create_turtle():
    """Create our drawing turtle with optimized settings"""
    artist = turtle.Turtle()
    artist.speed(0)  # Fastest drawing speed
    artist.pensize(1)
    artist.hideturtle()  # Hide turtle for cleaner look
    return artist

def get_triangle_colors():
    """Return a beautiful color palette for the triangles"""
    return ["#FF6B6B", "#4ECDC4", "#45B7D1", "#96CEB4", "#FFEAA7", "#DDA0DD", "#98D8C8", "#F7DC6F"]

def draw_triangle(artist, points, color):
    """Draw a single triangle given three points"""
    artist.penup()
    artist.goto(points[0])
    artist.pendown()
    artist.fillcolor(color)
    artist.begin_fill()
    
    for point in points:
        artist.goto(point)
    artist.goto(points[0])  # Close the triangle
    
    artist.end_fill()

def draw_circle(artist, center, radius, color):
    """Draw a proper filled circle using turtle's dot method"""
    artist.penup()
    artist.goto(center[0], center[1])
    artist.pencolor(color)
    artist.dot(radius * 2, color)  # dot() takes diameter, not radius



def sierpinski_recursive(artist, points, depth, mode="triangles"):
    """
    The magic happens here! This function calls itself to create the fractal.
    Each time we split the triangle into 3 smaller triangles and recurse.
    """
    if depth == 0:
        # Base case: draw the actual shape based on mode
        colors = get_triangle_colors()
        color = random.choice(colors)
        
        # Calculate center point for non-triangle modes
        center_x = (points[0][0] + points[1][0] + points[2][0]) / 3
        center_y = (points[0][1] + points[1][1] + points[2][1]) / 3
        center = (center_x, center_y)
        
        # Calculate size based on triangle size
        side_length = ((points[1][0] - points[0][0])**2 + (points[1][1] - points[0][1])**2)**0.5
        
        if mode == "triangles":
            draw_triangle(artist, points, color)
        elif mode == "circles":
            # Make circles much more prominent and beautiful!
            circle_radius = side_length / 4  # Large, visible circles
            draw_circle(artist, center, circle_radius, color)
        return
    
    # Recursive case: find the midpoints of each side
    # This is where the fractal magic happens!
    mid1 = ((points[0][0] + points[1][0]) / 2, (points[0][1] + points[1][1]) / 2)
    mid2 = ((points[1][0] + points[2][0]) / 2, (points[1][1] + points[2][1]) / 2)
    mid3 = ((points[2][0] + points[0][0]) / 2, (points[2][1] + points[0][1]) / 2)
    
    # Recurse on the three new triangles (notice we skip the middle one!)
    sierpinski_recursive(artist, [points[0], mid1, mid3], depth - 1, mode)
    sierpinski_recursive(artist, [mid1, points[1], mid2], depth - 1, mode)
    sierpinski_recursive(artist, [mid3, mid2, points[2]], depth - 1, mode)

def main():
    """Main function that runs our Sierpinski Triangle generator"""
    print("🔺 Sierpinski Triangle Generator")
    print("Created by Ryan Rustill")
    print()
    print("Choose your visual mode:")
    print("1. Classic Triangles (traditional fractal beauty)")
    print("2. Circle Pattern (bold geometric circles)")
    print("3. Surprise Me! (random mode)")
    
    choice = input("\nEnter your choice (1-3): ").strip()
    
    # Map choices to modes
    modes = {
        "1": "triangles",
        "2": "circles", 
        "3": random.choice(["triangles", "circles"])
    }
    
    mode = modes.get(choice, "triangles")
    
    print(f"\n🎨 Generating Sierpinski Triangle in {mode} mode...")
    print("Watch as mathematics creates infinite complexity from simple rules!")
    
    # Set up the graphics
    screen = setup_screen()
    artist = create_turtle()
    
    # Define the main triangle (equilateral triangle centered on screen)
    size = 300
    height = size * math.sqrt(3) / 2
    
    # Three points of our starting triangle
    top = (0, height/2)
    bottom_left = (-size/2, -height/2)
    bottom_right = (size/2, -height/2)
    
    points = [top, bottom_left, bottom_right]
    
    # Generate the fractal! Start with depth 5 for good detail
    sierpinski_recursive(artist, points, 5, mode)
    
    print(f"\n✨ Beautiful! Your {mode} Sierpinski Triangle is complete!")
    print("\nFractal fun fact: No matter how far you zoom into a Sierpinski Triangle,")
    print("you'll keep seeing the same triangular pattern repeating infinitely!")
    print("\nClick anywhere on the screen to close the window.")
    
    # Keep the window open until clicked
    screen.exitonclick()

if __name__ == "__main__":
    main() 