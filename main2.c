#include "regles.h"
#include "baseC.h"
#include "baseF.h"
#include "moteurInference.h"

int main(){
    
    printf("\n\n test de la creation de regle :  \n");
    regle Regle1 = creerRegle();

    Regle1 = ajtPremisse(Regle1,"premisse1");
    Regle1 = ajtPremisse(Regle1,"premisse2");
    Regle1 = ajtPremisse(Regle1,"premisse3");
    Regle1 = creerConclusion(Regle1, "c1");

    printf("Voici ma Regle1 :\n\n");
    afficherRegle(Regle1);

    printf("\n\n test de la fonction appart premisse :  \n");
    printf("remisse1 est dans la premisse la regle1 ? %s \n", apartPremisse(Regle1.premisse,"premisse1") ? "Oui" : "Non");
    printf("premisse25 est dans la premisse la regle1 ? %s \n", apartPremisse(Regle1.premisse,"premisse25") ? "Oui" : "Non");


    printf("\n\n test de la fonction supp proposition:  \n");
    Regle1 = supProposition(Regle1 ,"premisse1");
    printf("Voici ma Regle1 apres suppression :\n\n");
    afficherRegle(Regle1);

    printf("\n\n test de la fonction estvidepremisse d'une regle : \n");
    regle Regle2 = creerRegle();
    printf(" les premisse de regle 1 est vide ? %s\n", estvidePremisse(Regle1.premisse) ? "Oui" : "Non");
    printf(" les premisse de regle 2 est vide ? %s\n", estvidePremisse(Regle2.premisse) ? "Oui" : "Non");

    printf("\n\n test de la fonction qui renvoie la tete de la premisse d'une regle et la fonction qui donne la conlussion d'une regle: \n");
    printf("La tete de la regle1 est : %s  et la conclusion est : %s \n", tetePremisse(Regle1.premisse), conclRegle(Regle1));


    Regle2 = ajtPremisse(Regle2,"premisse1");
    Regle2 = ajtPremisse(Regle2,"premisse3");
    Regle2 = creerConclusion(Regle2, "c2");

    regle Regle3 = creerRegle();
    Regle3 = ajtPremisse(Regle3,"premisse4");
    Regle3 = ajtPremisse(Regle3,"premisse5");
    Regle3 = ajtPremisse(Regle3,"premisse6");
    Regle3 = creerConclusion(Regle3, "c3");

    printf("\n\n------------------------------\n\n");
    printf("test de la creation de base de connaissance : \n\n");

    BC base1 = creerBaseC();
    base1 = ajouterRegleC(base1,Regle1);
    base1 = ajouterRegleC(base1,Regle2);
    base1 = ajouterRegleC(base1,Regle3);

    printf("voici la base de connaissance apres ajout des règles : \n\n");
    afficherBaseConnaissance(base1);

    printf("\n\n------------------------------\n\n");
    printf("test de la creation de base de faits : \n\n");

    BF baseF = creerBaseF();

    baseF = ajouterFait(baseF, "premisse1");
    baseF = ajouterFait(baseF, "premisse2");
    baseF = ajouterFait(baseF, "premisse3");

    printf("voici la base des faits apres ajout des faits: \n\n");
    afficherBaseF(baseF);

    printf("\n\n------------------------------\n\n");
    printf("test du moteur d'inferrence: \n\n");

    moteurInf(base1,baseF);

    return 0;
    
}