# 🌳 Fractal Tree Generator

Today I learned how to grow realistic trees using recursion!

## What you'll see
A brown tree grows on your screen branch by branch, starting from a trunk and splitting into smaller and smaller branches. Each branch creates two more branches, and those create more branches, until you get these tiny green leaves. It looks eerily like a real tree!

## How to run this
```bash
cd snippets/python/fractal_tree
python3 fractal_tree.py
```

## How it works
This can be a mind-bender to understand. The secret is **recursion** - a function that calls itself! 

The `draw_tree()` function draws one branch, then calls itself twice to create two smaller branches. Those smaller branches call themselves to create even smaller branches. It keeps going until the branches get too tiny to matter.

The crazy part is how just three numbers control the entire tree:
- **branch_length**: How long each branch is
- **angle**: How wide the branches spread out  
- **depth**: How many levels of branching (more = more detailed tree)

I added some randomness so each branch is slightly different, making it look more natural instead of perfectly mathematical.

## Try changing this
- **recursion_depth**: Try 6 for a simpler tree, or 10 for an incredibly detailed one (warning: 10+ takes forever!)
- **branch_angle**: 15 makes a tall skinny tree, 45 makes a wide bushy tree
- **initial_length**: 80 for a smaller tree, 200 for a giant tree
- **Challenge**: Change the colors! Try making autumn trees with orange/red leaves

## What I learned
Recursion completely blew my mind. The idea that a function can call itself seemed impossible at first, but seeing it create these natural-looking trees made it click. 

I also discovered how mathematical patterns can create things that look organic and natural. Three simple numbers can generate something that looks like it grew in a forest!

This felt like unlocking a superpower, now I understand how computer graphics can simulate nature. 