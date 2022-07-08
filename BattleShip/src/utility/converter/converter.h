/**
 * Modulo Converter
 * DESCRIZIONE: Funzioni per conversioni di dati da un tipo all'altro e per utility di vario genere.
 *
 */
#ifndef _CONVERTER_H
#define _CONVERTER_H

#include "../../global/GlobalConstants.h"


char toUpperCase(char letter);
int getLength(char str[]);
void numberToString(int number, char buffer[]);
int stringToNumber(char str[], int len);
char getCharColumn(int column);
int getIntegerColumn(char column);

#endif /* _CONVERTER_H */
