#include <ncurses.h>
#include "texteditor.h"

bool save(char* filename){
    FILE *file=fopen(filename,"w+");
    if (file == NULL){
        return false;
    } 

    int cur = inuse_head;
    while(cur != INVALID_INDEX) {
        fprintf(file, "%s\n",textbuffer[cur].statement);
        cur = textbuffer[cur].next;
    }

    fclose(file);
    return true;
}


