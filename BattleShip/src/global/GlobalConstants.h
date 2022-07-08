/**
 * Modulo GlobalCostants
 * DESCRIZIONE: Dichiarazione di tutte le costanti globali usate all'interno degli algoritmi
 * 
 */

#ifndef _GLOBAL_CONSTANTS_H
#define _GLOBAL_CONSTANTS_H

#define LOWER_TO_UPPER 32 // LOWER_TO_UPPER	- Conversione delle parole da minuscolo a maiuscolo o viceversa - Numero intero
#define START_UPPERCASE_ASCII 65 // START_UPPERCASE_ASCII - Prima lettera dell’alfabeto maiuscola in ASCII - Numero intero
#define START_LOWERCASE_ASCII 97 // START_LOWERCASE_ASCII -	Prima lettera dell’alfabeto minuscola in ASCII - Numero intero
#define MAX_SHIP_AMOUNT 15 // MAX_SHIP_AMOUNT - Numero massimo di navi in un playground - Numero intero
#define MAX_SHIP_SIZE 5 // MAX_SHIP_SIZE - Dimensione massima di una nave - Numero intero
#define MIN_SHIP_SIZE 1 // MIN_SHIP_SIZE - Dimensione minima di una nave - Numero intero
#define AIRSTRIKE_TURN 20 // AIRSTRIKE_TURN	- Turno dal quale si può iniziare ad utilizzare l’Airstrike - Numero intero
#define NUM_SAVE 5 // NUM_SAVE - posizione contenente il numero del salvataggio - Numero intero

enum TABLE_RANGE {
	TABLE_MIN = 1, // TABLE_MIN - Riga/Colonna minima - Numero intero
	TABLE_MAX = 16 // TABLE_MAX - Riga/Colonna massima - Numero intero
};

enum RANGE_ASCII_DIGIT {
	MIN_DIGIT = 48, // MIN_DIGIT - 0 in codice ASCII - Numero intero
	MAX_DIGIT = 57 // MAX_DIGIT - 9 in codice ASCII - Numero intero
};

enum RANGE_SAVE_SLOTS {
	FIRST_SLOT = 1, // FIRST_SLOT - Primo slot di salvataggio - Numero intero
	LAST_SLOT = 7 // LAST_SLOT - Ultimo slot di salvataggio - Numero intero
};

enum COORDS_CONSTANTS {	
	SEPARATOR = '-', // SEPARATOR - Separatore tra riga e colonna - Carattere
	COORD_SEPARATOR = '_', // COORD_SEPARATOR - Separatore di coordinate - Carattere
	MAX_COORD_LEN = 5, // MAX_COORD_LEN - Lunghezza massima di una coordinata - Numero intero
	MAX_ROW_LEN = 3, // MAX_ROW_LEN - Lunghezza massima della stringa contenente la riga - Numero intero
	MAX_COORDS_RANGE = 11, // MAX_COORDS_RANGE - Lunghezza massima di un range di coordinate - Numero intero
	START_ROW_COORD = 2 // START_ROW_COORD - Inizio della riga nelle coordinate - Numero intero
};

enum PLAYER_CONSTANTS {
	SHIP_NUMB = 15, // SHIP_NUMB - Numero massimo di navi - Numero intero
	MAX_LONG_SHOT = 3, //MAX_LONG_SHOT - Numero massimo di longShot a disposizione di un player - Numero intero
	MAX_RADAR = 3, // MAX_RADAR - Numero massimo di radar a disposizione di un player - Numero intero
	MAX_AIR_STRIKE = 1 // MAX_AIR_STRIKE - Numero massimo di airStrike a disposizione di un player - Numero intero
};

enum MAP_SYMBOLS { 
	WATER = '~', // WATER - Carattere che indica la presenza di acqua nel playground e nell’heatMap - Carattere
	PLAYGROUND_HIT = 'X', // PLAYGROUND_HIT - Carattere che indica una nave colpita nel playground - Carattere
	SUNK = '*', // SUNK - Carattere che indica la presenza una nave affondata nel playground e nell’heatMap - Carattere
	UNKNOWN = '?', // UNKNOWN - Carattere che indica le celle di cui non si hanno informazioni nell’heatMap - Carattere
	HEAT_MAP_HIT = '!', // HEAT_MAP_HIT - Carattere che indica una nave colpita nell’heatMap - Carattere
	HEAT_MAP_SUCCESSFUL_SCAN = '#' // HEAT_MAP_SUCCESSFUL_SCAN - Carattere che indica la presenza di una nave nell’heatMap a seguito di una scansione - Carattere
};

#endif /* _GLOBAL_CONSTANTS_H */
