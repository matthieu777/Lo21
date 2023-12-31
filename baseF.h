#ifndef __BASEF__H__
#define __BASEF__H__

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct baseF {
       char *texte;
       struct baseF *next;
}baseFaits;

typedef baseFaits *BF;


BF creerBaseF();
BF ajouterFait(BF b, char* text);
void afficherBaseF(BF b);
void libererBaseF(BF baseF);






#endif
