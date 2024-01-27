#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ANSI_BOLD "\033[1m"
#define ANSI_RESET "\033[0m"

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
        if (index2 == -1) {
            printf("Computing effectiveness of %s move against %s type:\n", pokemon_types[index3], pokemon_types[index1]);
        } else {
            printf("Computing effectiveness of %s move against %s, %s type:\n", pokemon_types[index3], pokemon_types[index1], pokemon_types[index2]);
        }
    } else {
        printf("Invalid indices\n");
        return;
    }
    
    if (effectiveness != -1.0) {
        if (effectiveness == 0.25 || effectiveness == 0.5) {
            printf("%.2f - It's not very effective.\n", effectiveness);
        } else if (effectiveness == 2.0 || effectiveness == 4.0) {
            printf("%.1f - It's super effective!\n", effectiveness);
        } else if (effectiveness == 0.0) {
            printf("%.1f - The defending Pokemon is immune!\n", effectiveness);
        }
        else if (effectiveness == 1.0) {
            printf("%.1f - Neutral\n", effectiveness);
        }
    }
}

void listOffense(int index1, char ***SE, char ***NVE, char ***Im) {
    // Allocate memory for SE, NVE, and Im arrays
    *SE = malloc(NUM_TYPES * sizeof(char *));
    *NVE = malloc(NUM_TYPES * sizeof(char *));
    *Im = malloc(NUM_TYPES * sizeof(char *));


    // Check if memory allocation succeeded
    if (*SE == NULL || *NVE == NULL || *Im == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Populate SE, NVE, and Im arrays
    int se_count = 0, nve_count = 0, im_count = 0;
    for (int i = 0; i < NUM_TYPES; i++) {
        if (type_chart[index1][i] == 2.0) {
            (*SE)[se_count] = strdup(pokemon_types[i]);
            se_count++;
        } else if (type_chart[index1][i] == 0.5) {
            (*NVE)[nve_count] = strdup(pokemon_types[i]);
            nve_count++;
        } else if (type_chart[index1][i] == 0.0) {
            (*Im)[im_count] = strdup(pokemon_types[i]);
            im_count++;
        }
    }
    
    // Print SE, NVE, and Im arrays side by side with 20 characters spacing
    printf("Offensive Characteristics of %s Type\n", pokemon_types[index1]);
    printf("%-20s%-20s%-20s\n", "Super Effective", "Not Very Effective", "Won't affect");
    for (int j = 0; j < se_count || j < nve_count || j < im_count; j++) {
        if (j < se_count) {
            printf("%-20s", (*SE)[j]); // Aligns SE column
        } else {
            printf("%-20s", ""); // Print an empty string with width 20
        }
        if (j < nve_count) {
            printf("%-20s", (*NVE)[j]); // Aligns NVE column
        } else {
            printf("%-20s", ""); // Print an empty string with width 20
        }
        if (j < im_count) {
            printf("%-20s\n", (*Im)[j]); // Aligns Im column
        } else {
            printf("\n"); // Move to the next line
        }
    }
}

void listDefense(int index1, char ***SE, char ***NVE, char ***Im) {
    // Allocate memory for SE, NVE, and Im arrays
    *SE = malloc(NUM_TYPES * sizeof(char *));
    *NVE = malloc(NUM_TYPES * sizeof(char *));
    *Im = malloc(NUM_TYPES * sizeof(char *));


    // Check if memory allocation succeeded
    if (*SE == NULL || *NVE == NULL || *Im == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Populate SE, NVE, and Im arrays
    int se_count = 0, nve_count = 0, im_count = 0;
    for (int i = 0; i < NUM_TYPES; i++) {
        if (type_chart[i][index1] == 2.0) {
            (*SE)[se_count] = strdup(pokemon_types[i]);
            se_count++;
        } else if (type_chart[i][index1] == 0.5) {
            (*NVE)[nve_count] = strdup(pokemon_types[i]);
            nve_count++;
        } else if (type_chart[i][index1] == 0.0) {
            (*Im)[im_count] = strdup(pokemon_types[i]);
            im_count++;
        }
    }
    
    // Print SE, NVE, and Im arrays side by side with 20 characters spacing
    printf("Defensive Characteristics of %s Type\n", pokemon_types[index1]);
    printf("%-20s%-20s%-20s\n", "Weak to", "Resists", "Immune to");
    for (int j = 0; j < se_count || j < nve_count || j < im_count; j++) {
        if (j < se_count) {
            printf("%-20s", (*SE)[j]); // Aligns SE column
        } else {
            printf("%-20s", ""); // Print an empty string with width 20
        }
        if (j < nve_count) {
            printf("%-20s", (*NVE)[j]); // Aligns NVE column
        } else {
            printf("%-20s", ""); // Print an empty string with width 20
        }
        if (j < im_count) {
            printf("%-20s\n", (*Im)[j]); // Aligns Im column
        } else {
            printf("\n"); // Move to the next line
        }
    }
}


void combo(int index1, int index2, char ***SE, char ***NVE, char ***Im){
    // Allocate memory for SE, NVE, and Im arrays
    *SE = malloc(NUM_TYPES * sizeof(char *));
    *NVE = malloc(NUM_TYPES * sizeof(char *));
    *Im = malloc(NUM_TYPES * sizeof(char *));


    // Check if memory allocation succeeded
    if (*SE == NULL || *NVE == NULL || *Im == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    
    int se_count = 0, nve_count = 0, im_count = 0;
    for (int i = 0; i < NUM_TYPES; i++) {
        if ((type_chart[i][index1] == 2.0 && type_chart[i][index2] == 2.0) ||
        (type_chart[i][index1] == 1.0 && type_chart[i][index2] == 2.0) ||
        (type_chart[i][index1] == 2.0 && type_chart[i][index2] == 1.0)) {
            (*SE)[se_count] = strdup(pokemon_types[i]);
            se_count++; 
        } else if ((type_chart[i][index1] == 0.5 && type_chart[i][index2] == 0.5) || (type_chart[i][index1] == 0.5 && type_chart[i][index2] == 1.0) || (type_chart[i][index1] == 1.0 && type_chart[i][index2] == 0.5)) {
                (*NVE)[nve_count] = strdup(pokemon_types[i]);
                nve_count++;
} else if (type_chart[i][index1] == 0.0 || type_chart[i][index2] == 0.0) {
        (*Im)[im_count] = strdup(pokemon_types[i]);
        im_count++;
}

    }
    
    printf("Defensive Characteristics of %s, %s type\n", pokemon_types[index1], pokemon_types[index2]);
printf("%-20s%-20s%-20s\n", "Weak to", "Resists", "Immune to");

for (int j = 0; j < se_count || j < nve_count || j < im_count; j++) {
    // Print Pokémon types for Weak to column
    if (j < se_count) {
        if ((type_chart[findIndex((*SE)[j])][index1] == 2.0 && type_chart[findIndex((*SE)[j])][index2] == 2.0)) {
            printf("*%s", (*SE)[j]); // Print with asterisks for super effectiveness
            // Adjust spacing based on string length
            int len = strlen((*SE)[j]);
            printf("%-*s", 19 - len, ""); // Fill remaining space
        } else {
            printf("%-20s", (*SE)[j]); // Aligns SE column
        }
    } else {
        printf("%-20s", ""); // Print an empty string with width 20
    }
    
    // Print Pokémon types for Resists column
    if (j < nve_count) {
        if ((type_chart[findIndex((*NVE)[j])][index1] == 0.5 && type_chart[findIndex((*NVE)[j])][index2] == 0.5)) {
            printf("_%s", (*NVE)[j]); // Print with underscores for not very effectiveness
            // Adjust spacing based on string length
            int len = strlen((*NVE)[j]);
            printf("%-*s", 19 - len, ""); // Fill remaining space
        } else {
            printf("%-20s", (*NVE)[j]); // Aligns NVE column
        }
    } else {
        printf("%-20s", ""); // Print an empty string with width 20
    }
    
    // Print Pokémon types for Immune to column
    if (j < im_count) {
        printf("%-20s\n", (*Im)[j]); // Aligns Im column
    } else {
        printf("\n"); // Move to the next line
    }
}

}

int main() {
    char cmd; // Command character
    char type[MAXLENGTH]; // Pokémon type
    int index1 = -1; // Index of Primary type
    int index2 = -1; // Index of Secondary type
    int index3 = -1; // Index of move type
    
    char **SE, **NVE, **Im;
    
   do {
        // Ask for command
        printf("Enter command (h for Help): ");
        scanf(" %c", &cmd);
        
        // Process command using switch-case
        switch(cmd) {
            case 'h':
                printf("Available commands:\n");
                printf("t: Enter Primary type\n");
                printf("s: Enter Secondary type\n");
                printf("m: Enter move type\n");
                printf("c: Compute effectiveness\n");
                printf("o: List offensive characteristics\n");
                printf("d: List defensive characteristics\n");
                printf("q: Quit the program\n");
                break;
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
            case 'o':
                listOffense(index1, &SE, &NVE, &Im);
                break;
            case 'd':
                listDefense(index1, &SE, &NVE, &Im);
                break;
            case 'l':
                combo(index1,index2, &SE, &NVE, &Im);
                break;
            case 'q':
                if (SE != NULL) {
                    for (int i = 0; i < NUM_TYPES; i++) {
                        free(SE[i]);
                    }
                    free(SE);
                }
                if (NVE != NULL) {
                    for (int i = 0; i < NUM_TYPES; i++) {
                        free(NVE[i]);
                    }
                    free(NVE);
                }
                if (Im != NULL) {
                    for (int i = 0; i < NUM_TYPES; i++) {
                        free(Im[i]);
                    }
                    free(Im);
                }
                printf("Bye Bye!\n");
                break;
            default:
                printf("Unknown command. Enter 'h' for help.\n");
                break;
        }
    } while (cmd != 'q');
    return 0;
}
