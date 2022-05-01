#include <stdlib.h>
#include <stdio.h>

#include "./playGame.h"

void playGame(Round round)
{
    int turn;
    int whoPlay;
    Player player1;
    Player player2;
    int end;
    int AvailableShipsControl;
    int idWinner;
    player1 = getActivePlayer(round);
    player2 = getPassivePlayer(round);
    turn = getGameRound(round);
    whoPlay = getWhoPlay(round);
    end = 0;

    while (end == 0)
    {
        if (whoPlay == 1)
        {
            printf("\n\n\nORA GIOCA IL GIOCATORE 1");
            round = setActivePlayer(round, player1);
            round = setPassivePlayer(round, player2);
            round = newTurn(round);
            player1 = getActivePlayer(round);
            player2 = getPassivePlayer(round);
            whoPlay = 2;
        }
        else
        {
            printf("\n\n\nORA GIOCA IL GIOCATORE 2");
            round = setActivePlayer(round, player2);
            round = setPassivePlayer(round, player1);
            round = newTurn(round);
            player2 = getActivePlayer(round);
            player1 = getPassivePlayer(round);
            whoPlay = 1;
        }

        AvailableShipsControl = getAvailableShips(player2);
        if (AvailableShipsControl == 0)
        {
            end = 1;
            idWinner = getId(player1);
            printf("\n Partita finita: ha vinto il giocatore %d\n", idWinner);
        }
        else
        {
            turn++;
            round = setGameRound(round, turn);
        }
    }
    return;
}

Round newTurn(Round round)
{

    Player activePlayer;
    char activePlayerPlayground[TABLE_MAX][TABLE_MAX];
    char activePlayerHeatMap[TABLE_MAX][TABLE_MAX];

    int turn;
    char choice;
    int row;
    int column;
    char axis;
    int activePlayerLongShot;
    int activePlayerAirStrike;
    int activePlayerRadar;
    int error;

    activePlayer = getActivePlayer(round);
    getPlayground(activePlayer, activePlayerPlayground);
    getHeatMap(activePlayer, activePlayerHeatMap);

    printf("ECCO LA TUA ATTUALE MAPPA DI GIOCO\n");
    showMap(activePlayerPlayground);

    printf("ECCO LA TUA ATTUALE CONOSCIENZA DEL CAMPO AVVERSARIO\n");
    showMap(activePlayerHeatMap);

    activePlayerLongShot = getLongShots(activePlayer);
    activePlayerAirStrike = getAirstrike(activePlayer);
    activePlayerRadar = getRadar(activePlayer);
    turn = getGameRound(round);

    do
    {
        choice = nextMoveChoice();

        if (choice == 1)
        {
            row = rowChoice();
            column = columnChoice();
            round = hit(row, column, round);
        }
        else if (choice == 2)
        {
            if (activePlayerLongShot > 0)
            {
                row = rowChoice();
                column = columnChoice();
                round = longShot(row, column, round);
                activePlayer = setLongshots(activePlayer, (activePlayerLongShot - 1));
            }
            else
            {
                error = 1;
                printf("\nErrore: non hai colpi a largo raggio a disposizione\n");
            }
        }
        else if (choice == 3)
        {
            if (turn > 10)
            {
                if (activePlayerAirStrike > 0)
                {
                    axis = axisChoice();
                    if (axis == 'R')
                    {
                        row = rowChoice();
                        round = airStrikeRow(round, row);
                        activePlayer = setAirstrike(activePlayer, (activePlayerAirStrike - 1));
                    }
                    else
                    {
                        column = columnChoice();
                        round = airStrikeColumn(round, column);
                        activePlayer = setAirstrike(activePlayer, (activePlayerAirStrike - 1));
                    }
                }
                else
                {
                    error = 1;
                    printf("\nErrore: non hai il bombardamento aereo a disposizione\n");
                }
            }
            else
            {
                error = 1;
                printf("\n Errore: Sara' possibile utilizzare il bombardamento aereo tra %d\n", 11 - turn);
            }
        }
        else if (choice == 4)
        {
            if (activePlayerRadar > 0)
            {
                row = rowChoice();
                column = columnChoice();
                round = radar(round, row, column);
                activePlayer = setRadar(activePlayer, (activePlayerRadar - 1));
            }
            else
            {
                error = 1;
                printf("\nErrore: non hai il radar a disposizione\n");
            }
        }
        else if (choice == 5)
        {
            // salvataggio
            // torna al menù principale
        }
    } while (error == 1);

    printf("SCEGLI QUALE CELLA COLPIRE\n");

    return round;
}

char nextMoveChoice()
{
    char choice;
    choice = ' ';

    int error;

    do
    {
        error = 0;
        printf("Mosse: \n 1: colpo normale \n 2: colpo a largo raggio \n 3: bombardamento aereo \n 4: radar \n 5: esci\n Seleziona la tua mossa: ");
        choice = getchar();

        if (choice < '1' || choice > '5')
        {
            error = 1;
            printf("\n Errore \n");
        }

        fflush(stdin);
    } while (error == 1);

    return choice;
}

int rowChoice()
{
    int row;
    int error;

    row = 0;

    do
    {
        error = 0;
        printf("Inserire la riga da colpire: ");

        scanf("%d", &row);

        if (row < 1 || row > 16)
        {
            error = 1;
            printf("\n\nErrore\n\n"); // TODO: Da gestire meglio la stampa dell'errore
        }

        fflush(stdin);
    } while (error == 1);

    return row;
}

int columnChoice()
{
    char column;
    int error;
    int intColumn;

    column = ' ';

    do
    {
        error = 0;
        printf("Inserire la colonna da colpire: ");

        column = getchar();

        if (column < 'A' || column > 'P')
        {
            error = 1;
            printf("\n\nErrore\n\n"); // TODO: Da gestire meglio la stampa dell'errore
        }

        fflush(stdin);
    } while (error == 1);

    intColumn = getIntegerColumn(column);

    return intColumn;
}