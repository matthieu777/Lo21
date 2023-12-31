#include "regles.h"




//Créer une règle vide
regle creerRegle(){
    regle creer;
    creer.premisse = NULL; 
    creer.conclusion = NULL;
    return creer;
};

//Ajouter une proposition à la prémisse d’une règle, l’ajout se fait en queue
regle ajtPremisse(regle regled, char *text){
    Premisse actuel = regled.premisse;

    
    // si premisse est null
     if (actuel == NULL) {
        actuel = (Premisse)malloc(sizeof(Proposition));
        actuel->texte = (char*)malloc(strlen(text) + 1);
        strcpy(actuel->texte, text);
        actuel->next = NULL;
        regled.premisse = actuel;
        return regled;
    }
    
    while (actuel->next != NULL) {
        actuel = actuel->next;
    }

    actuel->next = (Premisse)malloc(sizeof(Proposition));
    actuel = actuel->next;
    actuel->texte = (char*)malloc(strlen(text) + 1);    
    strcpy(actuel->texte, text);
    actuel->next = NULL;

    return regled; 
}


//Créer la conclusion d’une règle
regle creerConclusion(regle regled, char* text){
    if(estvidePremisse(regled.premisse)) {
        printf("la premisse est vide");
    }
    else {
        regled.conclusion = (char *)malloc(strlen(text)+1);
        strcpy(regled.conclusion, text);
    }
    return regled;
}





//Tester si une proposition appartient à la prémisse d’une règle, de manière récursive
bool apartPremisse(Premisse premise, char* text){
     if(estvidePremisse(premise)){
        return false;
    }
    else{
        if(strcmp(premise->texte, text) == 0){
            return true;
        }
        else{
            return apartPremisse(premise->next, text);
        }
    }
}




//Supprimer une proposition de la prémisse d’une règle
regle supProposition(regle regleCourante, char *text) {
    
    if (estvidePremisse(regleCourante.premisse)) {
        printf("la premisse est vide");     //si la liste est vide on a rien a supprimer
        return regleCourante;
    }
    if(apartPremisse(regleCourante.premisse,text)) {
    
    if (strcmp(regleCourante.premisse->texte, text) == 0) { //si c'est le 1er elem
        Premisse temp = regleCourante.premisse;
        regleCourante.premisse = regleCourante.premisse->next;
        free(temp->texte);
        free(temp);
        return regleCourante;
    }

    Premisse actuel = regleCourante.premisse;                       //cas general
    while (actuel->next != NULL && strcmp(actuel->next->texte, text) != 0) {
        actuel = actuel->next;
    }

    //si on trouve l'ellement on supp
    if (actuel->next != NULL) {
        Premisse temp = actuel->next;
        actuel->next = actuel->next->next;
        free(temp->texte);
        free(temp);
    }
 
    } else {
        printf("la proposition donner n'existe pas dans la premisse");
    }
   

    return regleCourante;
}


//Tester si la prémisse d’une règle est vide
bool estvidePremisse(Premisse p){
    if (p == NULL){
        return true;
    } else {
        return false;
    }
};


//Accéder à la proposition se trouvant en tête d’une prémisse 
char* tetePremisse(Premisse p){
    if(estvidePremisse(p)){
        return "la premisse est vide";
    }
    else {
        return p->texte;
    }
}

//Accéder à la conclusion d’une règle
char* conclRegle(regle r){
    if (r.conclusion == NULL){
        return "la conclusion est vide";
    }
    return r.conclusion;
}



//------------------------------------


//fonction pour afficher les regles
void afficherRegle(regle Regle) {
    printf("Premisse:\n");

    
    Premisse actuel = Regle.premisse;
    while (actuel != NULL) {    //on parcours les proposition jusqu'a qu'il y'en ai plus
        printf("- %s\n", actuel->texte);    //on affiche le texte de la proposition
        actuel = actuel->next;  //on passe a la prochaine proposition
    }

    printf("Conclusion: \n %s \n", Regle.conclusion);   //on affiche la conclusion
}






void libererRegle(regle Regle) {
    
    Premisse actuel = Regle.premisse;
    while (actuel != NULL) {
        Premisse temp = actuel;
        actuel = actuel->next;
        free(temp->texte);
        free(temp);
    }

    if (Regle.conclusion != NULL) {
        free(Regle.conclusion);
    }
}