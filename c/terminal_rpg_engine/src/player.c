#include "game_types.h"

// Create a new player with dynamic memory allocation
Player* create_player(const char* name) {
    Player* player = (Player*)malloc(sizeof(Player));
    if (!player) {
        printf("Error: Could not allocate memory for player!\n");
        return NULL;
    }
    
    // Initialize player stats
    strncpy(player->name, name, MAX_NAME_LENGTH - 1);
    player->name[MAX_NAME_LENGTH - 1] = '\0';  // Ensure null termination
    player->health = 100;
    player->max_health = 100;
    player->attack = 10;
    player->defense = 5;
    player->gold = 0;          // Start with no gold
    player->current_room = 0;  // Start in room 0
    
    // Initialize dynamic inventory
    init_inventory(&player->inventory, MAX_INVENTORY_SIZE);
    
    printf("%s%sWelcome to the Terminal RPG, %s%s%s!%s\n", 
           COLOR_GREEN, COLOR_BOLD, COLOR_CYAN, player->name, COLOR_GREEN, COLOR_RESET);
    
    return player;
}

// Free player memory (important for preventing memory leaks!)
void free_player(Player* player) {
    if (player) {
        free_inventory(&player->inventory);
        printf("Player memory successfully freed.\n");
    }
}

// Save player data to file (file I/O demonstration)
void save_player(Player* player, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not save game to %s\n", filename);
        return;
    }
    
    // Write player basic stats
    fprintf(file, "%s\n", player->name);
    fprintf(file, "%d %d\n", player->health, player->max_health);
    fprintf(file, "%d %d\n", player->attack, player->defense);
    fprintf(file, "%d\n", player->current_room);
    
    // Write inventory data
    fprintf(file, "%d\n", player->inventory.count);
    for (int i = 0; i < player->inventory.count; i++) {
        Item* item = &player->inventory.items[i];
        fprintf(file, "%s|%s|%d|%d|%d\n", 
                item->name, item->description, 
                item->value, item->attack_bonus, item->defense_bonus);
    }
    
    fclose(file);
    printf("Game saved successfully to %s!\n", filename);
}

// Load player data from file (file I/O demonstration)
int load_player(Player* player, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("No saved game found at %s\n", filename);
        return 0;  // File doesn't exist, not an error
    }
    
    // Read player basic stats
    if (fscanf(file, "%49s", player->name) != 1) {
        printf("Error reading player name from save file\n");
        fclose(file);
        return -1;
    }
    
    if (fscanf(file, "%d %d", &player->health, &player->max_health) != 2) {
        printf("Error reading player health from save file\n");
        fclose(file);
        return -1;
    }
    
    if (fscanf(file, "%d %d", &player->attack, &player->defense) != 2) {
        printf("Error reading player combat stats from save file\n");
        fclose(file);
        return -1;
    }
    
    if (fscanf(file, "%d", &player->current_room) != 1) {
        printf("Error reading player location from save file\n");
        fclose(file);
        return -1;
    }
    
    // Read inventory
    int item_count;
    if (fscanf(file, "%d", &item_count) != 1) {
        printf("Error reading inventory count from save file\n");
        fclose(file);
        return -1;
    }
    
    // Clear current inventory and resize if needed
    free_inventory(&player->inventory);
    init_inventory(&player->inventory, MAX_INVENTORY_SIZE);
    
    // Read each inventory item
    for (int i = 0; i < item_count; i++) {
        Item item;
        char line[500];
        
        // Read the full line (skip any remaining newline)
        if (i == 0) fgetc(file);  // Skip newline after count
        if (!fgets(line, sizeof(line), file)) {
            printf("Error reading item %d from save file\n", i);
            break;
        }
        
        // Parse the item data (format: name|description|value|attack|defense)
        char* token = strtok(line, "|");
        if (token) strncpy(item.name, token, MAX_NAME_LENGTH - 1);
        
        token = strtok(NULL, "|");
        if (token) strncpy(item.description, token, MAX_DESCRIPTION_LENGTH - 1);
        
        token = strtok(NULL, "|");
        if (token) item.value = atoi(token);
        
        token = strtok(NULL, "|");
        if (token) item.attack_bonus = atoi(token);
        
        token = strtok(NULL, "|\n");
        if (token) item.defense_bonus = atoi(token);
        
        // Add item to inventory
        add_item_to_inventory(&player->inventory, item);
    }
    
    fclose(file);
    printf("Game loaded successfully! Welcome back, %s!\n", player->name);
    return 1;  // Success
}

