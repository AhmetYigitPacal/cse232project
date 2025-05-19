#include "texteditor.h"

bool delete(int index) {
    if(inuse_head == INVALID_INDEX) {
        printw("No line to delete\n");
        return false;
    }

    // If the inuse head is index
    if(inuse_head == index) {
        // Remove index from inuse
        inuse_head = textbuffer[index].next;
        if(inuse_head != INVALID_INDEX)
            textbuffer[inuse_head].prev = INVALID_INDEX;

        // Add index to free
        if(free_head!= INVALID_INDEX)
            textbuffer[free_head].prev = index;
        textbuffer[index].next = free_head;
        textbuffer[index].prev = INVALID_INDEX;
        free_head = index;

        // Delete the text
        textbuffer[index].statement[0] = '\0';

        return true;
    }

    // Check if the index is inuse
    int current = inuse_head;
    while(current != INVALID_INDEX) {
        // If next of current is the index
        if(textbuffer[current].next == index) {
            int nextindex = textbuffer[index].next;
            int previndex = current;

            // Remove index from inuse
            textbuffer[previndex].next = nextindex;
            if(nextindex != INVALID_INDEX)
                textbuffer[nextindex].prev = previndex;

            // Add index to free
            if(free_head != INVALID_INDEX)
                textbuffer[free_head].prev = index;
            textbuffer[index].next = free_head;
            textbuffer[index].prev = INVALID_INDEX;
            free_head = index;

            // Delete the text
            textbuffer[index].statement[0] = '\0';

            return true;
        }

        current = textbuffer[current].next;
    }

    printw("The line %d is not in use", index);
    return false;
}
