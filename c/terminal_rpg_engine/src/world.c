#include "game_types.h"

// Create a new game world with dynamic memory allocation
GameWorld* create_world() {
    GameWorld* world = (GameWorld*)malloc(sizeof(GameWorld));
    if (!world) {
        printf("Error: Could not allocate memory for game world!\n");
        return NULL;
    }
    
    world->rooms = NULL;
    world->room_count = 0;
    world->game_running = 1;
    
    printf("%s%sGame world created successfully.%s\n", COLOR_GREEN, COLOR_BOLD, COLOR_RESET);
    return world;
}

// Free all world memory
void free_world(GameWorld* world) {
    if (!world) return;
    
    // Free all room memory and their items/NPCs
    if (world->rooms) {
        for (int i = 0; i < world->room_count; i++) {
            if (world->rooms[i].room_items) {
                free(world->rooms[i].room_items);
            }
            if (world->rooms[i].room_npcs) {
                free(world->rooms[i].room_npcs);
            }
        }
        free(world->rooms);
    }
    
    // Free player memory
    free_player(&world->player);
    
    free(world);
    printf("World memory successfully freed.\n");
}

// Load world data from file (demonstrates file I/O)
int load_world_from_file(GameWorld* world, const char* rooms_file) {
    FILE* file = fopen(rooms_file, "r");
    if (!file) {
        printf("Error: Could not open rooms file %s\n", rooms_file);
        return 0;
    }
    
    // Read number of rooms
    if (fscanf(file, "%d", &world->room_count) != 1) {
        printf("Error reading room count from file\n");
        fclose(file);
        return 0;
    }
    
    // Allocate memory for rooms array
    world->rooms = (Room*)malloc(world->room_count * sizeof(Room));
    if (!world->rooms) {
        printf("Error: Could not allocate memory for rooms!\n");
        fclose(file);
        return 0;
    }
    
    // Read each room
    for (int i = 0; i < world->room_count; i++) {
        Room* room = &world->rooms[i];
        char line[500];
        
        // Skip any remaining newline
        if (i == 0) fgetc(file);
        
        if (!fgets(line, sizeof(line), file)) {
            printf("Error reading room %d from file\n", i);
            break;
        }
        
        // Parse room data (format: id|name|description|north|south|east|west)
        char* token = strtok(line, "|");
        if (token) room->id = atoi(token);
        
        token = strtok(NULL, "|");
        if (token) strncpy(room->name, token, MAX_NAME_LENGTH - 1);
        
        token = strtok(NULL, "|");
        if (token) strncpy(room->description, token, MAX_DESCRIPTION_LENGTH - 1);
        
        token = strtok(NULL, "|");
        if (token) room->north = atoi(token);
        
        token = strtok(NULL, "|");
        if (token) room->south = atoi(token);
        
        token = strtok(NULL, "|");
        if (token) room->east = atoi(token);
        
        token = strtok(NULL, "|\n");
        if (token) room->west = atoi(token);
        
        // Initialize room items (will be loaded separately)
        room->room_items = NULL;
        room->item_count = 0;
        
        // Initialize room NPCs
        room->room_npcs = NULL;
        room->npc_count = 0;
    }
    
    fclose(file);
    printf("%s%sSuccessfully loaded %d rooms%s from %s\n", 
           COLOR_GREEN, COLOR_BOLD, world->room_count, COLOR_RESET, rooms_file);
    
    // Now load items for rooms
    load_room_items(world, "data/items.txt");
    
    // Add NPCs to rooms
    setup_npcs(world);
    
    return 1;
}

