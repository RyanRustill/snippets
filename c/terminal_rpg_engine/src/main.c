#include "game_types.h"

// Display ASCII box with text
void display_ascii_box(const char* text) {
    int len = strlen(text);
    printf("╔");
    for (int i = 0; i < len + 2; i++) printf("═");
    printf("╗\n");
    printf("║ %s%s%s ║\n", COLOR_BOLD, text, COLOR_RESET);
    printf("╚");
    for (int i = 0; i < len + 2; i++) printf("═");
    printf("╝\n");
}

// Display startup banner with branding
void display_startup_banner() {
    printf("\n");
    display_ascii_box("Terminal RPG Engine - Loading...");
}

// Display help information
void display_help() {
    printf("\n");
    display_ascii_box("Terminal RPG Commands");
    printf("\n%s%sMovement:%s north, south, east, west (or n, s, e, w)\n", COLOR_GREEN, COLOR_BOLD, COLOR_RESET);
    printf("%s%sActions:%s  look, inventory (inv), take/pick <item>, drop <num>\n", COLOR_YELLOW, COLOR_BOLD, COLOR_RESET);
    printf("%s%sSocial:%s   talk <person>, say <message>, attack <enemy>\n", COLOR_MAGENTA, COLOR_BOLD, COLOR_RESET);
    printf("%s%sGame:%s     save, load, help (h), quit (q)\n", COLOR_BLUE, COLOR_BOLD, COLOR_RESET);
    printf("\n");
}

