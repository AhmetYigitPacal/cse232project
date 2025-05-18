#include <stdio.h>
#include <string.h>
#include "cse232editor.h"

node textbuffer[25]; // 25 satırlık metin tamponu
int free_head = 0;   // Boş düğümlerin başı
int inuse_head = -1; // Kullanılan düğümlerin başı

int main(int argc, char** argv) {
    if(argc <= 1) {
        printf("Not enough arguments!\n");
        return 1;
    }

    if(argc > 2) {
        printf("More than 1 arguments!\n");
        return 1;
    }

    // Dosyayı aç ve içeriği yükle
    edit(argv[1]);

    int ch;
	int x = 0, y = 0;
	keypad(stdscr, TRUE);
	printw("Welcome to the text editor\n");
	refresh();
	getch();

    int i = 0;
    char buffer[40];
    buffer[0] = '\0';

	while(1){
		clear();
		mvprintw(y, x, "$");
		refresh();

		ch = getch();
		
		if(ch == KEY_UP){
			if(y > 0) y--;

		} else if (ch == KEY_DOWN){
			if(y < 24) y++;
            
		} else if (ch=='q') {
            break;

        } else if(ch == '\n') {
            buffer[i] = '\0';
            // printw("You inputted %s\n", buffer);
            
            switch(buffer[0]) {
                case 'I':
                    printw("Inserting %s at line %d", &buffer[2], y);
                    insert(y, &buffer[2]);
                    push(&function_call_stack, INSERT, y, &buffer[2]);
                    break;

                case 'D':
                    printw("Deleting line %d", y);
                    delete(y);
                    push(&function_call_stack, DELETE, y, &buffer[2]);
                    break;

                case 'U':
                    printw("Undoing");
                    undo();
                    break;

                case 'R':
                    printw("Redoing");
                    redo();
                    break;

                case 'P':
                    display();  
                    break;
                // case 'S':
                // case 'Q':
                default: 
                    printw("Unknown command!");
                    break;
            }
            
            refresh();
            getch();
            buffer[0] = '\0';
            i = 0;

		} else {
            buffer[i] = ch;
            i++;

        }
	}

	endwin();

    quit();

    return 0;
}
