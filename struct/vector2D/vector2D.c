#include "./vector2D.h"


Vector2D strToVector2D(char* coord)
{
    Vector2D vector;

    vector = setX(vector, coord[0]);
    vector = setY(vector, coord[1]);

    return vector;
}


Vector2D setX(Vector2D vector, char x)
{
    vector.x = x - FIRST_UPPERCASE_ASCII;

    return vector;
}


Vector2D setY(Vector2D vector, char y)
{
    vector.y = y - FIRST_UPPERCASE_ASCII;

    return vector;
}


int getX(Vector2D vector)
{
    int x = 0;
    x = vector.x + FIRST_UPPERCASE_ASCII;

    return x;
}


int getY(Vector2D vector)
{
    int y = 0;
    y = vector.y + FIRST_UPPERCASE_ASCII;

    return y;
}


void vector2DToStr(Vector2D vector, char* coord)
{
    coord[0] = getX(vector) + FIRST_UPPERCASE_ASCII;
    coord[1] = getY(vector) + FIRST_UPPERCASE_ASCII;

    return;
}

// TODO 
// int isValidVector2D(Vector2D vector)
// {
//     return 0;
// }


