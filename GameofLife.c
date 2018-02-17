
#include <stdlib.h>
#include <stdio.h>
#include "GameofLife.h"

int main(int argc, char* argv[]){

	if (argc != 4){
		printf("Not enough parameters!\n");
		printf("Usage: GameofLife numRows numColumns FILE\n");
		printf("FILE is the file you want progress saved to and to load from.\n");
		exit(1);
	}

	int row = atoi(argv[1]);
	if (row <= 0){
		printf("Row count must be greater than zero, row was %d\n", row);
		exit(1);
	}

	int column = atoi(argv[2]);
	if (column <= 0){
		printf("Column count must be greater than zero, column was %d\n", column);
		exit(1);
	}

	char* fileName= argv[3];

	printf("Would you like to load a file to continue a game?\n");
	printf("If so, please make sure you enter the same rows and columns.\n");
	printf("Y : yes 	N : no\n");
	int A = getchar();
	if (A == 'Y'){
		char* sim = readFile(fileName, row, column);
		//display(row, column, sim);
		for(int i=0; i<row*column; i++)
			printf("%c,", sim[i]);
		exit(1);
		int i = 0;
		while (1){
			printf("Would you like to continue or save?\n");
			printf("Enter : continue 	S: save\n");
			int B = getchar();
			if(B == 'S'){
				writeFile(fileName, sim, row, column);
				exit(1);
			}
			else{
				char* newSim = step(row, column, sim);
				free(sim);
				sim = newSim;
				display(row, column, sim);
			}
		}
	}
	else{
		char* sim = createSim(row, column);
		display(row, column, sim);
		int i = 0;
		while (1){
			printf("Would you like to continue or save?\n");
			printf("Enter : continue 	S: save\n");
			int B = getchar();
			if(B == 'S'){
				writeFile(fileName, sim, row, column);
				exit(1);
			}
			else{
				char* newSim = step(row, column, sim);
				free(sim);
				sim = newSim;
				display(row, column, sim);
			}
		}
	}
}

//Displays simulation
void display(int row, int column, char* sim){

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	for (int y = 0; y < row; y++){

		for (int x = 0; x < column; x++){
			printf("%c", *(sim + y*column + x));
		}
		printf("\n");
	}
}

//Counts neighbours
int countNei(int row, int column, int x, int y, char* sim) {

	int cnt = 0;
	int piv = y*column + x;

	for (int i = -1; i <= 1; i++){
		for (int j = -1; j <= 1; j++){
			char c = *(sim + piv + (i * column) + j);

			if(c == '#') cnt++;
		}
	}
	return cnt;
}

//Adds the next step of the simulation, or next "generation"
char* step(int row, int column, char* pSim){
	//********************************************************//
	char* stepSim = malloc(row * column * sizeof(int));
	
	if(stepSim == NULL){
		return NULL;
	}

	for (int y = 0; y < row; y++){

		for (int x = 0; x < column; x++){
			int A = countNei(row, column, x, y, pSim);
			char cell = *(pSim + y*column + x);
			if (cell == '#') A--;

			*(stepSim + y * column + x) = cell;

			if (A < 2){
				*(stepSim + y * column + x) = '.';
			}
			else if((A == 2 || A == 3) && cell == '#'){
				*(stepSim + y * column + x) = '#';
			}	
			else if(A > 3 && cell == '#'){
				*(stepSim + y * column + x) = '.';
			}
			else if(A == 3 && cell == '.'){
				*(stepSim + y * column + x) = '#';
			}
		}		
	}
	return stepSim;
}

//Gets random double to randomize the live cells
double getRandD(double min, double max){
	
	return ((double)rand()/RAND_MAX) * (max - min) + min;
}

//Creates the simulation with random live cells
char* createSim(int row, int column){
	
	char* sim = (char*)malloc(row * column * sizeof(char));

	if (sim == NULL) return NULL;
	
	for (int y = 0; y < row; y++){
		
		for (int x = 0; x < column; x++){
			
			if (getRandD(0.0, 1.0) <= 0.35){
				*(sim + y * column + x) = '#';
			}
			
			else{
				*(sim + y * column + x) = '.';
			}
		}
	}

	return sim;
}
//Reads file in order to load previous saved game
char* readFile(char* filename, int row, int column){
	FILE *file;
	int num;
	int i;
	if ((file = fopen(filename, "r")) == NULL){
		printf("ERROR! File could not be opened\n");
		exit(1);
	}

	char* simLoad = (char*)malloc(row * column * sizeof(char));
	fseek(file, 0L, SEEK_END);
	int size = ftell(file);
	rewind(file);

	if (simLoad == NULL) return NULL;
	
	fread(simLoad, 1, size, file);

	return simLoad;
}
//Writes to file to save game
void writeFile(char* filename, char* sim, int row, int column){
	FILE *file;
	file = fopen(filename, "w");


	if (file == NULL){
		printf("ERROR! Could not open file.\n");
		exit(1);
	}

	for (int y = 0; y < row; y++){

		for (int x = 0; x < column; x++){
			fprintf(file, "%c", *(sim + y*column + x));
		}
	}
	fclose(file);

	return;
}
