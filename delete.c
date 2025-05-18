#include "cse232editor.h"

#define INVALID_INDEX -1 

void delete(int index) {
    // Check if the index is valid
    if(index < 0 || index >= 25) {
        printw("Invalid index\n");
        return;
    }

    // Check if the line is inuse
    if(index == inuse_head) {
        inuse_head = textbuffer[inuse_head].next;
        return;
    }
    
    int current = inuse_head;

    while(textbuffer[current].next != INVALID_INDEX) {
        // If the index is inuse
        if(textbuffer[current].next == index) {
		int next_index = textbuffer[index].next;

        // Remove line from inuse
        textbuffer[current].next = next_index;

 		if (next_index != -1)
            textbuffer[next_index].prev = current;

            // Remove prev connection from deleted node
            textbuffer[index].prev = INVALID_INDEX;

            // Add index to end of the free
            textbuffer[free_head].prev = index;
            textbuffer[index].next = free_head;
            free_head = index;

            return;
        }

        current = textbuffer[current].next;
    }
}