// Process player commands
void process_command(GameWorld* world, const char* command) {
    char cmd_copy[100];
    strncpy(cmd_copy, command, sizeof(cmd_copy) - 1);
    cmd_copy[sizeof(cmd_copy) - 1] = '\0';
    
    // Convert to lowercase for easier parsing
    for (int i = 0; cmd_copy[i]; i++) {
        if (cmd_copy[i] >= 'A' && cmd_copy[i] <= 'Z') {
            cmd_copy[i] = cmd_copy[i] + 32;
        }
    }
    
    char* first_word = strtok(cmd_copy, " \n");
    if (!first_word) return;
    
    // Movement commands
    if (strcmp(first_word, "north") == 0 || strcmp(first_word, "n") == 0 ||
        strcmp(first_word, "south") == 0 || strcmp(first_word, "s") == 0 ||
        strcmp(first_word, "east") == 0 || strcmp(first_word, "e") == 0 ||
        strcmp(first_word, "west") == 0 || strcmp(first_word, "w") == 0) {
        
        if (move_player(world, first_word)) {
            display_room(world);
        }
    }
    // Look around
    else if (strcmp(first_word, "look") == 0 || strcmp(first_word, "l") == 0) {
        display_room(world);
    }
    // Show inventory
    else if (strcmp(first_word, "inventory") == 0 || strcmp(first_word, "inv") == 0) {
        display_inventory(&world->player.inventory);
    }
    // Take item
    else if (strcmp(first_word, "take") == 0 || strcmp(first_word, "get") == 0 || 
             strcmp(first_word, "pick") == 0 || strcmp(first_word, "pickup") == 0) {
        
        // Get the rest of the input as the item name (handle multi-word names)
        char* item_name = strtok(NULL, "\n");
        if (!item_name) {
            printf("Take what? Use: %stake <item name>%s\n", COLOR_CYAN, COLOR_RESET);
            return;
        }
        
        // Remove leading spaces
        while (*item_name == ' ') item_name++;
        
        // Convert item name to lowercase for matching
        char search_name[100];
        strncpy(search_name, item_name, sizeof(search_name) - 1);
        search_name[sizeof(search_name) - 1] = '\0';
        for (int i = 0; search_name[i]; i++) {
            if (search_name[i] >= 'A' && search_name[i] <= 'Z') {
                search_name[i] = search_name[i] + 32;
            }
        }
        
        Room* current_room = &world->rooms[world->player.current_room];
        int found = 0;
        
        for (int i = 0; i < current_room->item_count; i++) {
            // Convert room item name to lowercase for comparison
            char room_item_lower[MAX_NAME_LENGTH];
            strncpy(room_item_lower, current_room->room_items[i].name, MAX_NAME_LENGTH - 1);
            room_item_lower[MAX_NAME_LENGTH - 1] = '\0';
            for (int j = 0; room_item_lower[j]; j++) {
                if (room_item_lower[j] >= 'A' && room_item_lower[j] <= 'Z') {
                    room_item_lower[j] = room_item_lower[j] + 32;
                }
            }
            
            // Check if search term is contained in item name (case insensitive)
            if (strstr(room_item_lower, search_name) != NULL) {
                Item item = current_room->room_items[i];
                
                if (add_item_to_inventory(&world->player.inventory, item)) {
                    // Remove item from room
                    for (int j = i; j < current_room->item_count - 1; j++) {
                        current_room->room_items[j] = current_room->room_items[j + 1];
                    }
                    current_room->item_count--;
                    found = 1;
                }
                break;
            }
        }
        
        if (!found) {
            printf("There's no '%s%s%s' here.\n", COLOR_YELLOW, item_name, COLOR_RESET);
            if (current_room->item_count > 0) {
                printf("Available items: ");
                for (int i = 0; i < current_room->item_count; i++) {
                    printf("%s%s%s", COLOR_BOLD, current_room->room_items[i].name, COLOR_RESET);
                    if (i < current_room->item_count - 1) printf(", ");
                }
                printf("\n");
            }
        }
    }
    // Drop item
    else if (strcmp(first_word, "drop") == 0) {
        char* item_num_str = strtok(NULL, " \n");
        if (!item_num_str) {
            printf("Drop what? Use: drop <inventory number>\n");
            return;
        }
        
        int item_num = atoi(item_num_str) - 1; // Convert to 0-based index
        if (item_num < 0 || item_num >= world->player.inventory.count) {
            printf("Invalid item number. Check your inventory.\n");
            return;
        }
        
        // Get the item before removing it
        Item dropped_item = world->player.inventory.items[item_num];
        
        if (remove_item_from_inventory(&world->player.inventory, item_num)) {
            // Add item to current room (simplified - in a real game you'd expand room arrays)
            printf("You dropped the %s here.\n", dropped_item.name);
        }
    }
    // Save game
    else if (strcmp(first_word, "save") == 0) {
        save_player(&world->player, "savegame.txt");
    }
    // Load game
    else if (strcmp(first_word, "load") == 0) {
        int result = load_player(&world->player, "savegame.txt");
        if (result == 1) {
            // Make sure loaded room is valid
            if (world->player.current_room >= 0 && world->player.current_room < world->room_count) {
                display_room(world);
            } else {
                printf("Warning: Invalid room in save file, starting in town square.\n");
                world->player.current_room = 0;
                display_room(world);
            }
        }
    }
    // Show help
    else if (strcmp(first_word, "help") == 0 || strcmp(first_word, "h") == 0) {
        display_help();
    }
    // Quit game
    else if (strcmp(first_word, "quit") == 0 || strcmp(first_word, "q") == 0 || 
             strcmp(first_word, "exit") == 0) {
        printf("\n%s%sThanks for playing! %s\n", COLOR_CYAN, COLOR_BOLD, COLOR_RESET);  // Terminal branding
        world->game_running = 0;
    }
    // Talk to NPC
    else if (strcmp(first_word, "talk") == 0 || strcmp(first_word, "speak") == 0) {
        char* npc_name = strtok(NULL, "\n");
        if (!npc_name) {
            printf("Talk to whom? Use: %stalk <person name>%s\n", COLOR_CYAN, COLOR_RESET);
            return;
        }
        while (*npc_name == ' ') npc_name++;  // Remove leading spaces
        talk_to_npc(world, npc_name);
    }
    // Say something (roleplay)
    else if (strcmp(first_word, "say") == 0) {
        char* message = strtok(NULL, "\n");
        if (!message) {
            printf("Say what? Use: %ssay <message>%s\n", COLOR_CYAN, COLOR_RESET);
            return;
        }
        while (*message == ' ') message++;  // Remove leading spaces
        printf("\n%s%s%s says: \"%s%s%s\"\n\n", 
               COLOR_GREEN, world->player.name, COLOR_RESET,
               COLOR_WHITE, message, COLOR_RESET);
    }
    // Attack NPC
    else if (strcmp(first_word, "attack") == 0 || strcmp(first_word, "fight") == 0 || 
             strcmp(first_word, "kill") == 0) {
        char* npc_name = strtok(NULL, "\n");
        if (!npc_name) {
            printf("Attack whom? Use: %sattack <enemy name>%s\n", COLOR_CYAN, COLOR_RESET);
            return;
        }
        while (*npc_name == ' ') npc_name++;  // Remove leading spaces
        attack_npc(world, npc_name);
    }
    // Unknown command
    else {
        printf("I don't understand '%s'. Type 'help' for commands.\n", first_word);
    }
}

