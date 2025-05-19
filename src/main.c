#include <stdio.h>
#include <string.h>
#include <curses.h>
#include "texteditor.h"

node textbuffer[25];
int free_head = 0;
int inuse_head = -1;

int main(int argc, char** argv) {
    if(argc <= 1) {
        printf("Not enough arguments!\n");
        return 1;
    }

    if(argc > 2) {
        printf("More than 1 arguments!\n");
        return 1;
    }

    edit(argv[1]);

    int ch;
	int currentline = 0;
	keypad(stdscr, TRUE);

    int i = 0;
    char buffer[40];
    buffer[0] = '\0';

	while(1){
		clear();

        display();
        mvprintw(25, 0, "Command: %s", buffer);
		mvprintw(currentline, 0, "%2d %s", currentline, textbuffer[currentline].statement);
        move(currentline, 3);
        
		refresh();
		ch = getch();
		
		if(ch == KEY_UP){
			if(currentline > 0) currentline--;

		} else if (ch == KEY_DOWN){
			if(currentline < 24) currentline++;

        } else if(ch == '\n') {
            switch(buffer[0]) {
            case 'I':
                if(insert(currentline, &buffer[2]))
                    mvprintw(26, 0, "Inserted %s at line %d", &buffer[2], currentline);
                push(&function_call_stack, INSERT, currentline, &buffer[2]);
                break;

            case 'D':
                if(delete(currentline))
                    mvprintw(26, 0, "Deleted line %d", currentline);
                push(&function_call_stack, DELETE, currentline, textbuffer[currentline].statement);
                break;

            case 'U':
                undo(); // Not working for now
                break;

            case 'R':
                redo(); // Not working for now
                break;

            case 'S':
                save(argv[1]);
                break;

            case 'Q':
                quit();
                break;

            default: 
                printw("Unknown command!");
                break;
            }
            
            refresh();
            getch();
            buffer[0] = '\0';
            i = 0;

        } else if(ch == KEY_BACKSPACE) {
            if(i > 0)
                buffer[--i] = '\0';

		} else {
            buffer[i++] = ch;
            buffer[i] = '\0';

        }
	}

    return 0;
}
