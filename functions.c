#include "functions.h"
#include "ncurses.h"
#include <math.h>

/* SIMULATION FUNCTIONS*/
void init_obstacles(WINDOW* w, int* mat){
	int nbObstacles = 25;
	for(int i=0 ; i<nbObstacles ; i++){
		int randCol = rand()%(COLONNE);
		int randRow = rand()%(LIGNE);
		mat[randRow * COLONNE + randCol] = 1;

		wattron(w,COLOR_PAIR(2));
		mvwprintw(w,randRow,randCol," ");
		wrefresh(w);
		wattroff(w,COLOR_PAIR(2));
	}
}

int finSimulation(int* mat){
	int j=0;
	for(int i=0 ; i<COLONNE-1 ; i++){
		if(mat[i]==0){
			j=1;
		}
	}
	return j;
}
void updateSimulation(WINDOW* info, WINDOW* simulation, WINDOW* etat, int* col, int* row, int* nbFlocons, int* mat){
	int random=0;
	if(*row<LIGNE-1){
		if(*row<LIGNE && mat[COLONNE*(*row+1)+(*col)]==0){
			mat[COLONNE*(*row)+*col] = 0;
			wattron(simulation,COLOR_PAIR(3));
			mvwprintw(simulation,*row,*col," ");
			wrefresh(simulation);
			wattroff(simulation,COLOR_PAIR(3));
			(*row)++;
			mat[COLONNE*(*row)+(*col)]=2;
			wattron(simulation,COLOR_PAIR(1));
			mvwprintw(simulation,*row,*col," ");
			wrefresh(simulation);
			wattroff(simulation,COLOR_PAIR(1));
		}
		else{
			if((*col<COLONNE-1) && (*col>0) && (*row<LIGNE) && (mat[COLONNE*(*row)+(*col+1)]==0) && (mat[COLONNE*(*row+1)+(*col+1)]==0) && (mat[COLONNE*(*row+1)+(*col-1)]==0) && (mat[COLONNE*(*row)+(*col-1)]==0)){
				random=rand()%2; /* 0 vers la gauche, 1 vers la droite */
				if(random==0){
					toLeft(simulation,row,col,mat);
				}else{
					toRight(simulation,row,col,mat);
				}
			}else{
				if((*col>0) && (*row<LIGNE) && (mat[COLONNE*(*row+1)+(*col-1)]==0) && (mat[COLONNE*(*row)+(*col-1)]==0)){
					toLeft(simulation,row,col,mat);
				}else if((*col<COLONNE-1) && (*row<LIGNE) && (mat[COLONNE*(*row)+(*col+1)]==0) && (mat[COLONNE*(*row+1)+(*col+1)]==0)){
					toRight(simulation,row,col,mat);
				}else{
					createFlocon(info,simulation,etat,col,row,nbFlocons,mat);
				}
			}
		}
	}
	else{	
		createFlocon(info,simulation,etat,col,row,nbFlocons,mat);
	}
}
void createFlocon(WINDOW* info, WINDOW* simulation, WINDOW* etat, int* col, int* row, int* nbFlocons, int* mat){
	do{
		*col = (rand()%(COLONNE));
		*row = 0;
		wattron(simulation, COLOR_PAIR(1));
		mvwprintw(simulation,*row,*col," ");
		wrefresh(simulation);
		wattroff(simulation, COLOR_PAIR(1));
		mat[COLONNE*(*row)+(*col)]=0;
	} while((finSimulation(mat)==1) && (mat[*col]!=0));

	(*nbFlocons)++;
    mvwprintw(etat,1,1, "Flocons : %d", *nbFlocons);
    wrefresh(etat);
	wclear(info);
	mvwprintw(info, 0, 0, "Nouveau flocon colonne : %d", *col);
	wrefresh(info);
}
void toLeft(WINDOW* simulation, int* row, int* col, int* mat){
	wattron(simulation, COLOR_PAIR(3));
	mvwprintw(simulation,*row,*col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(3));
	mat[COLONNE*(*row)+(*col)]=0;
	(*col)--;
	(*row)++;
	mat[COLONNE*(*row)+(*col)]=2;
	wattron(simulation, COLOR_PAIR(1));
	mvwprintw(simulation, *row, *col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(1));
}
void toRight(WINDOW* simulation, int* row, int* col, int* mat){
	wattron(simulation, COLOR_PAIR(3));
	mvwprintw(simulation,*row,*col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(3));
	mat[COLONNE*(*row)+(*col)]=0;
	(*col)++;
	(*row)++;
	mat[COLONNE*(*row)+(*col)]=2;
	wattron(simulation, COLOR_PAIR(1));
	mvwprintw(simulation,*row,*col," ");
	wrefresh(simulation);
	wattroff(simulation, COLOR_PAIR(1));
}

/* EDITOR FUNCTIONS */
void renduObstacles(WINDOW* w, int* mat){
	for(int x=0 ; x<COLONNE ; x++){
		for(int y=0 ; y<LIGNE ; y++){
			if(mat[COLONNE*y+x]){
				wattron(w,COLOR_PAIR(2));
				mvwprintw(w,y,x," ");
				wrefresh(w);
				wattroff(w,COLOR_PAIR(2));
			}
		}
	}		
}

void clickObstacles(WINDOW* simulation, int* col, int* row, int* mat){
	if(mat[COLONNE*(*row)+(*col)]==1){
		mat[COLONNE*(*row)+(*col)]=0;
		wattron(simulation, COLOR_PAIR(3));
		mvwprintw(simulation,*row,*col," ");
		wrefresh(simulation);
		wattroff(simulation, COLOR_PAIR(3));
	}
	else if((mat[COLONNE*(*row)+(*col)]==0)){
			mat[COLONNE*(*row)+(*col)]=1;
			wattron(simulation, COLOR_PAIR(2));
			mvwprintw(simulation,*row,*col," ");
			wrefresh(simulation);
			wattroff(simulation, COLOR_PAIR(2));
		}
}
int exist(const char* fname){
    int res;
    int file = open(fname, O_WRONLY);
    if(file==-1){
        // printf("Erreur : le fichier \"%s\" n'existe pas.\n",fname);
        res = EXIT_FAILURE;
    }else{
        // printf("Le fichier "%s" existe.\n",fname);
        res = file;
    }
    return res;
}