// Main game loop
void game_loop(GameWorld* world) {
    char input[100];
    
    printf("\n");
    display_ascii_box("Terminal RPG Engine");
    printf("\n%sA text-based RPG adventure!%s\n", COLOR_DIM, COLOR_RESET);
    printf("Type '%shelp%s' for commands.\n\n", COLOR_CYAN, COLOR_RESET);
    
    // Show starting room
    display_room(world);
    
    // Main game loop
    while (world->game_running) {
        printf("%s> %s", COLOR_BOLD, COLOR_RESET);
        fflush(stdout);  // Ensure prompt appears
        
        // Get user input
        if (fgets(input, sizeof(input), stdin)) {
            // Remove newline
            input[strcspn(input, "\n")] = 0;
            
            // Skip empty input
            if (strlen(input) == 0) continue;
            
            // Process the command
            process_command(world, input);
        } else {
            // EOF or error
            break;
        }
    }
}

// Main function
int main() {
    // Display startup banner with branding
    display_startup_banner();
    
    // Create game world
    GameWorld* world = create_world();
    if (!world) {
        printf("%s%sFailed to create game world!%s\n", COLOR_RED, COLOR_BOLD, COLOR_RESET);
        return 1;
    }
    
    // Load world data from files
    if (!load_world_from_file(world, "data/rooms.txt")) {
        printf("%s%sFailed to load world data!%s\n", COLOR_RED, COLOR_BOLD, COLOR_RESET);
        free_world(world);
        return 1;
    }
    
    printf("\n");
    
    // Create or load player
    char player_name[MAX_NAME_LENGTH];
    printf("%s%sEnter your character name:%s ", COLOR_MAGENTA, COLOR_BOLD, COLOR_RESET);
    fflush(stdout);
    
    if (fgets(player_name, sizeof(player_name), stdin)) {
        // Remove newline
        player_name[strcspn(player_name, "\n")] = 0;
        
        // Create player
        Player* player = create_player(player_name);
        if (!player) {
            printf("Failed to create player!\n");
            free_world(world);
            return 1;
        }
        
        // Copy player into world
        world->player = *player;
        free(player);  // Free the temporary player struct
        
        // Ask if they want to load a saved game
        printf("Load saved game? (y/n): ");
        char load_choice[10];
        if (fgets(load_choice, sizeof(load_choice), stdin)) {
            if (load_choice[0] == 'y' || load_choice[0] == 'Y') {
                load_player(&world->player, "savegame.txt");
            }
        }
        
        // Start the game
        game_loop(world);
    }
    
    // Cleanup
    free_world(world);
    printf("Game ended. Memory cleaned up successfully.\n");
    
    return 0;
}

// Calculate player's total attack with weapons
int calculate_player_attack(Player* player) {
    int total_attack = player->attack;
    
    // Add weapon bonuses from inventory
    for (int i = 0; i < player->inventory.count; i++) {
        total_attack += player->inventory.items[i].attack_bonus;
    }
    
    return total_attack;
}

// Calculate player's total defense with armor
int calculate_player_defense(Player* player) {
    int total_defense = player->defense;
    
    // Add armor bonuses from inventory
    for (int i = 0; i < player->inventory.count; i++) {
        total_defense += player->inventory.items[i].defense_bonus;
    }
    
    return total_defense;
}

// Talk to an NPC
void talk_to_npc(GameWorld* world, const char* npc_name) {
    Room* current_room = &world->rooms[world->player.current_room];
    
    // Convert search name to lowercase
    char search_name[100];
    strncpy(search_name, npc_name, sizeof(search_name) - 1);
    search_name[sizeof(search_name) - 1] = '\0';
    for (int i = 0; search_name[i]; i++) {
        if (search_name[i] >= 'A' && search_name[i] <= 'Z') {
            search_name[i] = search_name[i] + 32;
        }
    }
    
    // Find NPC in current room
    for (int i = 0; i < current_room->npc_count; i++) {
        NPC* npc = &current_room->room_npcs[i];
        
        if (!npc->is_alive) continue;
        
        // Convert NPC name to lowercase for comparison
        char npc_lower[MAX_NAME_LENGTH];
        strncpy(npc_lower, npc->name, MAX_NAME_LENGTH - 1);
        npc_lower[MAX_NAME_LENGTH - 1] = '\0';
        for (int j = 0; npc_lower[j]; j++) {
            if (npc_lower[j] >= 'A' && npc_lower[j] <= 'Z') {
                npc_lower[j] = npc_lower[j] + 32;
            }
        }
        
        // Check if search term matches
        if (strstr(npc_lower, search_name) != NULL) {
            printf("\n%s%s%s says:\n", COLOR_CYAN, npc->name, COLOR_RESET);
            printf("\"%s%s%s\"\n\n", COLOR_WHITE, npc->dialogue, COLOR_RESET);
            return;
        }
    }
    
    printf("There's no one named '%s%s%s' here to talk to.\n", COLOR_YELLOW, npc_name, COLOR_RESET);
}

