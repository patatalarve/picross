#include<stdio.h>
#include<stdlib.h>
#include <time.h>

int** chargement_tableau(int NB_L, int NB_C){
	int i;
	int j;
	int alea;
	int**TAB;
	srand(time(NULL));

//initialise le tableau
	//TAB=NULL;
	TAB=(int**)malloc(sizeof(int*)*NB_L);
	
	for(i=0;i<NB_L;i++){
		TAB[i]=(int*)malloc(sizeof(int)*NB_C);
	}
//definie une valeur aléatoir 0 ou 1
	
//rempli le tableau de 0 et 1 aléatoirement
	for(i=0;i<NB_L;i++){
		for(j=0;j<NB_C;j++){
			//definie une valeur aléatoir 0 ou 1
			alea=rand()%2;
			TAB[i][j]=alea;	
		}
	}

return(TAB);
}


//affichage du tableau

void affichage_aleatoire(int NB_L, int NB_C, int **BOARD){

	int i;
	int j;
	

	for(i=0;i<NB_L;i++){
		for(j=0;j<NB_C;j++){

		printf("%d", BOARD[i][j]);
		
		}
	printf("\n");
	}
printf("\n");
}




int main(){
      	int** SEQ;
	int** BOARD;
	int NB_L;
	int NB_C;
	system("clear");	
        printf("Quelle est la taille du pricross voulu\n\t Nombres de lignes ?\n");
	scanf("%d",&NB_C);
	
	printf("\t Nombres de colonnes ?\n");
	scanf("%d",&NB_L);
	
	BOARD=chargement_tableau(NB_L, NB_C);
	system("clear");
	affichage_aleatoire(NB_L, NB_C, BOARD);
	

return(0);
}













