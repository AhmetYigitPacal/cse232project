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
        // printw("%d\n", inuse[i]);
        printw("%2d ", i);
        if(inuse[i]) {
            printw("%s", textbuffer[i].statement);
        }
        printw("\n");
    }

    refresh();
}