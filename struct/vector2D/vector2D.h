/**
 * La struttura Vector2D è un contenitore che racciunde le proprietà come
 * ascissa e ordinata, in modo tale da ottenere una rappresentazione più 
 * compatta delle coordinate all'interno della tabella di gioco.
 * 
 * All'intero della struttura troviamo i campi x e y che 
 * rappresentano, rispettivamente, le ascisse e le ordinate. 
 * 
 * Le ascisse sono le colonne della tabella e le ordinate sono le righe.
 */

#define FIRST_UPPERCASE_ASCII 65
#define FIRST_NUMBER_ASCII 48


typedef struct Vector2D {
    int x;
    int y;
} Vector2D;


Vector2D strToVector2D(char* coord);
Vector2D setX(Vector2D vector, char x);
Vector2D setY(Vector2D vector, char y);

int getX(Vector2D vector);
int getY(Vector2D vector);
// int isValidVector2D(Vector2D vector); TODO

void vector2DToStr(Vector2D vector, char* coord);





