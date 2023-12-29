#include "moteurInference.h"

void moteurInf(BC baseC, BF baseF) {

    if(baseC==NULL){
        printf("=> erreur la base de connaissance est vide");
        return;
    }
    if(baseF==NULL){
        printf("=> erreur la base de faits est vide");
        return;
    }

    BC regleActuel = baseC;
    int concTrouve = 0; // variable pour savoir si une conclusion a été trouvée

    while (regleActuel != NULL) {
        Premisse premisseActuel = regleActuel->Bcregle.premisse;
        int premisseSatisfaite = 1;

        // on cherche d'abord dans la premisse
        while (premisseActuel != NULL) {
            int faitTrouve = 0;
            BF faitActuel = baseF;

            // on cherche dans les faits
            while (faitActuel != NULL) {
                if (strcmp(premisseActuel->texte, faitActuel->texte) == 0) { //si on trouve une premisse egale
                    faitTrouve = 1;
                    break;
                }
                faitActuel = faitActuel->next;  //on passe au fait suivant
            }

            if (!faitTrouve) {  //si le fait n'est pas present
                premisseSatisfaite = 0;
                break;
            }

            premisseActuel = premisseActuel->next; //on passe a la prochaine premisse
        }

        if (premisseSatisfaite) {
            printf("%s ", regleActuel->Bcregle.conclusion);     //on affiche la conclussion trouver si il y'en a une
            concTrouve = 1;
        }

        regleActuel = regleActuel->next;    //on examine la prochaine regle
    }

    if (!concTrouve) {   //si rien n'a été trouver dans toutes les regles
        printf("Aucune conclusion n'a pu etre trouver");
    }
}