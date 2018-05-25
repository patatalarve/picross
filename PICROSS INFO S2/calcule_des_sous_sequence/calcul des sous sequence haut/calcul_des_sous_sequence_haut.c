#include<stdio.h> 
#include<stdlib.h>

//calcule les ous sequence des colonnes d'un tableau et les rentres dans un tableau a bi-dimension
int** calcul_des_sous_sequence_haut(int NB_L, int NB_C, int **BOARD){

	int **TABsousequencehaut;
	int i;
	int j;
	int c=0;
	int d=0;
//compteur	
	int seq=0;
//initialise le tableau qui va prendre les sous sequence des colonnes de taille NB_L et (NB_C+1)/2
	TABsousequencehaut=NULL;
	TABsousequencehaut=(int**)malloc(sizeof(int*)*NB_L);
	
	for(i=0;i<NB_L;i++){
		TABsousequencehaut[i]=(int*)malloc(sizeof(int)*NB_C);
	}

	
	for(j=0;j<NB_L;j++){
		for(i=0;i<NB_C;i++){
			if(BOARD[i][j]==1){
				seq++;
			}
			if(seq!=0 && BOARD[i][j]==0){
				TABsousequencehaut[c][d]=seq;
				d++;
				seq=0;
			}
			if(seq!=0 && i==(NB_C-1)){
				TABsousequencehaut[c][d]=seq;
				seq=0;
			}				

		}	
	c++;
	d=0;

	}		
return(TABsousequencehaut);
}

int** remise_haut(int NB_L, int NB_C, int** TABsousequencehaut){

	int i;
	int j;
	int** TAB_sous_sequence_haut_final;
// initialise le tableaux qui va nous servir a mettre de haut en bas
	TAB_sous_sequence_haut_final=NULL;
	TAB_sous_sequence_haut_final=(int**)malloc(sizeof(int*)*NB_L);
	
	for(i=0;i<NB_L;i++){
		TAB_sous_sequence_haut_final[i]=(int*)malloc(sizeof(int)*NB_C);
	}


	for(i=0;i<NB_L;i++){
		for(j=(NB_C-1);j>=0;j--){
			TAB_sous_sequence_haut_final[j][i]=TABsousequencehaut[i][j];
		}	
	}

	/*for(i=0;i<(NB_L+1)/2;i++){
		for(j=0;j<NB_C;j++){
			printf("%d ",TAB_sous_sequence_haut_final[i][j]);
		}
	printf("\n");
	}

printf("\n");*/
}
return(TAB_sous_sequence_haut_final);

int main(){

return(0);
}
