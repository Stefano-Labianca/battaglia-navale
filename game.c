#include <stdio.h>
#include <stdlib.h>

#include "./utility/rule_controller/rule_controller.h"
#include "./utility/save/save_game.h"
#include "./utility/play/newGame/newGame.h"
#include "./utility/maps_controller/MapsController.h"

char userChoice();

void mainLoop();
void showMenu();
int fileChoice();

int main()
{
    printf("                                  _/|                           \n");
    printf("                                 _|:|                           \n");
    printf("                               _|:::|                           \n");
    printf("                         _ /|  |::::|                           \n");
    printf("                         |::|  |::::|                           \n");
    printf("                         |::|  |:::::)__                        \n");
    printf("                       /:|:::: |::::::::|                       \n");
    printf("                      :::|::::_|::::::::|                       \n");
    printf("                ____(:::::::::::::::::::|___ _______         __ \n");
    printf("               (::::::::::::::::::::::::|:::|::::::|  ______|::)\n");
    printf("     ___________\\:::::::::::::::::::::::::::|:::|___|:::::::::|\n");
    printf("     \\::::::::::::::::::::::::::::::::::::::::::::::::::::::::|\n");
    printf("      |:::::::::::::::::::::::::::::::::::::::::::::::::::::::| \n");
    printf("  ____        _   _              _ _         _   _                  _      \n");
    printf(" | __ )  __ _| |_| |_ __ _  __ _| (_) __ _  | \\ | | __ ___   ____ _| | ___ \n");
    printf(" |  _ \\ / _` | __| __/ _` |/ _` | | |/ _` | |  \\| |/ _` \\ \\ / / _` | |/ _ \\ \n");
    printf(" | |_) | (_| | |_| || (_| | (_| | | | (_| | | |\\  | (_| |\\ V / (_| | |  __/\n");
    printf(" |____/ \\__,_|\\__|\\__\\__,_|\\__, |_|_|\\__,_| |_| \\_|\\__,_| \\_/ \\__,_|_|\\___|\n");
    printf("                           |___/                                           \n");

    mainLoop();

    system("pause");
    return EXIT_SUCCESS;
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
    int numFile;
    while (end == 0)
    {
        showMenu();
        choice = userChoice();

        if (choice == '1')
        {
            numFile = fileChoice();
            newGame(numFile);
        }

        else if (choice == '2')
        {
            numFile = fileChoice();
            //loadGame(numFile)
            // TODO: Gestione del caricamento dei dati di una partita salvata
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
    printf("\n  --- MENU' PRINCIPALE ---\n");
    printf("  1. Nuova partita\n");
    printf("  2. Carica partita\n");
    printf("  3. Visualizza regole\n\n");
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
    char input;
    input = ' ';

    do
    {
        printf("  Inserisci una scelta valida tra le opzioni disponibili: ");
        scanf("%c", &input);
        fflush(stdin);
    } while (input < '1' || input > '4');
    
    return input;
}


int fileChoice()
{
    int numFile;
     do
    {
        printf("  Inserisci il numero di salvataggio (da 1 a 7)");
        scanf("%d", &numFile);
        fflush(stdin);
    } while (numFile < 1 || numFile > 7);
    return numFile;
}