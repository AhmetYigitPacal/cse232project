#include <stdlib.h>
#include <ncurses.h>
#include "texteditor.h"

void quit(){
    clear();
    printw("Press any button to exit\n");
    refresh();
    getch();
    endwin();
    exit(0);
}