// Load items into rooms from file
int load_room_items(GameWorld* world, const char* items_file) {
    FILE* file = fopen(items_file, "r");
    if (!file) {
        printf("Warning: Could not open items file %s\n", items_file);
        return 0;  // Not critical if no items file
    }
    
    char line[500];
    
    // Count items per room first
    int* item_counts = (int*)calloc(world->room_count, sizeof(int));
    
    while (fgets(line, sizeof(line), file)) {
        int room_id = atoi(strtok(line, "|"));
        if (room_id >= 0 && room_id < world->room_count) {
            item_counts[room_id]++;
        }
    }
    
    // Allocate memory for each room's items
    for (int i = 0; i < world->room_count; i++) {
        if (item_counts[i] > 0) {
            world->rooms[i].room_items = (Item*)malloc(item_counts[i] * sizeof(Item));
            world->rooms[i].item_count = 0;  // Will increment as we add items
        }
    }
    
    // Rewind file and read items
    fseek(file, 0, SEEK_SET);
    
    while (fgets(line, sizeof(line), file)) {
        Item item;
        
        // Parse item data (format: room_id|name|description|value|attack|defense)
        char* token = strtok(line, "|");
        int room_id = atoi(token);
        
        if (room_id < 0 || room_id >= world->room_count) continue;
        
        token = strtok(NULL, "|");
        if (token) strncpy(item.name, token, MAX_NAME_LENGTH - 1);
        
        token = strtok(NULL, "|");
        if (token) strncpy(item.description, token, MAX_DESCRIPTION_LENGTH - 1);
        
        token = strtok(NULL, "|");
        if (token) item.value = atoi(token);
        
        token = strtok(NULL, "|");
        if (token) item.attack_bonus = atoi(token);
        
        token = strtok(NULL, "|\n");
        if (token) item.defense_bonus = atoi(token);
        
        // Add item to room
        Room* room = &world->rooms[room_id];
        if (room->room_items && room->item_count < item_counts[room_id]) {
            room->room_items[room->item_count] = item;
            room->item_count++;
        }
    }
    
    free(item_counts);
    fclose(file);
    printf("%s%sSuccessfully loaded room items%s from %s\n", 
           COLOR_GREEN, COLOR_BOLD, COLOR_RESET, items_file);
    return 1;
}

// Display current room information
void display_room(GameWorld* world) {
    if (!world || !world->rooms) return;
    
    Room* current_room = &world->rooms[world->player.current_room];
    
    printf("\n╔");
    for (int i = 0; i < (int)strlen(current_room->name) + 4; i++) printf("═");
    printf("╗\n");
    printf("║ %s%s%s%s ║\n", COLOR_CYAN, COLOR_BOLD, current_room->name, COLOR_RESET);
    printf("╚");
    for (int i = 0; i < (int)strlen(current_room->name) + 4; i++) printf("═");
    printf("╝\n");
    
    printf("%s\n", current_room->description);
    
    // Show available exits
    printf("\n%s%sExits:%s ", COLOR_MAGENTA, COLOR_BOLD, COLOR_RESET);
    int has_exit = 0;
    if (current_room->north != -1) { printf("%snorth%s ", COLOR_GREEN, COLOR_RESET); has_exit = 1; }
    if (current_room->south != -1) { printf("%ssouth%s ", COLOR_GREEN, COLOR_RESET); has_exit = 1; }
    if (current_room->east != -1) { printf("%seast%s ", COLOR_GREEN, COLOR_RESET); has_exit = 1; }
    if (current_room->west != -1) { printf("%swest%s ", COLOR_GREEN, COLOR_RESET); has_exit = 1; }
    if (!has_exit) printf("%snone%s", COLOR_RED, COLOR_RESET);
    printf("\n");
    
    // Show items in room
    if (current_room->item_count > 0) {
        printf("\n%s%sItems here:%s\n", COLOR_YELLOW, COLOR_BOLD, COLOR_RESET);
        for (int i = 0; i < current_room->item_count; i++) {
            printf("• %s%s%s: %s\n", 
                   COLOR_BOLD, current_room->room_items[i].name, COLOR_RESET,
                   current_room->room_items[i].description);
        }
    }
    
    // Show NPCs in room
    if (current_room->npc_count > 0) {
        printf("\n%s%sPeople here:%s\n", COLOR_CYAN, COLOR_BOLD, COLOR_RESET);
        for (int i = 0; i < current_room->npc_count; i++) {
            NPC* npc = &current_room->room_npcs[i];
            if (npc->is_alive) {
                if (npc->is_hostile) {
                    printf("⚔ %s%s%s: %s %s(HOSTILE)%s\n", 
                           COLOR_RED, npc->name, COLOR_RESET,
                           npc->description, COLOR_RED, COLOR_RESET);
                } else {
                    printf("😊 %s%s%s: %s\n", 
                           COLOR_GREEN, npc->name, COLOR_RESET,
                           npc->description);
                }
            } else {
                printf("💀 %s%s%s (dead)\n", COLOR_DIM, npc->name, COLOR_RESET);
            }
        }
    }
    
    printf("\n");
}

