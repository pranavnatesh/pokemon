#include <stdio.h>
#include <string.h>

#define NUM_TYPES 18 // Number of Pokémon types
#define MAXLENGTH 9 // Maximum length of a Pokémon type name

// Array of Pokémon types
char *pokemon_types[NUM_TYPES] = {
    "bug", "dark", "dragon", "electric", "fairy", "fighting", "fire", "flying", "ghost", "grass", "ground", "ice", "normal", "poison", "psychic", "rock", "steel", "water"
};

float type_chart[NUM_TYPES][NUM_TYPES] = {
    //                  Bug     Dark    Dragon  Electric    Fairy   Fighting    Fire    Flying  Ghost   Grass   Ground  Ice     Normal  Poison  Psychic Rock    Steel   Water
    /* Bug */       {   1.0,    2.0,    1.0,    1.0,        0.5,    0.5,        0.5,    0.5,    0.5,    2.0,    1.0,    1.0,    1.0,    0.5,    2.0,    1.0,    0.5,    1.0},
    /* Dark */      {   1.0,    0.5,    1.0,    1.0,        0.5,    0.5,        1.0,    1.0,    2.0,    1.0,    1.0,    1.0,    1.0,    1.0,    2.0,    1.0,    1.0,    1.0},
    /* Dragon */    {   1.0,    1.0,    2.0,    1.0,        0.0,    1.0,        1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    0.5,    1.0},
    /* Electric */  {   1.0,    1.0,    0.5,    0.5,        1.0,    1.0,        1.0,    2.0,    1.0,    0.5,    0.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    2.0},
    /* Fairy */     {   1.0,    2.0,    2.0,    1.0,        1.0,    2.0,        0.5,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    0.5,    1.0,    1.0,    0.5,    1.0},
    /* Fighting */  {   0.5,    2.0,    1.0,    1.0,        0.5,    1.0,        1.0,    0.5,    0.0,    1.0,    1.0,    2.0,    2.0,    0.5,    0.5,    2.0,    2.0,    1.0},
    /* Fire */      {   2.0,    1.0,    0.5,    1.0,        1.0,    1.0,        0.5,    1.0,    1.0,    2.0,    1.0,    2.0,    1.0,    1.0,    1.0,    0.5,    2.0,    0.5},
    /* Flying */    {   2.0,    1.0,    1.0,    0.5,        1.0,    2.0,        1.0,    1.0,    1.0,    2.0,    1.0,    1.0,    1.0,    1.0,    1.0,    0.5,    0.5,    1.0},
    /* Ghost */     {   1.0,    0.5,    1.0,    1.0,        1.0,    1.0,        1.0,    1.0,    2.0,    1.0,    1.0,    1.0,    0.0,    1.0,    2.0,    1.0,    1.0,    1.0},
    /* Grass */     {   0.5,    1.0,    0.5,    1.0,        1.0,    1.0,        0.5,    0.5,    1.0,    0.5,    2.0,    1.0,    1.0,    0.5,    1.0,    2.0,    0.5,    2.0},
    /* Ground */    {   0.5,    1.0,    1.0,    2.0,        1.0,    1.0,        2.0,    0.0,    1.0,    0.5,    1.0,    1.0,    1.0,    2.0,    1.0,    2.0,    2.0,    1.0},
    /* Ice */       {   1.0,    1.0,    2.0,    1.0,        1.0,    1.0,        0.5,    2.0,    1.0,    2.0,    2.0,    0.5,    1.0,    1.0,    1.0,    1.0,    0.5,    0.5},
    /* Normal */    {   1.0,    1.0,    1.0,    1.0,        1.0,    1.0,        1.0,    1.0,    0.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    0.5,    0.5,    1.0},
    /* Poison */    {   1.0,    1.0,    1.0,    1.0,        2.0,    1.0,        1.0,    1.0,    0.5,    2.0,    0.5,    1.0,    1.0,    0.5,    1.0,    0.5,    0.0,    1.0},
    /* Psychic */   {   1.0,    0.0,    1.0,    1.0,        1.0,    2.0,        1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    2.0,    0.5,    1.0,    0.5,    1.0},
    /* Rock */      {   2.0,    1.0,    1.0,    1.0,        1.0,    0.5,        2.0,    2.0,    1.0,    1.0,    0.5,    2.0,    1.0,    1.0,    1.0,    1.0,    0.5,    1.0},
    /* Steel */     {   1.0,    1.0,    1.0,    0.5,        2.0,    1.0,        0.5,    1.0,    1.0,    1.0,    1.0,    2.0,    1.0,    1.0,    1.0,    2.0,    0.5,    0.5},
    /* Water */     {   1.0,    1.0,    0.5,    1.0,        1.0,    1.0,        2.0,    1.0,    1.0,    0.5,    2.0,    1.0,    1.0,    1.0,    1.0,    2.0,    1.0,    0.5}
};

