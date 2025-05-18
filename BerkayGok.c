#include <stdlib.h>
#include <ncurses.h>
#include "cse232editor.h"

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
                printw("File is created");
                refresh();
                napms(2000);
        }
}

void quit(){
        clear();
        printw("Exitting from text editor.");
        refresh();
        napms(1000);
        endwin();
}
