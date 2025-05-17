#include <stdio.h>
#include "cse232editor.h"

node textbuffer[25];
int free_head = 0;
int inuse_head = -1;

int main() {
    edit("deneme.txt");

    insert(0, "line4");

    for(int i = inuse_head; i != -1; i = textbuffer[i].next) {
        printf("%d: %s\n", i, textbuffer[i].statement);
    }

    delete(5);


    printf("After:\n");
    for(int i = inuse_head; i != -1; i = textbuffer[i].next) {
        printf("%d: %s\n", i, textbuffer[i].statement);
    }

    // display();

    


    

    return 0;
}