#include <stdio.h>
#include <string.h>
#include<unistd.h>
#include <ctype.h>
#include<time.h>
#include <stdlib.h>
#include <stdbool.h>


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
    char prenom[50];
    char mot_de_passe[50];
    int estApprenant;
    Date dn;
    int etat;
    int nbrabsence;
    int Classe;
    int cumulretard;
    int presence;
    int role;
    int classe;
    int code;
} APPRENANT;

// Structure pour les administrateurs
typedef struct {
    int id;
    int matricule;
    char nom[10];
    char prenom[20];
    char password[20];
    int estApprenant;
} ADMIN;
// structur heure
typedef struct{
    int h;
    int m;
}HEURE;

//prototype
// Prototypes de fonction
int chargerUtilisateur(APPRENANT utilisateur[]);
int pageDeConnexion(APPRENANT utilisateur[], ADMIN *admin);
void menuApprenant();
void menuNonApprenant();
int marquerPresence();
//APPRENANT chercherUtilisateurParId(int id);
//void modifierUtilisateur(APPRENANT utilisateur);



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
        
        int option;
        printf("\nMenu Apprenant :\n");
        printf("1.... MARQUER MA PRÉSENCE\n");
        printf("2... NOMBRE DE MINUTES D’ABSENCE\n");
        printf("3... mes messages\n");
        printf("4...Quitter\n");
        printf("\n Faites votre choix");
        scanf("%d", &option);
        if(option==1){
            marquerPresence();
        }
        
            

           

            
    } else if (estApprenant == 2) {
        printf("Nom d'administrateur chargé : %s\n", admin.nom);

         int choix;
    do{
        printf("Menu Administrateur :\n");
        printf("1. GESTION DES ÉTUDIANTS\n");
        printf("2. GÉNÉRATION DE FICHIERS\n");
        printf("3. MARQUER LES PRÉSENCES\n");
        printf("4. ENVOYER UN MESSAGE\n");
        printf("5. Quitter\n");
        printf("\nVotre Choix \n? ");
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
    
    if (choix == 3) {
    char matricule[20];
    int codeAttendu;
    char password[20];
     const char adminPassword[] = "mot_de_passe2";
     #define MAX_CODES 100
        int codesDejaTraites[MAX_CODES];
        int nbCodesTraites = 0;
    FILE *file = fopen("code-admin.txt", "r");

    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        // Quittez le programme en cas d'erreur d'ouverture de fichier
    }

        do {
            printf("Entrer votre code (entrez 'q' pour quitter) : ");
            scanf("%s", matricule);

            if (strcmp(matricule, "q") == 0) {
                // Demander le mot de passe de l'admin
                printf("Entrer votre mot de passe d'admin : ");
                scanf("%s", password);

                // Vérifier le mot de passe
                if (strcmp(password, "mot_de_passe2") == 0) {
                    printf("Mot de passe correct. Retour à la saisie du code.\n");
                    // Retourner au début de la boucle
                    continue;
                } else {
                    printf("Mot de passe incorrect. Sortie du programme.\n");
                    break;
                }
            }

            if (fscanf(file, "%4d", &codeAttendu) == 1) {
                int codeAttendu = atoi(matricule);
                // Vérifier si le code est déjà traité
                    int codeDejaTraite = 0;
                    for (int i = 0; i < nbCodesTraites; i++) {
                        if (codeAttendu == codesDejaTraites[i]) {
                            codeDejaTraite = 1;
                            break;
                        }
                    }

                    if (codeDejaTraite) {
                        printf("Ce code a déjà été traité. Passer au suivant.\n");
                        continue;  // Passer au code suivant
                    }
                    codesDejaTraites[nbCodesTraites++] = codeAttendu;
                    // Vérifier si le code est correct
                    if (codeAttendu == atoi(matricule)) {
                        // Obtenir l'heure locale
                        struct tm *tm_info;
                        time_t t;
                        time(&t);
                        tm_info = localtime(&t);

                        printf("Vous êtes marqué présent.\n");
                        printf("Date actuelle : %02d/%02d/%04d\n", tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900);
                        printf("Heure actuelle : %02d:%02d:%02d\n", tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);

                        // Enregistrer la présence dans le fichier presence.txt
                        FILE *presenceFile = fopen("presence.txt", "a");

                        if (presenceFile != NULL) {
                            fprintf(presenceFile, "Matricule : %s, Date : %02d/%02d/%04d, Heure : %02d:%02d:%02d\n",
                                    matricule, tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900,
                                    tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);

                            fclose(presenceFile);
                        } else {
                            perror("Erreur lors de l'ouverture du fichier presence.txt");
                        }
                    } else {
                        printf("vous etes deja marqué present.\n");
                    }
            } else {
                    // Lecture échouée ou fin de fichier atteinte
                    printf("Erreur lors de la lecture du fichier ou fin du fichier atteinte.\n");
                    break;
        }

    } while (1);

    fclose(file);

            

        } while (choix != 5);
    }

    return 0;
}




