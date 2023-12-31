#include "regles.h"
#include "baseC.h"
#include "baseF.h"
#include "moteurInference.h"

#include <stdio.h>
#include <unistd.h>



int main(){

    int choix;

    do {
        printf("Bienvenue, que voulez-vous faire ? \n 1) Comment ça marche \n 2) Créer/modiffier une base de connaissance \n 3) Utiliser le moteur d'inférence \n 4) Quitter \n ");

        if (scanf("%d", &choix) != 1) {
            // si c'est pas un nombre
            printf("\n => Entrée invalide, veuillez saisir un nombre.\n\n");
            while (getchar() != '\n');  
            continue; //reviens au debut
        }

        // traitement des choix
        switch (choix) {
            case 1:
                printf("\n-------------------\n");
                printf(" Option 2 : \n\n Une base de connaissance est une liste de regles.\n Une regles est constituer d'une premisse avec plusieurs propositions.\n A partir de tout c'est proposition on propose une conclusion a la premisse.\n\n Par exemple voici une regles A et B et C => conclusion5. \n Ainsi une base de connaissance est constituer de plusieurs règles. \n\n\n\n Option 3 : \n\n Le moteur d'inferance fonctionne avec une base de faits et une base de connaissance.\n Le moteur d'inferance va chercher a partir des faits donner dans la base de faits et de la base de connaissance si on peut deduire une ou plusieurs conclusion. \n\n Exemple : \n Ma base de fait contient A B C et ma base de connaissance contient les regles A et D => conc1 mais aussi A et B => conc 2 \n Donc ici le moteur d'inférence peut a partir de la base de faits donner et la base de connaissance, deduire la 'conc2'  \n\n\n\n Option 4 : \n\n Quitter le programme\n");
                break;

            case 2:
                printf("\n-------------------\n");
                int choix = 0;
                do {
                    printf("Que voulez vous faire ? \n 1) Modifier une base deja existante ? \n 2) Creer une nouvelle base de connaissance ? \n 3) Quitter\n");
                    if (scanf("%d", &choix) != 1) {
                    // si c'est pas un nombre
                        printf("\n => Entrée invalide, veuillez saisir un nombre.\n\n");
                        while (getchar() != '\n');  
                        continue; //reviens au debut
                    }
                    switch(choix){
                        case 1 :
                            printf("\n Quelles base voulez vous modifier ? \n");
                            char nomFM[50];
                            scanf("%49s", nomFM);
                            BC baseCM = chargerBaseConnaissances(nomFM);
                            int choix3;

                            

                            do{
                                printf("\n Que voulez vous faire ? \n 1) Supprimer la base \n 2) Ajouter une regle ? \n 3) Supprimer une proposition de la tete \n\n");
                                
                                if (scanf("%d", &choix3) != 1) {
                                // si c'est pas un nombre
                                    printf("\n => Entrée invalide, veuillez saisir un nombre.\n\n");
                                while (getchar() != '\n');  
                                continue; //reviens au debut
                                }

                                switch (choix3)
                                {
                                case 1 :
                                    supprimerFichierBase(nomFM);
                                    libererBC(baseCM);
                                    printf("\nA bientot\n");
                                    break;


                                case 2 :
                                    printf("Ajouter une regle");
                                    printf("\nvoici la base avant ajout :\n\n");
                                    printf("----------------------- \n\n");
                                    afficherBaseConnaissance(baseCM);
                                    printf("-----------------------");


                                int choix2;
                                regle RegleM = creerRegle();
                                do {
                                    printf("\n Taper 1 pour ajouter une premise a la regle et 2 pour donner la conclusion \n");
                                    if (scanf("%d", &choix2) != 1) {
                                        printf("\nsaisir un nombre\n");
                                        while (getchar() != '\n'); 
                                        continue;
                                    }
                                    if (choix2 == 1) {
                                        printf("\n \n Donner premisse à la regle :\n\n");
                                        char premise[50];
                                        scanf("%49s", premise);
                                        RegleM = ajtPremisse(RegleM, premise);
                                        printf("\n %s a bien été ajouter \n\n",premise);
                                        
                                    }  else if (choix2 != 2) {
                                        printf("saisir 1 ou 2\n");
                                    } 
                                        
                                } while (choix2 != 2);
                                if (estvidePremisse(RegleM.premisse)){
                                    printf("=> erreur vous n'avez pas donner de premisse a la regle \n relancer le programme");
                                    return 0;
                                }
                                printf("\n Donner la conclusion à la regle : \n\n");
                                char conclusion[50];
                                scanf("%49s", conclusion);
                                RegleM = creerConclusion(RegleM, conclusion);
                                printf("\n %s a bien été ajouter\n",conclusion);
                                printf("------------------------");
                                printf("\n Voici votre regle ajouter: \n\n ");
                                afficherRegle(RegleM);
                                baseCM = ajouterRegleC(baseCM,RegleM);
                                
                                
                                
                                printf("------------------------");
                                printf("\n \n Voici votre base apres ajout : \n\n ");
                                afficherBaseConnaissance(baseCM);
                                sauvegarderBaseConnaissances(baseCM, nomFM);
                                libererBC(baseCM);
                                
                                
                                printf("\n \n relancer le programme pour l'utiliser \n à bientot\n");
                                    break;

                                case 3 :

                                    char prop[50];
                                    printf("\n\n Voici votre base : \n\n");
                                    printf("------------------------\n\n");
                                    afficherBaseConnaissance(baseCM);
                                    printf("\n\n------------------------\n\n");
                                    printf("Quelle proposition voulez-vous supprimer (dans toutes les regles) ? \n");
                                    scanf("%49s", prop);

                                    
                                    baseCM = supPropositionBaseC(baseCM, prop);

              
                                    sauvegarderBaseConnaissances(baseCM, nomFM);

                                    printf("\n\nVotre base a bien été modifier \n");
                                    printf("\n\nVoici votre base apres modification : \n\n");
                                    printf("------------------------\n");
                                    afficherBaseConnaissance(baseCM);
                                    libererBC(baseCM);
                                    printf("\n------------------------\n\n");
                                    printf("\n \n relancer le programme pour l'utiliser \n A bientôt\n");

                                    break;
                                
                                default:
                                    // si c'est pas un nombre vallide
                                    printf("\n => Option invalide. Veuillez saisir 1, 2 ou 3 \n \n");
                                    break;
                                }

                            } while (choix3 < 1 || choix3 > 3);
                            break;



                        case 2 :
                            printf("\nQuelles nom voulez vous donner a la base ? \n \n");
                            char nomF[50];
                            scanf("%49s", nomF);
                            creerFichierBase(nomF);
                            BC baseC = creerBaseC();
                            
                            int choix1;

                            do {
                            printf("\nVeuillez saisir 1 pour ecrire une nouvelle regle ou 2 pour quitter: \n ");
        
        
                            if (scanf("%d", &choix1) != 1) {
                                printf("saisir un nombre\n");
                                while (getchar() != '\n'); 
                                continue;
                            }

                            

                            if (choix1 == 1) {
                                int choix2;
                                regle Regle = creerRegle();
                                do {
                                    printf("\n taper 1 pour ajouter une premise et 2 pour donner la conclusion \n");
                                    if (scanf("%d", &choix2) != 1) {
                                        printf("\nsaisir un nombre\n");
                                        while (getchar() != '\n'); 
                                        continue;
                                    }
                                    if (choix2 == 1) {
                                        printf("\n \n Donner premisse à la regle :\n\n");
                                        char premise[50];
                                        scanf("%49s", premise);
                                        Regle = ajtPremisse(Regle, premise);
                                        printf("\n %s a bien été ajouter \n\n",premise);
                                        
                                    }  else if (choix2 != 2) {
                                        printf("saisir 1 ou 2\n");
                                    } 
                                        
                                } while (choix2 != 2);
                                if (estvidePremisse(Regle.premisse)){
                                    printf("=> erreur vous n'avez pas donner de premisse a la regle \n relancer le programme");
                                    return 0;
                                }
                                printf("\n Donner la conclusion à la regle : \n\n");
                                char conclusion[50];
                                scanf("%49s", conclusion);
                                Regle = creerConclusion(Regle, conclusion);
                                printf("\n %s a bien été ajouter",conclusion);
                                printf("------------------------");
                                printf("\n Voici votre regle ajouter: \n\n ");
                                afficherRegle(Regle);
                                baseC = ajouterRegleC(baseC,Regle);
                                
                                printf("------------------------");
                                printf("\n \n voici votre base actuelle : \n\n ");
                                afficherBaseConnaissance(baseC);
                                
                            } else if (choix1 != 2) {
                                printf("saisir 1 ou 2\n");
                            }
                            } while (choix1 != 2);
                            sauvegarderBaseConnaissances(baseC, nomF);
                            
                            libererBC(baseC);
                            
                            printf("\nVotre base à bien été creer, relancer le programme pour pouvoir l'utiliser\n");
                            break;
                        case 3 :
                            printf("A bientot");
                            exit(0);
                        default:
                            // si c'est pas un nombre vallide
                            printf("\n => Option invalide. Veuillez saisir 1, 2 ou 3\n \n");
                            break;
                    }
                    while (getchar() != '\n');
                } while (choix < 1 || choix > 3);



                break;

            case 3:
                printf("\n\n Veuillez donner le nom de la base de connaissance que vous voullez utiliser (si aucune n'est creer relancer et creer en une): \n\n");
                char baseCD[50];
                scanf("%49s", baseCD);
                BC baseCDD = chargerBaseConnaissances(baseCD);
                if (baseCDD == NULL){
                    break;
                };
                int choix4;
                BF baseF= creerBaseF();
                do{
                    printf("\n\nVeuillez maitenant donner vos faits, taper 1 pour ajouter un faits et 2 quand vous avez finit: \n\n");
                    if (scanf("%d", &choix4) != 1) {
                        printf("\nsaisir un nombre\n");
                        while (getchar() != '\n'); 
                        continue;
                    }
                    if (choix4 == 1) {
                        printf("\n \n Donner un fait:\n\n");
                        char fait[50];
                        scanf("%49s", fait);
                        baseF = ajouterFait(baseF,fait);
                        printf("\n %s a bien été ajouter a vos fait\n\n",fait);
                    }else if (choix4 != 2) {
                            printf("saisir 1 ou 2\n");
                    } 
                } while (choix4 != 2);
                
                printf("\n\n Voici donc votre base de faits \n \n");
                printf("----------------\n\n");
                afficherBaseF(baseF);
                printf("\n----------------\n\n");
                printf("Le programme va chercher vos fait : \n");
                sleep(2);
                printf("\n\n==> Le moteur d'inférence peut déduire a partire de vos fait et de la base de connaissance les conclusions suivantes :\n");
                moteurInf(baseCDD,baseF);
                libererBC(baseCDD);
                libererBaseF(baseF);
                
                break;

            case 4:
                // quitte le programme
                printf("Au revoir !\n");
                exit(0);

            default:
                // si c'est pas un nombre vallide
                printf("\n => Option invalide. Veuillez saisir 1, 2, 3 ou 4.\n \n");
                break;
        }

        while (getchar() != '\n');
    } while (choix < 1 || choix > 4); //tant que l'utilisateur donne pas un nombre valide

    return 0;

}
