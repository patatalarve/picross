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


void affichage_game(int NB_L,int NB_C,int tabgame[NB_L+((NB_L+1)/2)][NB_C+((NB_C+1)/2)]){
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
			
			for(j=x;j<NB_L+x;j++){
				addch(ACS_VLINE);
				printw("   ");
				
				

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
			printw(" ");
			for(i=1;i<x;i++){
				printw(" ");
							
		}
			printw("  ");
		
			for(i=0;i<NB_L;i++){
				addch(ACS_VLINE);
				printw("   ");
	
			}
		

		addch(ACS_VLINE);
		printw("\n");
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
	addch(ACS_VLINE);
	printw(" ");

		for(i=1;i<x;i++){
			printw("   ");
		}
	printw("  ");

		for(i=0;i<NB_L;i++){
			addch(ACS_VLINE);
			printw("   ");
		}

	addch(ACS_VLINE);
	printw("\n");
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

	addch(ACS_BTEE);
	addch(ACS_HLINE);
	addch(ACS_HLINE);
	addch(ACS_HLINE);
	addch(ACS_LRCORNER);


}








void LANCEMENT_JEU()
{
 	int BOARD[10][10];
	 while (click_souris() == 0)
  {
    clear();
    printw("Vous avez cliqué sur la position (%d, %d)\n", L, C);
	affichage_game(10,10,BOARD);  
	}
}




int main() {
 
    ncurses_initialiser(); //Initialisation de ncurses
    ncurses_souris(); //Initialisation de la souris
    LANCEMENT_JEU(); //Lancement du jeu
    endwin(); // Suspendre la session ncurses et restaurer le terminal
    return 0;
}






