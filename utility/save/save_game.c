#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "./save_game.h"


/**
 * @brief Mostra gli slot di salvataggio del gioco
 */
void showGameSlots()
{
	int i = 1;
	DIR *d;
    struct dirent *dir;
    
    d = opendir(PATH_SAVE_SLOTS);
    
    if (d) 
    {
        printf("\n\n");

        while ((dir = readdir(d)) != NULL) 
        {
            if ( ( strcmp(dir->d_name,".") !=0)  && ( strcmp(dir->d_name,"..") !=0)  ) 
		    {
                printf("  %d. %s\n",i, dir->d_name);
                i++;
            }
        }
        closedir(d);
    }
    return;
}
