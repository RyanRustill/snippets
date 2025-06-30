./# Terminal RPG Engine

A complete text-based RPG engine written in C that demonstrates professional programming concepts through an interactive adventure game.

## What You'll See

When you run this program, you'll experience a fully functional RPG where you can:
- **Explore a connected world** of 5 unique locations (Town Square, Dark Forest, Blacksmith Shop, Abandoned Cave, Crystal Chamber)
- **Pick up and manage items** with a dynamic inventory system
- **Talk to friendly and hostile NPCs** each with dialogue, health, and behavior flags
- **Engage in turn-based combat** with damage calculations, death states, and gold rewards
- **Save and load your game progress** to continue your adventure later
- **Navigate using simple commands** like "north", "take sword", "inventory"
- **Experience structured room displays** with visual feedback and color-coded output

The game loads world data from text files and manages all memory dynamically - this was my first time building a multi-file C project with proper memory management!

## Try Changing This

Want to experiment? Here are some fun modifications:

**Add New Locations:**
- Edit `data/rooms.txt` to add more rooms (just follow the format!)
- Connect them by changing the room exit numbers

**Create New Items:**
- Add items to `data/items.txt` with different attack/defense bonuses
- Try placing the same item in multiple rooms

**Add More Characters:**
- Modify setup_npcs() in world.c to add custom friendly or hostile NPCs with custom dialogue and stats

**Modify Game Mechanics:**
- In `src/main.c`, add new commands (maybe "use item" or "attack")
- Change the inventory size limit in `src/game_types.h`

## How to Build and Run

```bash
# Build the game
make

# Run the adventure
./terminal_rpg

# Clean up build files
make clean
```

## Game Commands

- **Movement:** `north`, `south`, `east`, `west` (or `n`, `s`, `e`, `w`)
- **Items:** `take <item>`, `drop <number>`, `inventory` (or `inv`)
- **NPCs:** `talk <person>`, `attack <enemy>`, `say <something>`
- **Game:** `save`, `load`, `help` (or `h`), `quit` (or `q`)

## What I Learned

This project was a huge leap forward in my C programming journey! I learned:

- **Dynamic Memory Allocation** - Using `malloc()` and `free()` to manage arrays of rooms, items, and NPCs
- **File I/O Operations** - Parsing structured world data from text files and saving/loading player state
- **Multi-file Project Structure** - Organizing code into logical modules with proper header files
- **Basic Combat Simulation** - Building turn-based logic, enemy AI response, and reward mechanics
- **Advanced Data Structures** - Building linked systems where rooms connect to each other and players have inventories
- **Terminal UX** - Using ANSI color codes and layout tricks to make the game feel alive
- **Professional Build Systems** - Creating a Makefile that handles multiple source files automatically

The coolest part was realizing this is how real RPG systems are structured: modular, file-driven, dynamically evolving, and extensible.

## Technical Details

**Architecture:**
- `game_types.h` - Defines all data structures and function signatures
- `player.c` - Handles player creation, inventory, and save/load operations
- `world.c` - Manages room loading, navigation, and item placement
- `main.c` - Controls the main game loop and command interface

**Memory Management:**
- All major systems use dynamic allocation with full cleanup
- NPCs and items are added to rooms based on file data or scripted logic
- Inventory management supports growing/shrinking arrays without leaks

**File Format:**
- Room data: `id|name|description|north|south|east|west`
- Item data: `room_id|name|description|value|attack_bonus|defense_bonus`

---

*This project represents a major advancement in my C programming skills - from basic syntax to building complete interactive systems!* 