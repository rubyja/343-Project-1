#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

char* createSim(int row, int column);
double getRandD(double min, double max);
void display(int row, int column, char* sim);
int countNei(int row, int column, int x, int y, char* sim);
char* step(int row, int column, char* pSim);
char* readFile(char* filename, int row, int column);
void writeFile(char* filename, char* sim, int row, int column);

#endif