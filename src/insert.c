#include <string.h>
#include <curses.h>
#include "texteditor.h"

bool insert(int index, char* text) {
    if(free_head == INVALID_INDEX) {
        return false;
    }

    // If the free head is the index
    if(free_head == index) {
        // Remove index from free
        free_head = textbuffer[index].next;
        if(free_head != INVALID_INDEX)
            textbuffer[free_head].prev = INVALID_INDEX;

        // Add index to inuse
        if(inuse_head != INVALID_INDEX)
            textbuffer[inuse_head].prev = index;
        textbuffer[index].next = inuse_head;
        textbuffer[index].prev = INVALID_INDEX;
        inuse_head = index;

        // Add the text
        strncpy(textbuffer[index].statement, text, 39);
        textbuffer[index].statement[39] = '\0';

        return true;
    }

    // Check if the index is in free
    int current = free_head;
    while(current != INVALID_INDEX) {
        // If next of current is the index
        if(textbuffer[current].next == index) {
            int nextindex = textbuffer[index].next;
            int previndex = current;

            // Remove index from free
            textbuffer[previndex].next = nextindex;
            if(nextindex != INVALID_INDEX)
                textbuffer[nextindex].prev = previndex;

            // Add index to inuse
            if(inuse_head != INVALID_INDEX)
                textbuffer[inuse_head].prev = index;
            textbuffer[index].next = inuse_head;
            textbuffer[index].prev = INVALID_INDEX;
            inuse_head = index;

            // Add the text
            strncpy(textbuffer[index].statement, text, 39);
            textbuffer[index].statement[39] = '\0';

            return true;
        }

        current = textbuffer[current].next;
    }


    // Replace the text
    strncpy(textbuffer[index].statement, text, 39);
    textbuffer[index].statement[39] = '\0';
    return true;
}
