#ifndef TEXTEDITOR_H_
#define TEXTEDITOR_H_

#include <curses.h>

#include "undoredo.h"

#include "ahmetyigit.h"
#include "berkay.h"
#include "emin.h"
#include "omeratilla.h"
#include "omersabri.h"
#include "eceoyku.h"

#define INVALID_INDEX -1 

typedef struct node{
    int prev;
    char statement[40];
    int next;
} node;

extern node textbuffer[25];
extern int free_head; 
extern int inuse_head; 

#endif // TEXTEDITOR_H_