// Function to find index of a type in pokemon_types array
int findIndex(char *type) {
    for (int i = 0; i < NUM_TYPES; i++) {
        if (strcmp(type, pokemon_types[i]) == 0) {
            return i;
        }
    }
    return -1; // Not found
}

// Function to compute effectiveness of a move
float compute(int index1, int index2, int index3) {
    if (index1 == -1 || index3 == -1) {
        return -1.0; // Invalid index
    }
    if (index2 == -1) return type_chart[index3][index1];
    else if (index2 != -1){
        return type_chart[index3][index1]*type_chart[index3][index2];
    }
}

void compute_and_print(int index1, int index2, int index3) {
    if (index1 == -1 || index3 == -1) {
        printf("Invalid indices. Please enter valid indices for both Pokémon type and move type.\n");
        return;
    }
    
    float effectiveness = compute(index1, index2, index3);
    if (effectiveness != -1.0) {
        printf("Computing effectiveness of %s move against %s type:\n%.1f ", pokemon_types[index3], pokemon_types[index1], effectiveness);
        if (effectiveness == 0.25 || effectiveness == 0.5){
            printf("- It's not very effective.\n");
        }
        else if (effectiveness == 2.0 || effectiveness == 4.0){
            printf("- It's super effective!\n");
        }
        else if (effectiveness == 0.0) printf("- The defending Pokemon is immune!\n");
    } else {
        printf("Invalid indices\n");
    }
}

int main() {
    char cmd; // Command character
    char type[MAXLENGTH]; // Pokémon type
    int index1 = -1; // Index of Primary type
    int index2 = -1; // Index of Secondary type
    int index3 = -1; // Index of move type
    
   do {
        // Ask for command
        printf("Enter command (t, s, m, c, q): ");
        scanf(" %c", &cmd);
        
        // Process command using switch-case
        switch(cmd) {
            case 't':
                printf("Enter Primary type: ");
                scanf("%s", type);
                index1 = findIndex(type);
                if (index1 != -1) {
                    // Type found
                } else {
                    printf("Type not found\n");
                }
                break;
            case 's':
                printf("Enter Secondary type: ");
                scanf("%s", type);
                index2 = findIndex(type);
                if (index2 != -1) {
                    // Type found
                } else {
                    printf("Type not found\n");
                }
                break;
            case 'm':
                if (index1 == -1) {
                    printf("No Pokémon type entered yet. Please enter a type using 't' command first.\n");
                    break;
                }
                printf("Enter move type: ");
                scanf("%s", type);
                index3 = findIndex(type);
                if (index3 != -1) {
                    // Move type found
                } else {
                    printf("Move type not found\n");
                }
                break;
            case 'c':
                compute_and_print(index1, index2, index3);
                break;
            case 'q':
                printf("Bye Bye! \n");
                break;
            default:
                printf("Unknown command. Enter 'h' for help.\n");
                break;
        }
    } while (cmd != 'q');
    return 0;
}