// Fonction pour la page de connexion
int pageDeConnexion(APPRENANT utilisateur[], ADMIN *admin) {
    char nomSaisi[50];
    char motDePasseSaisi[50];

        while (1) {
        printf("Nom d'utilisateur : ");

        // Utilisez fgets pour lire la ligne complète, y compris les espaces
        if (fgets(nomSaisi, sizeof(nomSaisi), stdin) == NULL) {
            perror("Erreur lors de la lecture du nom d'utilisateur");
            return -1;
        }

        // Supprimez le caractère de nouvelle ligne du nomSaisi si présent
        size_t len = strlen(nomSaisi);
        if (len > 0 && nomSaisi[len - 1] == '\n') {
            nomSaisi[len - 1] = '\0';
        }

        // Vérifiez si le champ du nom d'utilisateur est vide ou contient seulement des espaces
        int champVide = 1;
        for (size_t i = 0; i < len - 1; i++) {
            if (!isspace(nomSaisi[i])) {
                champVide = 0;
                break;
            }
        }

        if (champVide) {
            printf("Le champ du nom d'utilisateur est requis.\n");
            continue;  // Retournez au début de la boucle pour permettre la ressaisie
        }

        break;  // Sortez de la boucle lorsque l'utilisateur appuie sur Entrée
    }

    printf("Mot de passe : ");
    strcpy(motDePasseSaisi, getpass("Mot de passe invisible:")); 
    



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



int marquerPresence(int idapprenant)
{
    int v;
    char confirmation;
    time_t temps;
    struct tm *tempsActuel;

    printf("Confirmez-vous votre présence ? (o/n): ");
    scanf(" %c", &confirmation);
    APPRENANT a;                                  
    //APPRENANT a = verifiEtuExiste(idapprenant, &v);
    time(&temps);
    tempsActuel = localtime(&temps);

    if (confirmation == 'o' || confirmation == 'O')
    {
        int id1;
        char fich[30], date[15], line[200], heure[30], nom1[50], prenom1[50], code1[5];

        strcpy(fich, "copy_presence_");
        sprintf(date, "%02d_%02d_%d", tempsActuel->tm_mday, tempsActuel->tm_mon + 1, tempsActuel->tm_year + 1900);
        strcat(fich, date);
        strcat(fich, ".txt");
        sprintf(heure, "%2d : %2d", tempsActuel->tm_hour, tempsActuel->tm_min);

        FILE *fichPresence = fopen(fich, "a");
        FILE *fichPresence2 = fopen(fich, "ra");

        while (fgets(line, 200, fichPresence2) != NULL)
        {
            sscanf(line, "%d %s %s %s", &id1, nom1, prenom1, code1);
            if (idapprenant == id1)
            {
                printf("La présence a été déjà enregistrée\n");
                fclose(fichPresence2);
                fclose(fichPresence);
                return -1;
            }
        }

        fprintf(fichPresence, "%d %s %s %s %d %d\n", a.id, a.nom, a.prenom, a.code, a.classe, heure);

        fclose(fichPresence);
        fclose(fichPresence2);

        printf("date : %s heure : %s fichier : %s\n", date, heure, fich);
        if (tempsActuel->tm_hour >= 8)
        {
            int min = (tempsActuel->tm_hour - 8) * 60 + tempsActuel->tm_min;
            printf("Vous avez un retard !\n");
            a.cumulretard = a.cumulretard + min;
        }
        else
        {
            printf("Présence enregistrée à l'heure.\n");
        }
        printf("Présence confirmée le %02d/%02d/%d à %02d:%02d\n",
               tempsActuel->tm_mday, tempsActuel->tm_mon + 1, tempsActuel->tm_year + 1900,
               tempsActuel->tm_hour, tempsActuel->tm_min);
        return 1;
    }
    else
    {
        printf("Présence non confirmée.\n");
        return 0;
    }
}


























    
    



   
    
    





