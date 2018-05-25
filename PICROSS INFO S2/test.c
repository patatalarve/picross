/*pour compiler ce fichier : gcc -o EXEC PICROSS.c -Wall -lncurses
  Pour installer la librairie complète ncurses sur votre machine via le terminal, il faut taper la commande : sudo apt-get install libncurses* 
  */
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <ncurses.h> 
#include <unistd.h>
#include <math.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>


int L, C; /*L pour désigner la ligne et C la colonne du clic de la souris*/



/**Initialisation de ncurses**/
void ncurses_initialiser() {
	initscr();	        /* Démarre le mode ncurses */
	cbreak();	        /* Pour les saisies clavier (desac. mise en buffer) */
	noecho();             /* Désactive l'affichage des caractères saisis */
	keypad(stdscr, TRUE);	/* Active les touches spécifiques */
	refresh();            /* Met a jour l'affichage */
	curs_set(FALSE);      /* Masque le curseur */
}


/**Initialisation des couleurs**/
void ncurses_couleurs() {
	/* Vérification du support de la couleur */
	if(has_colors() == FALSE) {
		endwin();
		fprintf(stderr, "Le terminal ne supporte pas les couleurs.\n");
		exit(EXIT_FAILURE);
	}

	/* Activation des couleurs */
	start_color();
	//init_color(COLOR_BLACK, 1000, 1000, 1000);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);

}

/**Initialisation de la souris**/
void ncurses_souris() {
	if(!mousemask(ALL_MOUSE_EVENTS, NULL)) {
		endwin();
		fprintf(stderr, "Erreur lors de l'initialisation de la souris.\n");
		exit(EXIT_FAILURE);
	}

	if(has_mouse() != TRUE) {
		endwin();
		fprintf(stderr, "Aucune souris n'est détectée.\n");
		exit(EXIT_FAILURE);
	}
}


/**Pour récupérer les coordonnées (x,y) du clic de la souris**/
int click_souris()
{
	MEVENT event ;
	int ch;

	while((ch = getch()) != KEY_F(1)) 
	{
		switch(ch) 
		{
			case KEY_F(2): /*Pour quitter la boucle*/
				return 1;
			case KEY_MOUSE:
				if(getmouse(&event) == OK) 
				{
					C = event.x;
					L = event.y;
					if(event.bstate & BUTTON1_CLICKED)
					{ 
						return 0;
					}
				}
		}
	}
	return 0;
}



