import turtle
import math
import random

def draw_tree(branch_length, angle, depth):
    """
    This is where the magic happens! A function that calls itself to create branches.
    Each branch creates two smaller branches, just like a real tree!
    """
    if depth == 0:
        # When we've gone deep enough, stop and draw a little leaf
        turtle.color("lightgreen")
        turtle.dot(4)
        turtle.color("brown")
        return
    
    # Draw the current branch
    turtle.forward(branch_length)
    
    # Save our current position so we can come back here
    turtle.right(angle)
    
    # Create the right branch (slightly smaller and more random)
    new_length = branch_length * (0.7 + random.random() * 0.1)  # Makes it look more natural
    draw_tree(new_length, angle + random.randint(-5, 5), depth - 1)
    
    # Go back to where we were
    turtle.left(angle * 2)
    
    # Create the left branch
    new_length = branch_length * (0.7 + random.random() * 0.1)
    draw_tree(new_length, angle + random.randint(-5, 5), depth - 1)
    
    # Return to the base of this branch
    turtle.right(angle)
    turtle.backward(branch_length)

def setup_screen():
    """Set up our drawing canvas to look awesome"""
    screen = turtle.Screen()
    screen.bgcolor("black")  # Dark background makes the tree pop
    screen.title("Fractal Tree Generator")
    screen.setup(800, 600)
    return screen

def setup_turtle():
    """Configure our turtle to draw a beautiful tree"""
    turtle.speed(0)  # Fastest drawing speed
    turtle.color("brown")
    turtle.pensize(3)
    
    # Start at the bottom center, pointing up
    turtle.penup()
    turtle.goto(0, -250)
    turtle.setheading(90)  # Point straight up
    turtle.pendown()

def main():
    """Generate an amazing fractal tree!"""
    print("🌳 Fractal Tree Generator")
    print("Watch as mathematics creates nature...")
    
    # Set up everything
    screen = setup_screen()
    setup_turtle()
    
    # Draw the tree - these parameters create a beautiful balanced tree
    initial_length = 120      # Length of the trunk
    branch_angle = 25         # How wide the branches spread
    recursion_depth = 8       # How many levels of branches (more = more detailed)
    
    print(f"Growing tree with {recursion_depth} levels of branches...")
    
    # This is the moment where recursion creates magic!
    draw_tree(initial_length, branch_angle, recursion_depth)
    
    print("🎨 Tree complete! Click anywhere on the tree to close.")
    print("Try changing the numbers in the code to grow different trees!")
    
    # Keep the window open until clicked
    screen.exitonclick()

if __name__ == "__main__":
    main() 