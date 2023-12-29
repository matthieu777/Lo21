#ifndef __REGLES__H__
#define __REGLES__H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct proposition {
       char *texte;
       struct proposition *next;
}Proposition;

typedef Proposition *Premisse;

typedef char *Conclusion;

typedef struct Regle {
       Premisse premisse;
       Conclusion conclusion;
}regle;


regle creerRegle();
regle ajtPremisse(regle regled, char *text);
regle creerConclusion(regle regled, char* text);
bool apartPremisse(Premisse premise, char* text);
regle supProposition(regle regleCourante, char *text);
bool estvidePremisse(Premisse p);
char* tetePremisse(Premisse p);
char* conclRegle(regle r);

void afficherRegle(regle Regle);

#endif