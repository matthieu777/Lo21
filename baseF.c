#include "baseF.h"

//fonction qui creer une base vide
BF creerBaseF(){
    return NULL;
}

//fonction qui ajoute un fait a la base de faits donner
BF ajouterFait(BF b, char *text){
    BF nouveau = (BF)malloc(sizeof(baseFaits));
    
    nouveau->texte = (char*)malloc(strlen(text) + 1);
    strcpy(nouveau->texte, text);
    nouveau->next = NULL;

    
    if (b == NULL){
        return nouveau;
    } else {
        BF actuel = b;
        while (actuel->next != NULL){
            actuel = actuel->next;
        }

        actuel->next = nouveau;
        return b;
}
}

//fonction pour afficher la base de faits
void afficherBaseF(BF b) {
    printf("base de fait :\n");
    while (b != NULL) {
        printf("- %s\n", b->texte);
        b = b->next;
    }
}
    


