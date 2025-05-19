#include <stdlib.h>
#include <ncurses.h>
#include "texteditor.h"

void quit(){
    clear();
    endwin();
    exit(0);
}