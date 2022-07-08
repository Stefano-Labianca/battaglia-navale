#include <stdio.h>
#include <stdlib.h>

#include "./converter.h"
#include "../../global/GlobalConstants.h"


/**
 * Funzione toUpperCase
 * DESCRIZIONE: Trasforma una lettera minuscola in una lettera maiuscola. Se letter e' una lettera
 * maiuscola, allora viene restituita senza modificarla, se invece letter e' minuscola
 * viene trasformata in una lettera maiuscola.
 * 
 * INPUT
 * letter - Lettera da trasformare - carattere - Compresa tra 'a' e 'z'
 * LOWER_TO_UPPER - Conversione delle parole da minuscolo a maiuscolo o viceversa - Numero intero - 32
 * 
 * OUTPUT
 * letter - Lettera trasformata - carattere - Compresa tra 'A' e 'Z'
 *  
 */
char toUpperCase(char letter)
{
	if (letter >= 'a' && letter <= 'z')
	{
		letter -= LOWER_TO_UPPER;
	}

	return letter;
} 


/**
 * Funzione getLength
 * DESCRIZIONE: Ricava la lunghezza di una stringa.
 * 
 * INPUT
 * str - Stringa da calcolare la lunghezza - Stringa - \
 * 
 * OUTPUT
 * i - Lunghezza della stringa - intero - i >= 0
 *
 */
int getLength(char str[])
{
	int i;
	
	i = 0;
	
	while (str[i] != '\0')
	{
		i++;
	}
	
	return i;
}


/**
 * Funzione numberToString
 * DESCRIZIONE: Converte un numero naturale in una stringa, conservando il valore convertito
 * nel parametro buffer.
 * 
 * INPUT
 * number - Numero da convertire - intero - \
 * MIN_DIGIT - 0 in codice ASCII - Numero intero - 48
 * START_ROW_COORD - Inizio della riga nelle coordinate - Numero intero - 3
 * 
 * OUTPUT
 * buffer - Stringa che contiene il valore di number - Stringa - \
 * 
 * LAVORO
 * i - Posizione della cifra numerica all’interno della stringa - Numero intero - i > 0
 * last - Posizione del carattere di ENDSTRING - intero - last > 0
 */
void numberToString(int number, char buffer[])
{
	int i;
	int last;
	
	i = 0;
	last = START_ROW_COORD - 1;

	if (number > 9) 
	{
		i =  START_ROW_COORD - 1;
		last =  START_ROW_COORD;
	}
	// Se il numero e' compreso tra 1 e 9 allora la cifra viene inserita nel primo elemento di buffer (i)
	// e il carattere di ENDSTRING nel secondo elemento (last)
	// Se il numero e' compreso tra 10 e 16 allora la prima cifra viene inserita nella seconda posizione di buffer (i)
	// e il carattere di ENDSTRING nella terza posizione (last)

	while (number > 0)
	{
		// % = Funzione remainder
		buffer[i] = (number % 10) + MIN_DIGIT; // Converto l'ultima cifra del numero in un carattere
		number = (int) number / 10; // Prendo le cifre successive

		// Inserisco prima l'unita', ci spostiamo poi indietro per inserire la decina (nel caso in cui il numero e' maggiore di 9)
		i--;
	}
	
	buffer[last] = '\0';

	return;
}


/**
 * Funzione stringToNumber
 * DESCRIZIONE: Converte una stringa in un numero naturale, andando ad escludere quei caratteri che non fanno parte
 * del range ASCII delle cifre decimali. Se viene passata una stringa non valida, viene restituito il 
 * valore 0, altrimenti viene restituito il valore convertito.
 * 
 * INPUT
 * str - Stringa da convertire in un numero intero - Stringa - \
 * len - Lunghezza della stringa da convertire - Intero - \
 * MIN_DIGIT - 0 in codice ASCII - Numero intero - 48
 * MAX_DIGIT - 9 in codice ASCII - Numero intero - 57
 * 
 * OUTPUT
 * number - Numero convertito - intero - \
 * 
 * LAVORO
 * i - Indice di scorrimento della stringa - intero - i > 0
 */
int stringToNumber(char str[], int len)
{
	int number;
	int i;
	
	i = 0;
	number = 0;

	while (i < len)
	{
		if (str[i] >= MIN_DIGIT && str[i] <= MAX_DIGIT)
		{
			/**
			 * Converto un carattere in un numero e, una volta convertito, lo moltiplico 
			 * con un valore pari alla sua base (= 10) e alla sua posizione.
			 */
			number = (str[i] - MIN_DIGIT) + number * 10; 
		}

		i++;
	}

	return number;
}	


/**
 * Funzione getIntegerColumn
 * DESCRIZIONE: Converte un carattere, associato ad una colonna, e restituisce
 * la posizione della colonna all'interno della tabella.
 * 
 * INPUT
 * column - Carattere da convertire - Carattere - Contiene un valore tra 'A' e 'P'
 * START_UPPERCASE_ASCII - Prima lettera dell'alfabeto maiuscola in ASCII - Numero intero - 65
 * 
 * OUTPUT
 * numericColumn - Valore di column tradotto in numero - Intero - column >= TABLE_MIN AND column <= TABLE_MAX
 */
int getIntegerColumn(char column)
{
	int numericColumn;
	
	numericColumn = column - START_UPPERCASE_ASCII + 1;

	return numericColumn;
}


/**
 * Funzione getCharColumn
 * DESCRIZIONE: Converte la posizione di una colonna, e restituisce
 * il carattere associato ad essa nella tabella di gioco.
 * 
 * INPUT
 * column - Carattere da convertire - Intero - column >= TABLE_MIN AND column <= TABLE_MAX
 * START_UPPERCASE_ASCII - Prima lettera dell'alfabeto maiuscola in ASCII - Numero intero - 65
 * 
 * OUTPUT
 * charColumn - Posizione della colonna convertita nel suo carattere associato - Carattere - Compreso tra 'A' e 'P'
 */
char getCharColumn(int column)
{
	char charColumn;
	charColumn = ' ';

	charColumn = column + START_UPPERCASE_ASCII - 1;

	return charColumn;
}
