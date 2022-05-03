#include <stdio.h>
#include <stdlib.h>

#include "./rule_controller.h"



/**
 * @brief Mostra le regole di gioco
 */
void showRules()
{   
    FILE* rulesFile;
    char buffer[BUFFER_SIZE];

    rulesFile = fopen(RULES_PATH, "r");
    printf("\n  --- REGOLE DI GIOCO ---\n\n");

    while (fgets(buffer, BUFFER_SIZE, rulesFile) != NULL)
    {
        printf("  %s", buffer);
    }

    printf("\n  -----------------------\n\n");

    return;
}
