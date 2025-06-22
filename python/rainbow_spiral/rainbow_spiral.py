import turtle
import math

# Set up the screen with a dark background to make colors pop
screen = turtle.Screen()
screen.bgcolor("black")
screen.title("Rainbow Spiral")
screen.setup(width=800, height=800)

# Create our turtle artist
rainbow_turtle = turtle.Turtle()
rainbow_turtle.speed(0)  # Fastest drawing speed
rainbow_turtle.width(2)  # Nice thick lines to see the colors

# This is where the magic happens!
# We'll create a spiral that changes colors smoothly
def draw_rainbow_spiral():
    # Start from the center
    rainbow_turtle.penup()
    rainbow_turtle.goto(0, 0)
    rainbow_turtle.pendown()
    
    # These variables control our spiral and colors
    distance = 0    # How far to move each step
    angle = 91      # How much to turn (91 gives a nice spiral shape)
    
    # Draw 360 lines to make a complete, colorful spiral
    for step in range(360):
        # This is the cool part - calculate the color!
        # We use the step number to create a smooth rainbow transition
        hue = step / 360.0  # This gives us a number from 0 to 1
        
        # Convert our hue to RGB colors (this took me forever to figure out!)
        red = int(255 * (1 + math.cos(2 * math.pi * hue)) / 2)
        green = int(255 * (1 + math.cos(2 * math.pi * hue + 2 * math.pi / 3)) / 2)
        blue = int(255 * (1 + math.cos(2 * math.pi * hue + 4 * math.pi / 3)) / 2)
        
        # Set the turtle's color using our calculated RGB values
        rainbow_turtle.color(red/255, green/255, blue/255)
        
        # Move forward and turn to create the spiral
        rainbow_turtle.forward(distance)
        rainbow_turtle.left(angle)
        
        # Make the spiral gradually expand outward
        distance += 0.8  # Each step gets slightly longer
    
    # Finish with style!
    rainbow_turtle.hideturtle()

# Let's create our rainbow spiral!
print("Creating a rainbow spiral - this is so cool to watch!")
print("The colors shift smoothly from red through the entire spectrum...")

draw_rainbow_spiral()

print("Done! Look at those smooth color transitions!")
print("The math behind this creates a perfect rainbow effect.")

# Keep the window open so we can admire our rainbow creation!
screen.exitonclick() 