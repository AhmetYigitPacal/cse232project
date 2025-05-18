
#include <string.h>
#include "cse232editor.h"

void insert(int index, char* text) {
    if (free_head == -1) {
        printw("No space left in buffer.\n");
        return;
    }

    int new_node = free_head;
    free_head = textbuffer[free_head].next;

    strncpy(textbuffer[new_node].statement, text, 39);
    textbuffer[new_node].statement[39] = '\0';
    textbuffer[new_node].prev = -1;
    textbuffer[new_node].next = -1;

    if (inuse_head == -1 || index == 0) {
        // Başa ekle
        textbuffer[new_node].next = inuse_head;
        if (inuse_head != -1)
            textbuffer[inuse_head].prev = new_node;
        inuse_head = new_node;
    } else {
        // Ortaya veya sona ekle
        int current = inuse_head;
        int count = 0;
        while (count < index - 1 && textbuffer[current].next != -1) {
            current = textbuffer[current].next;
            count++;
        }

        int next_node = textbuffer[current].next;
        textbuffer[current].next = new_node;
        textbuffer[new_node].prev = current;
        textbuffer[new_node].next = next_node;

        if (next_node != -1)
            textbuffer[next_node].prev = new_node;
    }

    push(&function_call_stack, INSERT, new_node, "");
}


void display() {
    clear();
    int idx = inuse_head;
    int line_no = 0;
    while (idx != -1) {
        printw("%d: %s\n", line_no, textbuffer[idx].statement);
        idx = textbuffer[idx].next;
        line_no++;
    }
    refresh();
    getch(); // Gösterim için beklet
}
