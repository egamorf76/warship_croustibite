#define NB_COLONNES 11
#define NB_LIGNES 11
#define NB_BATEAUX 5
#define TAILLES_BATEAUX 2

struct Case
{
   int x;
   int y;
   char contenu; // 'E' pour eau, 'B' pour bateau, 'T' pour tir raté, 'H' pour tir réussi
};

void initialiserGrille(struct Case grille[NB_LIGNES][NB_COLONNES])
{
   // Initialise toutes les cases de la grille avec de l'eau
   for (int i = 0; i < NB_LIGNES; i++)
   {
      for (int j = 0; j < NB_COLONNES; j++)
      {
         grille[i][j].x = i;
         grille[i][j].y = j;
         grille[i][j].contenu = 'E';
      }
   }
   // Place aléatoirement les bateaux sur la grille
   placerBateaux(grille);
}

void placerBateaux(struct Case grille[NB_LIGNES][NB_COLONNES])
{
   for (int i = 0; i < NB_BATEAUX; i++)
   {
      int taille = TAILLES_BATEAUX[i];
      int x, y, direction;
      do
      {
         // Génère des coordonnées aléatoires pour le bateau
         x = rand() % NB_LIGNES;
         y = rand() % NB_COLONNES;
         direction = rand() % 2; // 0 pour horizontal, 1 pour vertical
      } while (!verifierPlacement(grille, x, y, taille, direction));
      // Place le bateau sur la grille
      placerBateau(grille, x, y, taille, direction);
   }
}

int verifierPlacement(struct Case grille[NB_LIGNES][NB_COLONNES], int x, int y, int taille, int direction)
{
   // Vérifie si le bateau dépasse de la grille
   if ((direction == 0 && y + taille > NB_COLONNES) || (direction == 1 && x + taille > NB_LIGNES))
   {
      return 0;
   }
   // Vérifie si le bateau entre en collision avec un autre bateau
   for (int i = 0; i < taille; i++)
   {
      if ((direction == 0 && grille[x][y + i].contenu == 'B') || (direction == 1 && grille[x + i][y].contenu == 'B'))
      {
         return 0;
      }
   }
   return 1;
}

void afficherGrille(struct Case grille[NB_LIGNES][NB_COLONNES])
{
   printf("  ");
   for (int j = 0; j < NB_COLONNES; j++)
   {
      printf("%d ", j);
   }
   printf("\n");
   for (int i = 0; i < NB_LIGNES; i++)
   {
      printf("%d ", i);
      for (int j = 0; j < NB_COLONNES; j++)
      {
         printf("%c ", grille[i][j].contenu);
      }
      printf("\n");
   }
}

void effectuerTir(struct Case grilleJoueur[NB_LIGNES][NB_COLONNES], struct Case grilleAdversaire[NB_LIGNES][NB_COLONNES], int x, int y)
{
   if (grilleAdversaire[x][y].contenu == 'B')
   {
      grilleAdversaire[x][y].contenu = 'H'; // Tir réussi
      grilleJoueur[x][y].contenu = 'H';     // Mise à jour de la grille du joueur actuel
      printf("Coulé !\n");
   }
   else
   {
      grilleAdversaire[x][y].contenu = 'T'; // Tir raté
      grilleJoueur[x][y].contenu = 'T';     // Mise à jour de la grille du joueur actuel
      printf("Manqué !\n");
   }
}

int tousBateauxCoules(struct Case grille[NB_LIGNES][NB_COLONNES])
{
   for (int i = 0; i < NB_LIGNES; i++)
   {
      for (int j = 0; j < NB_COLONNES; j++)
      {
         if (grille[i][j].contenu == 'B')
         {
            return 0; // Il reste au moins un bateau non coulé
         }
      }
   }
   return 1; // Tous les bateaux ont été coulés
}

int main()
{
   struct Case grilleJoueur1[NB_LIGNES][NB_COLONNES];
   struct Case grilleJoueur2[NB_LIGNES][NB_COLONNES];
   int joueurActuel = 1;

   initialiserGrille(grilleJoueur1);
   initialiserGrille(grilleJoueur2);

   while (!tousBateauxCoules(grilleJoueur1) && !tousBateauxCoules(grilleJoueur2))
   {
      printf("Grille du Joueur %d :\n", joueurActuel);
      afficherGrille(grilleJoueur1); // Afficher la grille du joueur actuel

      int x, y;
      printf("Joueur %d, entrez les coordonnées de votre tir :\n", joueurActuel);
      scanf("%d %d", &x, &y);

      // Vérifier si les coordonnées sont valides, puis effectuer le tir
      if (x >= 0 && x < NB_LIGNES && y >= 0 && y < NB_COLONNES)
      {
         if (joueurActuel == 1)
         {
            effectuerTir(grilleJoueur1, grilleJoueur2, x, y);
         }
         else
         {
            effectuerTir(grilleJoueur2, grilleJoueur1, x, y);
         }
         joueurActuel = (joueurActuel == 1) ? 2 : 1; // Changer de joueur
      }
      else
      {
         printf("Coordonnées invalides. Veuillez réessayer.\n");
      }
   }

   // Le jeu est terminé, afficher le gagnant
   if (tousBateauxCoules(grilleJoueur1))
   {
      printf("Joueur 2 a gagné !\n");
   }
   else
   {
      printf("Joueur 1 a gagné !\n");
   }

   return 0;
}
