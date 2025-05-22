#include <ncurses.h>
#include "texteditor.h"

bool save(char* filename){
    FILE *file=fopen(filename,"w+");
    if (file == NULL){
        return false;
    } 

    for (int i=0;i<25;i++){
        if (textbuffer[i].statement[0]!='\0'){
            fprintf(file, "%s\n",textbuffer[i].statement);
        }
    }

    fclose(file);
    return true;
}


