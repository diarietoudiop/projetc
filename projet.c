#include <stdio.h>
#include <string.h>
#include<unistd.h>
#include <ctype.h>
// Structure pour date
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

// Structure pour un apprenant
typedef struct {
    int id; 
    char nom[50];
    char mot_de_passe[50];
    int estApprenant;
    Date dn;
    int etat;
    int nbrabsence;
    int Classe;
    int cumulretard;
    int presence;
    int role;
} APPRENANT;

// Structure pour les administrateurs
typedef struct {
    int id;
    int matricule;
    char nom[10];
    char prenom[20];
    char password[30];
    int estApprenant;
} ADMIN;


int main() {
    APPRENANT utilisateurs[100];  
    ADMIN admin;

    
    int nbUtilisateurs = chargerUtilisateur(utilisateurs);

    printf("----- Page de Connexion -----\n");

    int estApprenant = pageDeConnexion(utilisateurs, &admin);

    while (estApprenant == -1) {
        printf("Connexion échouée. Veuillez vérifier vos identifiants.\n");

        estApprenant = pageDeConnexion(utilisateurs, &admin);
    }

    if (estApprenant == 1) {
        printf("Nom d'utilisateur chargé : %s\n", utilisateurs[0].nom);  
        menuApprenant();
        
    } else if (estApprenant == 2) {
        printf("Nom d'administrateur chargé : %s\n", admin.nom);
        menuNonApprenant(); 
    }

    return 0;
}

// Fonction pour la page de connexion
int pageDeConnexion(APPRENANT utilisateur[], ADMIN *admin) {
    char nomSaisi[50];
    char motDePasseSaisi[50];

    printf("Nom d'utilisateur : ");
    int c = getchar();
    while (c != '\n' && isspace(c)){
        printf("Le champ du mot de passe est requis.\n");  
        return -1; 
    }
    scanf("%s", nomSaisi);

    printf("Mot de passe : ");
    //scanf("%s", motDePasseSaisi);
    strcpy(motDePasseSaisi, getpass("Mot de passe:"));


    if (strcmp(nomSaisi, "admin") == 0) {
        if (strcmp(motDePasseSaisi, admin->password) == 0) {
            return 2; 
        } else {
            return -1; 
        }
    } else {
        for (int i = 0; i < 100; i++) { 
            if (strcmp(nomSaisi, utilisateur[i].nom) == 0 && strcmp(motDePasseSaisi, utilisateur[i].mot_de_passe) == 0) {
                if (utilisateur[i].estApprenant) {
                    return 1;  
                } else {
                    return 2;  
                }
            }
        }

        return -1; 
    }
}

// Fonction pour charger les utilisateurs depuis un fichier
int chargerUtilisateur(APPRENANT utilisateur[]) {
    
    FILE *utilisateurFile = fopen("utilisateur.txt", "r");

    if (utilisateurFile != NULL) {
        int i = 0;
        while (fscanf(utilisateurFile, "%s %s %d", utilisateur[i].nom, utilisateur[i].mot_de_passe, &utilisateur[i].estApprenant) != EOF) {
            
            i++;
        }

        fclose(utilisateurFile);
        return i; 
    } else {
        printf("Aucun fichier utilisateur.txt trouvé.\n");
        return 0; 
    }
}

// Fonction pour le menu des apprenants
void menuApprenant() {
    printf("Menu Apprenant :\n");
    printf("1. MARQUER MA PRÉSENCE\n");
    printf("2. NOMBRE DE MINUTES D’ABSENCE\n");
    printf("3. mes messages\n");
    printf("4. Quitter\n");
    int option;
    scanf("%d", &option);
    if  (option == 1) {
    marquerPresence();
    }
        
    
}

// Fonction pour le menu des non-apprenants
void menuNonApprenant() {
    int choix;
    do{
        printf("Menu Administrateur :\n");
        printf("1. GESTION DES ÉTUDIANTS\n");
        printf("2. GÉNÉRATION DE FICHIERS\n");
        printf("3. MARQUER LES PRÉSENCES\n");
        printf("4. ENVOYER UN MESSAGE\n");
        printf("5. Quitter\n");
        printf("\nVotre Choix ? ");
        scanf("%d", &choix);
    }while(choix<1 || choix>5);
    if(choix==1){
        do{
            int choix2;
            printf("Menu gestion d'etudiants :\n");
            printf("1. ajouts\n");
            printf("2. Editions\n");
            printf("3. suppression\n");
            printf("4. liste\n");
            printf("5. Quitter\n");
            printf("\nVotre Choix ? ");
            scanf("%d", &choix2);
        }while(choix!=5);
    }
    if(choix==2){
        
        do{
            int choix3;
            printf(" :\n");
            printf("1. ajouts\n");
            printf("2. Editions\n");
            printf("3. suppression\n");
            printf("4. liste\n");
            printf("5. Quitter\n");
            printf("\nVotre Choix ? ");
            scanf("%d", &choix3);
        }while(choix!=3);
        
    } 
}
// Fonction pour marquer la présence
//void marquerPresence(APPRENANT *utilisateur) {
    u//tilisateur->presence = 1;
   // printf("Présence de l'utilisateur %s marquée.\n", utilisateur->nom);





