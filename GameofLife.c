
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

void startSim(int row, int column);
char* createSim(int row, int column);
double getRandD(double min, double max);
void display(int row, int column, char* sim);
int countNei(int row, int column, int x, int y, char* sim);
char* step(int row, int column, char* pSim);

int main(int argc, char* argv[]){

	int row = atoi(argv[1]);
	if (row <= 0){
		printf("Row count must be greater than zero, row was %d\n", row);
		return -1;
	}

	row+=2;

	int column = atoi(argv[2]);
	if (column <= 0){
		printf("Column count must be greater than zero, column was %d\n", column);
		return -1;
	}

	column+=2;

	startSim(row, column);
}

//Displays simulation
void display(int row, int column, char* sim){

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	for (int y = 1; y < row - 1; y++){

		for (int x = 1; x < column - 1; x++){
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

	for (int y = 1; y < row - 1; y++){

		for (int x = 1; x < column - 1; x++){
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

//Starts the simulation
void startSim(int row, int column){
	puts("Starting...");
	printf("Rows = %d \n", row);
	printf("Columns = %d \n", column);

	char* sim = createSim(row, column);
	if (sim == NULL) return;
	
	display(row, column, sim);

	//*******************************************************//
	while(1){
		char* newSim = step(row, column, sim);
		if (newSim ==NULL) return;
		
		free(sim);
		sim = newSim;
		display(row, column, sim);
		Sleep(500);
	}
}

//Gets random double to randomize the live cells
double getRandD(double min, double max){
	
	return ((double)rand()/RAND_MAX) * (max - min) + min;
}

//Creates the simulation with random live cells
char* createSim(int row, int column){
	
	char* sim = (char*)malloc(row * column * sizeof(char));

	if (sim == NULL) return NULL;
	
	for (int y = 1; y < row - 1; y++){
		
		for (int x = 1; x < column - 1; x++){
			
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