// Move player in specified direction
int move_player(GameWorld* world, const char* direction) {
    if (!world || !world->rooms) return 0;
    
    Room* current_room = &world->rooms[world->player.current_room];
    int new_room = -1;
    
    // Determine which direction to move
    if (strcmp(direction, "north") == 0 || strcmp(direction, "n") == 0) {
        new_room = current_room->north;
    } else if (strcmp(direction, "south") == 0 || strcmp(direction, "s") == 0) {
        new_room = current_room->south;
    } else if (strcmp(direction, "east") == 0 || strcmp(direction, "e") == 0) {
        new_room = current_room->east;
    } else if (strcmp(direction, "west") == 0 || strcmp(direction, "w") == 0) {
        new_room = current_room->west;
    } else {
        printf("Invalid direction. Use: north, south, east, west (or n, s, e, w)\n");
        return 0;
    }
    
    // Check if exit exists
    if (new_room == -1) {
        printf("You can't go that way!\n");
        return 0;
    }
    
    // Check if room exists
    if (new_room < 0 || new_room >= world->room_count) {
        printf("Error: Invalid room connection!\n");
        return 0;
    }
    
    // Move player
    world->player.current_room = new_room;
    printf("You move %s.\n", direction);
    
    return 1;
}

// Setup NPCs in specific rooms
void setup_npcs(GameWorld* world) {
    // Add friendly blacksmith to Blacksmith Shop (room 2)
    Room* blacksmith_room = &world->rooms[2];
    blacksmith_room->room_npcs = (NPC*)malloc(1 * sizeof(NPC));
    blacksmith_room->npc_count = 1;
    
    NPC* blacksmith = &blacksmith_room->room_npcs[0];
    strncpy(blacksmith->name, "Eldric the Blacksmith", MAX_NAME_LENGTH - 1);
    strncpy(blacksmith->description, "A burly man with soot-covered hands who knows the area well", MAX_DESCRIPTION_LENGTH - 1);
    strncpy(blacksmith->dialogue, "Welcome, traveler! I heard there's a nasty troll lurking in the abandoned cave. You'll need good weapons to face it!", MAX_DESCRIPTION_LENGTH - 1);
    blacksmith->health = 50;
    blacksmith->max_health = 50;
    blacksmith->attack = 5;
    blacksmith->defense = 3;
    blacksmith->gold_reward = 0;
    blacksmith->is_hostile = 0;  // Friendly
    blacksmith->is_alive = 1;
    
    // Add hostile troll to Abandoned Cave (room 3)
    Room* cave_room = &world->rooms[3];
    cave_room->room_npcs = (NPC*)malloc(1 * sizeof(NPC));
    cave_room->npc_count = 1;
    
    NPC* troll = &cave_room->room_npcs[0];
    strncpy(troll->name, "Cave Troll", MAX_NAME_LENGTH - 1);
    strncpy(troll->description, "A massive, ugly creature with yellowed fangs and bloodshot eyes", MAX_DESCRIPTION_LENGTH - 1);
    strncpy(troll->dialogue, "GRAAAHHHH! WHO DARES ENTER MY CAVE?!", MAX_DESCRIPTION_LENGTH - 1);
    troll->health = 40;
    troll->max_health = 40;
    troll->attack = 15;
    troll->defense = 8;
    troll->gold_reward = 50;  // Reward for defeating it
    troll->is_hostile = 1;    // Hostile
    troll->is_alive = 1;
    
    printf("%s%sNPCs added to the world:%s Friendly blacksmith and hostile troll!\n", 
           COLOR_GREEN, COLOR_BOLD, COLOR_RESET);
} 