// Initialize dynamic inventory
void init_inventory(Inventory* inv, int capacity) {
    inv->items = (Item*)malloc(capacity * sizeof(Item));
    if (!inv->items) {
        printf("Error: Could not allocate memory for inventory!\n");
        inv->capacity = 0;
        inv->count = 0;
        return;
    }
    
    inv->capacity = capacity;
    inv->count = 0;
    printf("%s%sInventory initialized%s with capacity for %s%d%s items.\n", 
           COLOR_GREEN, COLOR_BOLD, COLOR_RESET, COLOR_YELLOW, capacity, COLOR_RESET);
}

// Free inventory memory
void free_inventory(Inventory* inv) {
    if (inv->items) {
        free(inv->items);
        inv->items = NULL;
        inv->count = 0;
        inv->capacity = 0;
    }
}

// Add item to dynamic inventory
int add_item_to_inventory(Inventory* inv, Item item) {
    if (inv->count >= inv->capacity) {
        printf("Inventory is full! Cannot pick up %s.\n", item.name);
        return 0;
    }
    
    inv->items[inv->count] = item;
    inv->count++;
    printf("%s✓ Picked up:%s %s%s%s\n", COLOR_GREEN, COLOR_RESET, COLOR_BOLD, item.name, COLOR_RESET);
    return 1;
}

// Remove item from inventory
int remove_item_from_inventory(Inventory* inv, int index) {
    if (index < 0 || index >= inv->count) {
        printf("Invalid item index!\n");
        return 0;
    }
    
    printf("%s✗ Dropped:%s %s%s%s\n", COLOR_RED, COLOR_RESET, COLOR_BOLD, inv->items[index].name, COLOR_RESET);
    
    // Shift remaining items down
    for (int i = index; i < inv->count - 1; i++) {
        inv->items[i] = inv->items[i + 1];
    }
    inv->count--;
    return 1;
}

// Display player inventory
void display_inventory(Inventory* inv) {
    printf("\n");
    printf("╔═══════════════════════╗\n");
    printf("║ %s%sYour Inventory%s       ║\n", COLOR_YELLOW, COLOR_BOLD, COLOR_RESET);
    printf("╚═══════════════════════╝\n");
    
    if (inv->count == 0) {
        printf("%s%sYour inventory is empty.%s\n", COLOR_DIM, COLOR_RESET, COLOR_RESET);
        return;
    }
    
    for (int i = 0; i < inv->count; i++) {
        Item* item = &inv->items[i];
        printf("%s%d.%s %s%s%s - %s\n", 
               COLOR_CYAN, i + 1, COLOR_RESET, 
               COLOR_BOLD, item->name, COLOR_RESET, 
               item->description);
        if (item->attack_bonus > 0) {
            printf("   %s⚔ Attack bonus: +%d%s\n", COLOR_RED, item->attack_bonus, COLOR_RESET);
        }
        if (item->defense_bonus > 0) {
            printf("   %s🛡 Defense bonus: +%d%s\n", COLOR_BLUE, item->defense_bonus, COLOR_RESET);
        }
        if (item->value > 0) {
            printf("   %s💰 Value: %d gold%s\n", COLOR_YELLOW, item->value, COLOR_RESET);
        }
    }
    printf("\n");
} 