#define MAX_LIGNES 11
#define MAX_COL 11

int tableau()
{
    int x,y;
    char plateau1[MAX_LIGNES][MAX_COL];
    char abcisses[MAX_LIGNES] = {'X', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    char ordonnees[MAX_LIGNES] = {'X', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    //boucles d'initialisation plateau1
 
    for(x=0;x<MAX_LIGNES;x++){
        plateau1[0][x]=abcisses[x];
    }
    for(y=0;y<MAX_COL;y++){
        plateau1[y][0]=ordonnees[y];
    }
 
    for(x=1;x<MAX_LIGNES;x++){
        for(y=1;y<MAX_COL;y++){
            plateau1[x][y]='O';
        }
    }

    //Boucle d'affichage
    printf("\n");
    for(x=0;x<MAX_LIGNES;x++){
        printf("%c | ",plateau1[0][x]);
    }
    printf("\n- - - - - - - - - - - - - - - - - - - - - \n");
 
    for(x=1;x<MAX_LIGNES;x++){
        for(y=0;y<MAX_COL;y++){
            if(y==0){
                printf("%c | ",plateau1[x][y]);
            }
            else{
                printf("%c   ",plateau1[x][y]);
            }
        }
        printf("\n  | \n");
    }
    return 0;
}