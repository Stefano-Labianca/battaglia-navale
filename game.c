#include <stdio.h>
#include <stdlib.h>

#include "./utility/rule_controller/rule_controller.c"
#include "./utility/save/save_game.c"

char userChoice();

void showLogo();
void mainLoop();
void showMenu();


int main()
{
    showLogo();
    mainLoop();

    system("pause");
    return EXIT_SUCCESS;
}


/**
 * @brief Mostra il logo del gioco
 */
void showLogo()
{
    printf("  ____        _   _              _ _         _   _                  _      \n");
	printf(" | __ )  __ _| |_| |_ __ _  __ _| (_) __ _  | \\ | | __ ___   ____ _| | ___ \n");
	printf(" |  _ \\ / _` | __| __/ _` |/ _` | | |/ _` | |  \\| |/ _` \\ \\ / / _` | |/ _ \\ \n");
	printf(" | |_) | (_| | |_| || (_| | (_| | | | (_| | | |\\  | (_| |\\ V / (_| | |  __/\n");
	printf(" |____/ \\__,_|\\__|\\__\\__,_|\\__, |_|_|\\__,_| |_| \\_|\\__,_| \\_/ \\__,_|_|\\___|\n");
	printf("                           |___/                                           \n\n");

    return;
}


/**
 * @brief Rappresenta il menù principale a cui l'utente può accedere
 * non appena avvia il programma.  
 * Da qui può scegliere se giocare una 
 * nuova partita, oppure se vuole continuare una partita salvata in 
 * precedenze, visualizzare le regole di gioco ed infine, uscire dal 
 * programma.
 */
void mainLoop()
{
    int end = 0;
    char choice = ' ';

    while (end == 0)
    {
        showMenu();
        choice = userChoice();

        if (choice == '1')
        {
            // Richiama la funzione gameLoop
        }

        else if (choice == '2')
        {
            showGameSlots();
            //TODO: Gestione del caricamento dei dati di una partita salvata
        }

        else if (choice == '3')
        {
            showRules();
        }

        else if (choice == '4')
        {
            end = 1;
        }

        else
        {
            printf("  Comando non valido\n\n");
        }
    }

    return;
}

/**
 * @brief Mostra a video il menù di gioco
 */
void showMenu()
{
    printf("\n\n  --- MENU' PRINCIPALE ---\n");
	printf("  1. Nuova partita\n");
	printf("  2. Carica partita\n");
	printf("  3. Visualizza regole\n\n\n");
	printf("  4. Esci dal gioco\n");
    printf("  -------------------------\n\n");


    return;
}


/**
 * @brief Fornisce la possibilità all'utente di scegliere cosa fare 
 * all'interno del menù di gioco, restituendo un carattere, che 
 * rappresenta la sua sua scelta. 
 * 
 * @return Carattere che rappresenta la scelta dell'utente. 
 */
char userChoice()
{
    char input = ' ';
    printf("  Inserisci una scelta valida tra le opzioni disponibili: ");
    scanf("%c", &input);
    fflush(stdin);

    return input;
}



