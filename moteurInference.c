#include "moteurInference.h"

 bool apartPremisseF(Premisse premise, BF baseF) {

    if (estvidePremisse(premise)) {
  
        return true;  //vrai si la premisse est vide
    } else {

        BF faitActuel = baseF;
        //on cherche la proposition dans la base de faits
        while (faitActuel != NULL) {    

            if (strcmp(premise->texte, faitActuel->texte) == 0) {   //si l'elemente de la base de fait corresponds a la premisse 
                return apartPremisseF(premise->next, baseF); //on cherche avec la premisse suivante
            }
            faitActuel = faitActuel->next; //on cherche avec un autre fait
        }

        return false;
        
    }   
}


//fonction pour enlenver les espaces avant et apres
char* supp(char* str) {
    int start = 0, end = strlen(str) - 1;

    while (start <= end && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')) { //on cherche le 1er vrai caractère
        start++;
    }

    while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n')) { //on cherche le dernier element qui n'est pas un espace
        end--;
    }


    char* result = (char*)malloc((end - start + 2) * sizeof(char)); //on copie la chaine sans les espaces non voulue
    strncpy(result, &str[start], end - start + 1);
    result[end - start + 1] = '\0';

    return result;
}




void moteurInf(BC baseC, BF baseF) {

    

    if (baseC == NULL) {             
        printf("Erreur : la base de connaissances est vide\n"); //si la base de connaissance est vide
        return;
    }

    if (baseF == NULL) {
        printf("Erreur : la base de faits est vide\n"); //si la base de faits est vide
        return;
    }

    BC regleActuelle = baseC;
    int conclusionTrouvee = 0; //variable pour savoir si on a trouver un resultat
    

    while (regleActuelle != NULL) { //parcours de la base de connaissance
        
        Premisse premisseActuelle = regleActuelle->Bcregle.premisse; //recuperation de la premisse de la regle
        int premisseTrouver = 1;
        while (premisseActuelle != NULL) { //pacours de la premisse
            if (!apartPremisseF(premisseActuelle, baseF)) {  //si tout les element de la premisse ne sont pas dans la base de faits
                premisseTrouver = 0; 
                break;
            }
            premisseActuelle = premisseActuelle->next;
        }   
        
        if (premisseTrouver) {                //si tout les elements de la premisse sont dans la base de faits on affiche la conclusion de la regle
           char* conc = conclRegle(regleActuelle->Bcregle);
           conc = supp(conc);   //on enleve les espaces non dessirable

            baseF = ajouterFait(baseF,conc); //ajoute la conclussion a la base de fait
            printf("\nconclusion trouver  : %s\n",conc);
            
            

            
            conclusionTrouvee = 1;
        }
        regleActuelle = regleActuelle->next; //on passe a la regle suivante
    }

    if (!conclusionTrouvee) {       //si on a rien trouver
        printf("Aucune conclusion n'a pu être trouvée\n");
    } 

    

} 