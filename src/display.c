#include <string.h>
#include <curses.h>
#include "texteditor.h"

void display() {
    clear();

    bool inuse[25] = {false};

    int current = inuse_head;
    while(current != INVALID_INDEX) {
        inuse[current] = true;
        current = textbuffer[current].next;
    }

    
    for(int i = 0; i < 25; i++) {
        attron(COLOR_PAIR(1));
        
        printw("%2d ", i);

        attroff(COLOR_PAIR(1));

        if(inuse[i]) {
            printw("%s", textbuffer[i].statement);
        }
        printw("\n");
    }

    refresh();
    
}