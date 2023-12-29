#ifndef __BASEC__H__
#define __BASEC__H__

#include "regles.h"

typedef struct baseC{
  regle  Bcregle;
  struct baseC *next;
} baseConnaissance;

typedef baseConnaissance *BC;




BC creerBaseC();
BC ajouterRegleC(BC base, regle r);
regle teteBaseC(BC b);

void creerFichierBase(const char *nom);
void supprimerFichierBase(const char *nom);
void afficherBaseConnaissance(BC base);
void sauvegarderBaseConnaissances(BC baseC, const char *nom);
BC chargerBaseConnaissances(const char *nom);
BC supPropositionBaseC(BC baseC, char *text) ;












#endif
