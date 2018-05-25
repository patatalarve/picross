//calcule les ous sequence des lignes d'un tableau et les rentre dans un tableau a bi dimension
int** calcul_des_sous_sequences_cote(int NB_L, int NB_C, int **BOARD){

	int **TABsoussequencecote;
	int i;
	int j;
	int c=0;
	int d=0;
//compteur	
	int seq=0;
//initialise le tableau qui va prendre les sous sequence des colonnes de taille NB_L et (NB_C+1)/2
	TABsoussequencecote=NULL;
	TABsoussequencecote=(int**)malloc(sizeof(int*)*NB_C);
	
	for(i=0;i<NB_C;i++){
		TABsoussequencecote[i]=(int*)malloc(sizeof(int)*NB_L);
	}

	for(i=0;i<NB_C;i++){
		for(j=0;j<NB_L;j++){
			if(BOARD[i][j]==1){
				seq++;
			}
			if(seq!=0 && BOARD[i][j]==0){
				TABsoussequencecote[c][d]=seq;
				d++;
				seq=0;
			}				
			if(seq!=0 && j==(NB_L-1)){
				TABsoussequencecote[c][d]=seq;
				seq=0;
			}
		}	
	c++;
	d=0;

	}		
return(TABsoussequencecote);
}
void affichage_TAB(int NB_L, int NB_C, int **BOARD){

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

	SEQ=calcul_des_sous_sequences_cote(NB_L,NB_C,BOARD);
	affichage_TAB(NB_L,(NB_C+1)/2,SEQ);



return(0);
}
