#include<stdio.h>
#include<stdlib.h>

//charge une m	trice a partir d'un fichier dans le même dossier 
int ** chargement_image(char* fichier){
	int NB_L; 
	int NB_C;
	int i;
	int j;
	FILE *file;
//ouvre le fichier choisi et le lis
	file=fopen(fichier,"r");
//defini par les deux premiers chiffres du fichier nombre de colonne et nombre de ligne 	
	int **TAB = NULL;	
	fscanf(file,"%d",&NB_C);
	fscanf(file,"%d",&NB_L);
//alocation dynamique du tableau

	TAB=(int**)malloc(sizeof(int*)*NB_C);
	for(i=0;i<NB_C;i++){
		TAB[i]=(int*)malloc(sizeof(int)*NB_L);
		}
//remplie le tableau alloué dynamiquement par les valeurs du fichier 

	for(i=0;i<NB_L;i++){
		for(j=0;j<NB_C;j++){

			fscanf(file,"%d",&TAB[i][j]);

		}
	}
//fermeture de la lecture du fichier
	fclose(file);
//retourne le tableau completé
	return (TAB);
}

//initialisation du choix du joueur pour le mode image 
	int** image (){
	int** TAB;	
	int NBR;
	printf("Quel mode voulez vous essayez ? \n\t 1)3*3\n\t 2)5*5\n\t 3)10*10\n\t 4)20*20\n ");
	scanf("%d",&NBR);
	
   	if(NBR==1){
		TAB=chargement_image("3*3.txt");
	}
	if(NBR==2){
		TAB=chargement_image("5*5.txt");
	}
	if(NBR==3){
		TAB=chargement_image("10*10.txt");
	}
	if(NBR==4){
		TAB=chargement_image("20*20.txt");
	}

	return(TAB);
}

//initialisation d'une fonction showarray nous permettant de tester nos tableau.

void show_array( int NB_L, int NB_C, int ** TAB){
	system("clear");

        int i;
        int j;
	


	for (i = 0 ; i < NB_L  ; i++) {
                for (j = 0 ; j < NB_C ; j++) {
                     printf("%d ",TAB[i][j]);
                }
               printf("\n");


        }
}

int main (){

	
	int** BOARD;
//remplissage du tableau BOARD
	BOARD=image();
	show_array(10,10,BOARD);
return(0);
}
