#include "baseC.h"


//creer une base de connaissance null
BC creerBaseC(){
    return NULL;    
}  

//fonction d'ajout de regle a la base de connaissance
BC ajouterRegleC(BC base, regle r){
    BC nouvelle = (BC)malloc(sizeof(baseConnaissance));

//copie de la nouvelle regle dans la base
    nouvelle->Bcregle.premisse = r.premisse;
    nouvelle->Bcregle.conclusion = r.conclusion;    
    nouvelle->next = NULL;

    
    if (base == NULL){  //si la base est vide on peut renvoyer la nouvelle base tels quels
        return nouvelle;
    } else {        //sinon on mets la nouvelle regle a la fin
        BC actuel = base;
        while (actuel->next != NULL){   //on cherche le dernière elements
            actuel = actuel->next;
        }

        actuel->next = nouvelle;    //on mets a la fin
        return base;
}
}

//fonction qui donne la regle en tete de la base de connaissance
regle teteBaseC(BC b){
    return b->Bcregle; 
}




//fonction en plus
//---------------------------------------


//fonction pour afficher la base de connaissance
void afficherBaseConnaissance(BC base) {
    BC actuel = base;

    while (actuel != NULL) {
        printf("Prémisse: ");                   //affichage de la premisse :
        Premisse premisseCourante = actuel->Bcregle.premisse;
        while (premisseCourante != NULL) {
            if (premisseCourante->texte != NULL) {
                printf("%s ", premisseCourante->texte);
            }
            premisseCourante = premisseCourante->next; //on passe a la prochaine premisse
        }
        printf("\n");

        if (actuel->Bcregle.conclusion != NULL) {        //affichage de la conclusion
            printf("Conclusion: %s\n", actuel->Bcregle.conclusion);
        } else {
            printf("erreur pas de conclusion");
        }

        actuel = actuel->next; // on passe a la prochaine regle

        printf("\n");
    }
}


//fonction pour creer un fichier/base
void creerFichierBase(const char *nom) {
    FILE *fichier;
    int s = 1; //bool pour renvoyer un message su la base a bien été creer
    fichier = fopen(nom, "w"); //ouverture du fichier

    if (fichier == NULL) {      //si on parviens pas creer(ou ouvrir) le fichier
        printf("impossible de creer le fichier");
        s = 0;
    }

    fclose(fichier); //on referme le fichier

    if (s == 1 ){
        printf("La base a ete creer\n");
    }
}

//fonction pour supprimer un fichier/base donné en pramètre
void supprimerFichierBase(const char *nom) {
    if (remove(nom) == 0) { //supression du fichier avec remove
        printf("la base à bien été supprimer");
    } else {
        printf("=> erreur la base n'a pas pu etre supprimer"); //si ca la supression na pas marcher
    }
}

//fonction pour sauvgarder dans un fichier (donner) une base de connaissance (donner)
void sauvegarderBaseConnaissances(BC baseC, const char *nom) {
    FILE *fichier = fopen(nom, "w"); //ouverture en écriture du fichier

    if (fichier == NULL) {
        printf("echec de l'ouverture");
        return;
    }

    BC regleActuel = baseC; //pointe sur la regle en tete

    while (regleActuel != NULL) {       //on recommance tant qu'il y'a des regle 
        
        Premisse premisseActuel = regleActuel->Bcregle.premisse; //pointe sur la proposition en tete
        
        while (premisseActuel != NULL) { //on recommance tant qu'il y'a des proposition dans la premisse
            fprintf(fichier, "%s  ", premisseActuel->texte); //on écrit la premisse dans le fichier
            premisseActuel = premisseActuel->next;  //on passe a la prochaine premisse
        }

        fprintf(fichier, " => %s\n", regleActuel->Bcregle.conclusion); //on ecrie dans la conclusion dans le fichier avec une fleche pour la forme

        regleActuel = regleActuel->next;    //on passe a la prochaine regle
    }

    fclose(fichier);  //fermeture du fichier
}




BC chargerBaseConnaissances(const char *nom) {
    FILE *fichier = fopen(nom, "r"); //on ouvre le fichier en lecture

    if (fichier == NULL) {
        printf("\n=> Erreur lors de l'ouverutre de la base, \nTester avec une autre base\n");    //si on parvient pas à ouvrir le fichier
        return NULL;
    }

    BC baseConnaissances = creerBaseC();    //on creer un base dans la quelle on place les regle
    BC dernierElement = NULL;

    char ligne[256];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {  //lecture ligne par ligne
        
        char *premisseL = strtok(ligne, "=>");        //on divise la ligne en 2 partie, la premisse et la conclusion
        char *conclusionL = strtok(NULL, "=>");

        if (premisseL != NULL && conclusionL != NULL) { //si la premisse et la conclusion n'est pas vide
            
            BC nouvelElement = (BC)malloc(sizeof(baseConnaissance));

            
            char *prop = strtok(premisseL, " \n");  //on recupere les propo delimiter par " "
            while (prop != NULL) {
                Premisse nouvellePremisse = (Premisse)malloc(sizeof(Proposition));
                nouvellePremisse->texte = strdup(prop); //copie du texte dans la base de donner 
                nouvellePremisse->next = NULL;  //le suivant est initialiser a null

                if (nouvelElement->Bcregle.premisse == NULL) {  //on ajoute au debut si la regle est nul
                    nouvelElement->Bcregle.premisse = nouvellePremisse;
                } else {
                    Premisse dernierePremisse = nouvelElement->Bcregle.premisse;
                    while (dernierePremisse->next != NULL) {        //sinon on ajoute a la fin
                        dernierePremisse = dernierePremisse->next;
                    }
                    dernierePremisse->next = nouvellePremisse;
                }

                prop = strtok(NULL, " \n"); //on passe a la pochaine proposition
            }

            nouvelElement->Bcregle.conclusion = strdup(conclusionL);    //copie de la conclusion

            
            nouvelElement->next = NULL;     //ajout de la regle / si elle est vide on mets au debut 
            if (baseConnaissances == NULL) {
                baseConnaissances = nouvelElement;
                dernierElement = nouvelElement;
            } else {    //sinon on ajoute a la fin
                dernierElement->next = nouvelElement;
                dernierElement = nouvelElement;
            }
        }
    }

    fclose(fichier);    //on ferme le fichier

    return baseConnaissances;
}

//fonction qui suprimme dans toutes les regles un proposition
BC supPropositionBaseC(BC baseC, char *text) {
    BC regleActuel = baseC;

    while (regleActuel != NULL) {
        
        regleActuel->Bcregle = supProposition(regleActuel->Bcregle, text);  //supression avec un fonction definie dans regle.c

        regleActuel = regleActuel->next;    //on passe a la prochaine regle
    }

    return baseC;
}


void libererBC(BC baseC) {
    BC temp;
    while (baseC != NULL) {
        temp = baseC;
        baseC = baseC->next;
        free(temp);
    }
}