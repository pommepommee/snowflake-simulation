#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "define.h"

/*SIMULATION FUNCTIONS*/
void init_obstacles(WINDOW*, int*);
int finSimulation(int*);
void updateSimulation(WINDOW*, WINDOW*, WINDOW*, int*, int*, int*, int*);
void createFlocon(WINDOW*, WINDOW*, WINDOW*, int*, int*, int*, int*);
void toLeft(WINDOW*, int*, int*, int*);
void toRight(WINDOW*, int*, int*, int*);

/*EDITOR FUNCTIONS*/
void renduObstacles(WINDOW*,int*);
void clickObstacles(WINDOW*,int*,int*,int*);
int exist(const char*);

#endif //FUNCTION_H