// Attack an NPC
void attack_npc(GameWorld* world, const char* npc_name) {
    Room* current_room = &world->rooms[world->player.current_room];
    Player* player = &world->player;
    
    // Convert search name to lowercase
    char search_name[100];
    strncpy(search_name, npc_name, sizeof(search_name) - 1);
    search_name[sizeof(search_name) - 1] = '\0';
    for (int i = 0; search_name[i]; i++) {
        if (search_name[i] >= 'A' && search_name[i] <= 'Z') {
            search_name[i] = search_name[i] + 32;
        }
    }
    
    // Find NPC in current room
    for (int i = 0; i < current_room->npc_count; i++) {
        NPC* npc = &current_room->room_npcs[i];
        
        if (!npc->is_alive) {
            printf("The %s%s%s is already dead.\n", COLOR_DIM, npc->name, COLOR_RESET);
            return;
        }
        
        // Convert NPC name to lowercase for comparison
        char npc_lower[MAX_NAME_LENGTH];
        strncpy(npc_lower, npc->name, MAX_NAME_LENGTH - 1);
        npc_lower[MAX_NAME_LENGTH - 1] = '\0';
        for (int j = 0; npc_lower[j]; j++) {
            if (npc_lower[j] >= 'A' && npc_lower[j] <= 'Z') {
                npc_lower[j] = npc_lower[j] + 32;
            }
        }
        
        // Check if search term matches
        if (strstr(npc_lower, search_name) != NULL) {
            printf("\n%s⚔ You attack the %s!%s\n", COLOR_RED, npc->name, COLOR_RESET);
            
            // Calculate damage
            int player_attack = calculate_player_attack(player);
            int damage_dealt = player_attack - npc->defense;
            if (damage_dealt < 1) damage_dealt = 1;  // Minimum 1 damage
            
            npc->health -= damage_dealt;
            printf("%sYou deal %d damage!%s ", COLOR_YELLOW, damage_dealt, COLOR_RESET);
            
            if (npc->health <= 0) {
                // NPC dies
                npc->is_alive = 0;
                printf("%s%s%s has been defeated!\n", COLOR_GREEN, npc->name, COLOR_RESET);
                
                if (npc->gold_reward > 0) {
                    player->gold += npc->gold_reward;
                    printf("%s💰 You found %d gold!%s (Total: %s%d gold%s)\n", 
                           COLOR_YELLOW, npc->gold_reward, COLOR_RESET,
                           COLOR_BOLD, player->gold, COLOR_RESET);
                }
            } else {
                printf("(%s%d/%d HP remaining%s)\n", COLOR_RED, npc->health, npc->max_health, COLOR_RESET);
                
                // NPC attacks back if hostile and alive
                if (npc->is_hostile) {
                    int npc_damage = npc->attack - calculate_player_defense(player);
                    if (npc_damage < 1) npc_damage = 1;  // Minimum 1 damage
                    
                    player->health -= npc_damage;
                    printf("%s%s attacks you for %d damage!%s ", COLOR_RED, npc->name, npc_damage, COLOR_RESET);
                    
                    if (player->health <= 0) {
                        printf("%s%sYou have been defeated! GAME OVER!%s\n", COLOR_RED, COLOR_BOLD, COLOR_RESET);
                        world->game_running = 0;
                    } else {
                        printf("(%s%d/%d HP remaining%s)\n", COLOR_GREEN, player->health, player->max_health, COLOR_RESET);
                    }
                }
            }
            printf("\n");
            return;
        }
    }
    
    printf("There's no one named '%s%s%s' here to attack.\n", COLOR_YELLOW, npc_name, COLOR_RESET);
} 