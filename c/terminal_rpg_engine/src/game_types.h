#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ANSI Color codes for terminal output
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"
#define COLOR_BOLD    "\033[1m"
#define COLOR_DIM     "\033[2m"

// Maximum string lengths
#define MAX_NAME_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 200
#define MAX_ROOMS 20
#define MAX_ITEMS_PER_ROOM 10
#define MAX_INVENTORY_SIZE 20

// Game item structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int value;
    int attack_bonus;
    int defense_bonus;
} Item;

// NPC (Non-Player Character) structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    char dialogue[MAX_DESCRIPTION_LENGTH];
    int health;
    int max_health;
    int attack;
    int defense;
    int gold_reward;
    int is_hostile;    // 0 = friendly, 1 = hostile
    int is_alive;      // 0 = dead, 1 = alive
} NPC;

// Player inventory (dynamic array)
typedef struct {
    Item* items;           // Dynamic array of items
    int count;            // Current number of items
    int capacity;         // Maximum capacity
} Inventory;

// Game room structure
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int north, south, east, west;  // Room connections (-1 if no exit)
    Item* room_items;              // Dynamic array of items in this room
    int item_count;                // Number of items in room
    NPC* room_npcs;                // Dynamic array of NPCs in this room
    int npc_count;                 // Number of NPCs in room
} Room;

// Player character structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    int health;
    int max_health;
    int attack;
    int defense;
    int gold;
    int current_room;
    Inventory inventory;
} Player;

// Game world structure
typedef struct {
    Room* rooms;           // Dynamic array of rooms
    int room_count;        // Number of rooms loaded
    Player player;         // Player character
    int game_running;      // Game state flag
} GameWorld;

// Function declarations for all our modules
// Player functions
Player* create_player(const char* name);
void free_player(Player* player);
void save_player(Player* player, const char* filename);
int load_player(Player* player, const char* filename);

// Inventory functions  
void init_inventory(Inventory* inv, int capacity);
void free_inventory(Inventory* inv);
int add_item_to_inventory(Inventory* inv, Item item);
int remove_item_from_inventory(Inventory* inv, int index);
void display_inventory(Inventory* inv);

// World functions
GameWorld* create_world();
void free_world(GameWorld* world);
int load_world_from_file(GameWorld* world, const char* filename);
int load_room_items(GameWorld* world, const char* items_file);
void setup_npcs(GameWorld* world);
void display_room(GameWorld* world);
int move_player(GameWorld* world, const char* direction);

// Game engine functions
void game_loop(GameWorld* world);
void process_command(GameWorld* world, const char* command);
void display_help();
void display_startup_banner();
void display_ascii_box(const char* text);

// Combat and NPC functions
void talk_to_npc(GameWorld* world, const char* npc_name);
void attack_npc(GameWorld* world, const char* npc_name);
int calculate_player_attack(Player* player);
int calculate_player_defense(Player* player);

#endif // GAME_TYPES_H 