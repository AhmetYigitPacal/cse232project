#include <ncurses.h>
#include "texteditor.h"

void save(char* filename){
    clear();
    FILE *file=fopen(filename,"w+");
    if (file==NULL){
        printw("File couldn't be created");
        refresh();
        napms(5000);
        return;
    } else{
        int index=inuse_head;
        while(index!=-1){
                fprintf(file,"%s\n",textbuffer[index].statement);
                index=textbuffer[index].next;
        }
        fclose(file);
        printw("Successfully saved to %s\n", filename);
        refresh();
    }
}


