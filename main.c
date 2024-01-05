#include "regles.h"
#include "baseC.h"
#include "baseF.h"
#include "moteurInference.h"

#include <stdio.h>
#include <unistd.h>



int main(){

    int choix;

    do {
        printf("Bienvenue, que voulez-vous faire ?\n1) Comment ça marche\n2) Créer/modifier une base de connaissance\n3) Utiliser le moteur d'inférence\n4) Quitter\n");

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
                printf(" Option 2 :\n\nUne base de connaissance est une liste de règles.\nUne règle est constituée d'une prémisse avec plusieurs propositions.\nÀ partir de toutes ces propositions, on propose une conclusion à la prémisse.\n\nPar exemple, voici une règle : A et B et C => conclusion5. Ainsi, une base de connaissance est constituée de plusieurs règles.\n\n\nOption 3 :\n\nLe moteur d'inférence fonctionne avec une base de faits et une base de connaissance.\nLe moteur d'inférence va chercher, à partir des faits donnés dans la base de faits et de la base de connaissance, si on peut déduire une ou plusieurs conclusions.\n\nExemple : Ma base de faits contient A, B, C et ma base de connaissance contient les règles A et D => conc1 mais aussi A et B => conc 2. Donc ici, le moteur d'inférence peut, à partir de la base de faits donnée et la base de connaissance, déduire la 'conc2'.\n\n\nOption 4 :\n\nQuitter le programme\n");
                break;

            case 2:
                printf("\n-------------------\n");
                int choix = 0;
                do {
                    printf("\nQue voulez-vous faire ?\n1) Modifier une base déjà existante ?\n2) Créer une nouvelle base de connaissance ?\n3) Quitter\n");
                    if (scanf("%d", &choix) != 1) {
                    // si c'est pas un nombre
                        printf("\n => Entrée invalide, veuillez saisir un nombre.\n\n");
                        while (getchar() != '\n');  
                        continue; //reviens au debut
                    }
                    switch(choix){
                        case 1 :
                            printf("\n Quelle base voulez-vous modifier ?\n");
                            char nomFM[50];
                            scanf("%49s", nomFM);
                            BC baseCM = chargerBaseConnaissances(nomFM);
                            int choix3;

                            

                            do{
                                printf("Que voulez-vous faire ?\n1) Supprimer la base\n2) Ajouter une règle ?\n3) Supprimer une proposition de toutes les règles\n\n");
                                
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
                                    printf("Ajoutez une regle");
                                    printf("\nVoici la base avant ajout :\n\n");
                                    printf("----------------------- \n\n");
                                    afficherBaseConnaissance(baseCM);
                                    printf("-----------------------");


                                int choix2;
                                regle RegleM = creerRegle();
                                do {
                                    printf("\n Tapez 1 pour ajouter une prémisse à la règle et 2 pour donner la conclusion.\n");
                                    if (scanf("%d", &choix2) != 1) {
                                        printf("\nsaisir un nombre\n");
                                        while (getchar() != '\n'); 
                                        continue;
                                    }
                                    if (choix2 == 1) {
                                        printf("\n \n Donnez une premisse à la regle :\n\n");
                                        char premise[50];
                                        scanf("%49s", premise);
                                        RegleM = ajtPremisse(RegleM, premise);
                                        printf("\n %s a bien été ajouté. \n\n",premise);
                                        
                                    }  else if (choix2 != 2) {
                                        printf("saisir 1 ou 2\n");
                                    } 
                                        
                                } while (choix2 != 2);
                                if (estvidePremisse(RegleM.premisse)){
                                    printf("=> Erreur : vous n'avez pas donné de prémisse à la règle. \n Relancez le programme");
                                    return 0;
                                }
                                printf("\n Donnez la conclusion à la regle : \n\n");
                                char conclusion[50];
                                scanf("%49s", conclusion);
                                RegleM = creerConclusion(RegleM, conclusion);
                                printf("\n %s a bien été ajouter\n",conclusion);
                                printf("------------------------");
                                printf("\n Voici votre regle ajoutée: \n\n ");
                                afficherRegle(RegleM);
                                baseCM = ajouterRegleC(baseCM,RegleM);
                                
                                
                                
                                printf("------------------------");
                                printf("\n \n Voici votre base apres ajout : \n\n ");
                                afficherBaseConnaissance(baseCM);
                                sauvegarderBaseConnaissances(baseCM, nomFM);
                                libererBC(baseCM);
                                
                                
                                printf("\n \n relancez le programme pour l'utiliser \n À bientôt\n");
                                    break;

                                case 3 :

                                    char prop[50];
                                    printf("\n\n Voici votre base : \n\n");
                                    printf("------------------------\n\n");
                                    afficherBaseConnaissance(baseCM);
                                    printf("\n\n------------------------\n\n");
                                    printf("Quelle proposition voulez-vous supprimer (dans toutes les règles) ? \n");
                                    scanf("%49s", prop);

                                    
                                    baseCM = supPropositionBaseC(baseCM, prop);

              
                                    sauvegarderBaseConnaissances(baseCM, nomFM);

                                    printf("\n\nVotre base a bien été modifiée \n");
                                    printf("\n\nVoici votre base après modification : \n\n");
                                    printf("------------------------\n");
                                    afficherBaseConnaissance(baseCM);
                                    libererBC(baseCM);
                                    printf("\n------------------------\n\n");
                                    printf("\n \n Relancez le programme pour l'utiliser. \n A bientôt\n");

                                    break;
                                
                                default:
                                    // si c'est pas un nombre vallide
                                    printf("\n => Option invalide. Veuillez saisir 1, 2 ou 3 \n \n");
                                    break;
                                }

                            } while (choix3 < 1 || choix3 > 3);
                            break;



                        case 2 :
                            printf("\nQuel nom voulez vous donner à la base ? \n \n");
                            char nomF[50];
                            scanf("%49s", nomF);
                            creerFichierBase(nomF);
                            BC baseC = creerBaseC();
                            
                            int choix1;

                            do {
                            printf("\nVeuillez saisir 1 pour écrire une nouvelle règle ou 2 pour quitter :\n ");
        
        
                            if (scanf("%d", &choix1) != 1) {
                                printf("saisir un nombre\n");
                                while (getchar() != '\n'); 
                                continue;
                            }

                            

                            if (choix1 == 1) {
                                int choix2;
                                regle Regle = creerRegle();
                                do {
                                    printf("\n Tapez 1 pour ajouter une prémisse et 2 pour donner la conclusion. \n");
                                    if (scanf("%d", &choix2) != 1) {
                                        printf("\nsaisir un nombre\n");
                                        while (getchar() != '\n'); 
                                        continue;
                                    }
                                    if (choix2 == 1) {
                                        printf("\n \n Donnez une premisse à la regle :\n\n");
                                        char premise[50];
                                        scanf("%49s", premise);
                                        Regle = ajtPremisse(Regle, premise);
                                        printf("\n %s a bien été ajoutée \n\n",premise);
                                        
                                    }  else if (choix2 != 2) {
                                        printf("saisir 1 ou 2\n");
                                    } 
                                        
                                } while (choix2 != 2);
                                if (estvidePremisse(Regle.premisse)){
                                    printf("=> Erreur : vous n'avez pas donné de prémisse à la règle \n relancez le programme");
                                    return 0;
                                }
                                printf("\n Donnez la conclusion à la regle : \n\n");
                                char conclusion[50];
                                scanf("%49s", conclusion);
                                Regle = creerConclusion(Regle, conclusion);
                                printf("\n %s a bien été ajouté",conclusion);
                                printf("\n------------------------");
                                printf("\n Voici votre regle ajoutée: \n\n ");
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
                            
                            printf("\nVotre base à bien été creer, relancez le programme pour pouvoir l'utiliser\n");
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
                printf("\n\n Veuillez donner le nom de la base de connaissances que vous souhaitez utiliser. \nSi aucune n'est créée, veuillez relancer le programme et en créer une.\n\n");
                char baseCD[50];
                scanf("%49s", baseCD);
                BC baseCDD = chargerBaseConnaissances(baseCD);
                if (baseCDD == NULL){
                    break;
                };
                int choix4;
                BF baseF= creerBaseF();
                do{
                    printf("\n\nVeuillez maintenant donner vos faits, tapez 1 pour ajouter un fait et 2 quand vous avez fini : \n\n");
                    if (scanf("%d", &choix4) != 1) {
                        printf("\nsaisir un nombre\n");
                        while (getchar() != '\n'); 
                        continue;
                    }
                    if (choix4 == 1) {
                        printf("\n \n Donnez un fait:\n\n");
                        char fait[50];
                        scanf("%49s", fait);
                        baseF = ajouterFait(baseF,fait);
                        printf("\n %s a bien été ajouté à vos faits.\n\n",fait);
                    }else if (choix4 != 2) {
                            printf("saisir 1 ou 2\n");
                    } 
                } while (choix4 != 2);
                
                printf("\n\n Voici donc votre base de faits \n \n");
                printf("----------------\n\n");
                afficherBaseF(baseF);
                printf("\n----------------\n\n");
                printf("Le programme va chercher vos faits : \n");
                sleep(2);
                printf("\n\n==> Le moteur d'inférence peut déduire à partir de vos faits et de la base de connaissances les conclusions suivantes :\n");
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
