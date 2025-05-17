#include <string.h>
#include "cse232editor.h"
#include <ncurses.h>
#include <stdio.h>

void insert(int line, char *stat)
{
    // node textbuffer[25]; // 25 satırlık editor buffer'i (her eleman bir node)
    // int free_head = 0;   // Free list'in başını gösteren index (boş düğümlerin bağlı listesi)
    // int inuse_head = -1; // Kullanılan bağlı listenin (aktif satırlar) başını gösteren index

    if (free_head == -1)
    {
        clear();
        printw("Text buffer is full!\n");
        refresh();
        getch();
        return;
    }

    int new_node = free_head;
    free_head = textbuffer[free_head].next;

    strncpy(textbuffer[new_node].statement, stat, 39);
    textbuffer[new_node].statement[39] = '\0';
    textbuffer[new_node].prev = -1;
    textbuffer[new_node].next = -1;

    if (inuse_head == -1 || line == 0)
    {
        textbuffer[new_node].next = inuse_head;
        if (inuse_head != -1)
            textbuffer[inuse_head].prev = new_node;
        inuse_head = new_node;
        return;
    }

    int curr = inuse_head;
    for (int i = 0; (i < line - 1) && (textbuffer[curr].next != -1); i++)
    {
        curr = textbuffer[curr].next;
    }

    int next = textbuffer[curr].next;
    textbuffer[curr].next = new_node;
    textbuffer[new_node].prev = curr;

    if (next != -1)
    {
        textbuffer[new_node].next = next;
        textbuffer[next].prev = new_node;
    }
}

void display()
{
    // node textbuffer[25]; // 25 satırlık editor buffer'i (her eleman bir node)
    free_head = 0;   // Free list'in başını gösteren index (boş düğümlerin bağlı listesi)
    inuse_head = -1; // Kullanılan bağlı listenin (aktif satırlar) başını gösteren index
    clear();
    int curr = inuse_head;
    while (curr != -1)
    {
        printw("%s\n", textbuffer[curr].statement);
        curr = textbuffer[curr].next;
    }
    refresh();
    move(0, 0);
    getch();
}

// int main()
// {
//     char *stat;
//     display();
//     insert(1, stat);
// }