/*Pour récupérer les données saisies par l'utilisateur sans bloquer le jeu*/
char key_pressed() {
	struct termios oldterm, newterm;
	int oldfd;
	char c, result = 0;
	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm;
	newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
	fcntl (STDIN_FILENO, F_SETFL, oldfd);
	if (c != EOF) {
		ungetc(c, stdin);
		result = getchar();
	}
	return result;
}






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
//calcule les ous sequence des lignes d'un tableau et les rentre dans un tableau a bi dimension
int** calcul_des_sous_sequences_cote(int NB_L, int NB_C, int **BOARD){

	int **TABsoussequencecote;
	int i;
	int j;
	int c=0;
	int d=0;
	//compteur	
	int seq=0;
	int**save;
	
	//initialise le tableau qui va prendre les sous sequence des colonnes de taille NB_L et (NB_C+1)/2
	
	save=NULL;
	save=(int**)malloc(sizeof(int*)*NB_C);

	for(i=0;i<NB_C;i++){
		save[i]=(int*)malloc(sizeof(int)*NB_L);
	}
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

	return(TAB_sous_sequence_haut_final);
}
void affichage_game(int NB_L,int NB_C,int tabgame[NB_L+((NB_L+1)/2)][NB_C+((NB_C+1)/2)], int** TAB_sequence_haut,int** TAB_sequence_cote){
	int x=(NB_L+1)/2;
	int y=(NB_C+1)/2;
	int i;
	int j;
	int cmpt;

	for(i=0;i<x;i++){		//Carre blanc
		printw("   ");
	}

	printw(" ");
	addch(ACS_ULCORNER);		//Premiere ligne du tab

	for(i=x;i<(NB_L+x-1);i++){
		addch(ACS_HLINE);
		addch(ACS_HLINE);
		addch(ACS_HLINE);
		addch(ACS_TTEE);

	}
	addch(ACS_HLINE);			//Derniere ligne du TAB
	addch(ACS_HLINE);
	addch(ACS_HLINE);
	addch(ACS_URCORNER);
	printw("\n");

	for(cmpt=0;cmpt<y;cmpt++){			//repetition pour avoir le tableau des indices


		for(j=0;j<x;j++){
			printw("   ");
		}
		printw(" ");

		for(j=0;j<NB_L;j++){
			addch(ACS_VLINE);
			printw(" ");
		if(TAB_sequence_haut[cmpt][j]==0){
			printw(" ");
			}	
			else{
			printw("%d",TAB_sequence_haut[cmpt][j]);
			}			
		
			printw(" ");

		}
		addch(ACS_VLINE);
		printw("\n");


	}
	addch(ACS_ULCORNER);			//apparition du tableau indice colonnes
	addch(ACS_HLINE);

	for(i=1;i<x;i++){
		addch(ACS_HLINE);
		addch(ACS_HLINE);
		addch(ACS_HLINE);

	}
	addch(ACS_HLINE);
	addch(ACS_HLINE);

	for(i=0;i<NB_L;i++){
		addch(ACS_PLUS);
		addch(ACS_HLINE);
		addch(ACS_HLINE);
		addch(ACS_HLINE);
	}
	addch(ACS_RTEE);
	printw("\n");
	for(j=0;j<NB_C;j++){
		addch(ACS_VLINE);
		printw("");
			
	for(i=0;i<x;i++){
			printw(" ");
			if(TAB_sequence_cote[j][i]==0){
			printw(" ");
			}	
			else{
			printw("%d",TAB_sequence_cote[j][i]);
			}			
			printw(" ");			
		}
		

		for(i=0;i<NB_L;i++){
			addch(ACS_VLINE);
			printw("   ");

		}


		addch(ACS_VLINE);
		printw("\n");
	if(j!=NB_C-1){
		addch(ACS_LTEE);

		for(i=1;i<x;i++){
			addch(ACS_HLINE);
			addch(ACS_HLINE);
			addch(ACS_HLINE);

		}
		addch(ACS_HLINE);
		addch(ACS_HLINE);
		addch(ACS_HLINE);

		for(i=0;i<NB_L;i++){
			addch(ACS_PLUS);
			addch(ACS_HLINE);
			addch(ACS_HLINE);
			addch(ACS_HLINE);
		}
		addch(ACS_RTEE);
		printw("\n");
	}
	
	else{
	
	  addch(ACS_LLCORNER);
	  addch(ACS_HLINE);

	  for(i=1;i<x;i++){
	  addch(ACS_HLINE);
	  addch(ACS_HLINE);
	  addch(ACS_HLINE);
	  }
	  addch(ACS_HLINE);
	  addch(ACS_HLINE);

	  for(i=x;i<NB_L+x-1;i++){
	  addch(ACS_BTEE);
	  addch(ACS_HLINE);
	  addch(ACS_HLINE);
	  addch(ACS_HLINE);

	  }
	//fin bas gauche du tableau
	addch(ACS_BTEE);
	addch(ACS_HLINE);
	addch(ACS_HLINE);
	addch(ACS_HLINE);
	addch(ACS_LRCORNER);
	

}
}
	


}















void LANCEMENT_JEU()
{

	endwin();

	int** SEQ_cote;
	int** SEQ_haut;
	int** SEQ_haut_fin;
	int** BOARD;
	int NB_L;
	int NB_C;
	system("clear");	
	printf("Quelle est la taille du pricross voulu\n\t Nombres de lignes ?\n");
	scanf("%d",&NB_C);

	printf("\t Nombres de colonnes ?\n");
	scanf("%d",&NB_L);

	int TAB[NB_L][NB_C];	
	BOARD=chargement_tableau(NB_L, NB_C);
	SEQ_cote=calcul_des_sous_sequences_cote(NB_L,NB_C,BOARD);
	SEQ_haut=calcul_des_sous_sequence_haut(NB_L,NB_C,BOARD);
	SEQ_haut_fin=remise_haut(NB_L,NB_C,SEQ_haut);
	system("clear");
	affichage_aleatoire(NB_L, NB_C, BOARD);



	ncurses_initialiser(); //Initialisation de ncurses
	ncurses_souris(); //Initialisation de la souris

	while (click_souris() == 0){

		clear();
		printw("Vous avez cliqué sur la position (%d, %d)\n", L, C);
		affichage_game(NB_L,NB_C,TAB,SEQ_haut_fin,SEQ_cote);  

	}
}




int main() {

	ncurses_initialiser(); //Initialisation de ncurses
	ncurses_souris(); //Initialisation de la souris
	LANCEMENT_JEU(); //Lancement du jeu
	endwin(); // Suspendre la session ncurses et restaurer le terminal
	return 0;
}






