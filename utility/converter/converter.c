
/**
 * @brief Trasforma una lettera minuscola in una lettera maiuscola. Se letter è una lettera
 * maiuscola, allora viene restituita senza modificarla, se invece letter è minuscola
 * viene trasformata in una lettera maiuscola.
 * 
 * @param letter Lettera da trasformare.
 * @return Lettera trasformata. 
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
 * @brief Ricava la lunghezza di una stringa.
 * 
 * @param str Stringa da calcolare la lunghezza.
 * @return Lunghezza di una stringa.
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
 * @brief Converte un numero naturale in una stringa, conservando il valore convertito
 * nel parametro buffer.
 * 
 * @param number Numero da convertire.
 * @param buffer Stringa che contiene il valore di number convertito.
 */
void numberToString(int number, char buffer[])
{
	int i;
	int last;
	
	i = 0;
	last = 1;

	if (number > 9)
	{
		i = 1;
		last = 2;
	}

	while (number > 0)
	{
		buffer[i] = (number % 10) + MIN_DIGIT; // Converto l'ultima cifra del numero in un carattere
		number = (int) number / 10; // Prendo le cifre successive
		i--;
	}
	
	buffer[last] = '\0';

	return;
}


/**
 * @brief Converte una stringa in un numero naturale, andando ad escludere quei caratteri che non fanno parte
 * del range ASCII delle cifre decimali. Se viene passata una stringa non valida, viene restituito il 
 * valore 0, altrimenti viene restituito il valore convertito.
 * 
 * @param str Stringa da convertire in un numero naturale.
 * @param len Lunghezza della stringa da convertire.
 * @return Numero convertito.
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
			number = (str[i] - MIN_DIGIT) + number * 10;
		}

		i++;
	}

	return number;
}	


/**
 * @brief Converte un carattere, associato ad una colonna, e restituisce
 * la posizione della colonna all'interno della tabella.
 * 
 * @param column Carattere da convertire.
 * @return Posizione della colonna all'interno della tabella.
 */
int getIntegerColumn(char column)
{
	int numericColumn;
	
	numericColumn = column - START_UPPERCASE_ASCII + 1;

	return numericColumn;
}


/**
 * @brief Converte la posizione di una colonna, e restituisce
 * il carattere associato ad essa nella tabella di gioco.
 * 
 * @param column Valore numerico da convertire.
 * @return Posizione della colonna convertita nel suo carattere associato.
 */
char getCharColumn(int column)
{
	char charColumn = ' ';
	charColumn = ' ';

	charColumn = column + START_UPPERCASE_ASCII - 1;

	return charColumn;
}