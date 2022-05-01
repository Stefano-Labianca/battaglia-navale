#ifndef _GLOBAL_CONSTANTS_H
#define _GLOBAL_CONSTANTS_H

#define LOWER_TO_UPPER 32
#define START_UPPERCASE_ASCII 65
#define START_LOWERCASE_ASCII 97
#define MAX_SHIP_AMOUNT 1
#define MAX_SHIP_SIZE 5 

enum TABLE_RANGE { TABLE_MIN = 1, TABLE_MAX = 16 };
enum ASCII_DIGIT_RANGE { MIN_DIGIT = 48, MAX_DIGIT = 57 };

enum COORDS_CONSTANTS {	
	SEPARATOR = '-', 
	COORD_SEPARETOR = '_', 
	MAX_COORD_LEN = 5, 
	MAX_ROW_LEN = 3, 
	MAX_COORDS_RANGE = 11 
};

enum PLAYER_CONSTANTS {
	SHIP_NUMB = 15,
	MAX_LONG_SHOT = 3,
	MAX_RADAR = 3,
	MAX_AIR_STRIKE = 1
};

enum MAP_SYMBOLS { 
	WATER = '~', 
	PLAYGROUND_HIT = 'X', 
	SUNK = '*',   
	UNKNOWN = '?', 
	HEAT_MAP_HIT = '!',
	HEAT_MAP_SUCCESSFUL_SCAN = '#' 
};

#endif /* _GLOBAL_CONSTANTS_H */