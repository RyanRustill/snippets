# spiral-turtle.py
# Creates an awesome galaxy-like spiral using Python's turtle graphics

import turtle  # This is built into Python - no extra installation needed!

# Create our drawing turtle and screen
t = turtle.Turtle()
s = turtle.Screen()
s.bgcolor("black")           # Black background makes the spiral pop
t.pencolor("yellow")         # Bright yellow for that space look

# These are the magic variables that create the spiral
a = 0                        # How far to move forward (starts at 0)
b = 0                        # How much to turn (starts at 0)
t.speed(0)                   # Draw as fast as possible

# Start drawing from the top center
t.penup()                    # Lift the pen to move without drawing
t.goto(0, 200)               # Go to starting position
t.pendown()                  # Put the pen down to start drawing

# This is where the magic happens!
while True:
    t.forward(a)             # Move forward by current distance
    t.right(b)               # Turn right by current angle
    a += 3                   # Next time, move a little farther
    b += 1                   # Next time, turn a little more
    if b == 210:             # Stop after 210 steps (feels just right)
        break
    t.hideturtle()           # Keep the turtle invisible for cleaner look

turtle.done()                # Keep the window open so we can admire our creation!
