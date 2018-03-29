#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*------------------------------Struct Declaration------------------------*/
typedef struct Point{
int row;
int column;
}point;
/*------------------- Global Variables------------------------*/
int n;
int digit=0;
int ** board;


/*--------------------- Print the Board -----------------------------*/
void printMatrix(){
	//int cnt=0;
	printf("-------------------------------------------------------------\n");
	for (int i = 0; i < n; i++)
	{
		printf("|");
		for (int j = 0; j < n; j++)
		{
			if(board[i][j] == -1){
				board[i][j] ='X';
				printf(" %c\t| ",board[i][j]);

			}else{
				printf(" %d\t| ",board[i][j]);
			}
			
		}
		//cnt++;
		printf("\n");
	}
	printf("-------------------------------------------------------------\n");
}
/*---------------------- Recursive function for building Tromino --------------------------- */
void Tile(int board_size, point pi){

	point p0,p1,p2,p3,p4;

	int found =0;
	/* Base Case*/
	if(board_size == 2){
		digit++;
		for (int i = 0; i < board_size; i++)
		{
			for (int j = 0; j < board_size;j++)
			{
				if(board[pi.row+i][pi.column+j]== 0){
					board[pi.row+i][pi.column+j] =  digit;
				}
			}
		}
	return;
	}
				//printf("pi.row : %d\n",pi.row);
				//printf("pi.column : %d\n",pi.column);
	for (int i = pi.row; i < n; i++)
	{
		for (int j = pi.column; j < n; j++)
		{
			if(board[i][j]!= 0 && found ==0){
				p0.row = i;
				p0.column = j;
				//printf("p0.row : %d\n",p0.row);
				//printf("p0.column : %d\n",p0.column);
				found =1;
			}
		}
	}
	
	/*Assigns Hole in Remaining Quadrant */
	
	if((p0.row < pi.row +board_size/2) && (p0.column < pi.column + board_size/2)){
		//1st Quadrant
		//printf("I am Quadrant 1\n");
		digit++;
		board[pi.row+board_size/2][pi.column + board_size/2 - 1] = digit;
		board[pi.row+board_size/2][pi.column+board_size/2] = digit;
		board[pi.row+board_size/2 - 1][pi.column+board_size/2] = digit;
	}
	else if((p0.row >= pi.row +board_size/2) && (p0.column < pi.column + board_size/2)){
		//2nd Quadrant
		//printf("I am Quadrant 2\n");
		digit++;
		board[pi.row+board_size/2 - 1][pi.column + (board_size/2)] = digit;
		board[pi.row+board_size/2][pi.column+board_size/2] = digit;
		board[pi.row+board_size/2 - 1][pi.column+board_size/2 - 1] = digit;

	}else if((p0.row < pi.row +board_size/2) && (p0.column >= pi.column + board_size/2)){
		//3rd Quadrant
		//printf("I am Quadrant 3\n");
		digit++;
		board[pi.row+board_size/2][pi.column + (board_size/2) - 1] = digit; //
		board[pi.row+board_size/2][pi.column+board_size/2] = digit;
		board[pi.row+(board_size/2) - 1][pi.column+board_size/2 - 1] = digit;

	}else if((p0.row >= pi.row +board_size/2) && (p0.column >= pi.column + board_size/2)){
		//4th Quadrant
		//printf("I am Quadrant 4\n");
		digit++;
		board[pi.row+board_size/2 - 1][pi.column + board_size/2] = digit;
		board[pi.row+board_size/2][pi.column+board_size/2 - 1] = digit;
		board[pi.row+board_size/2 - 1][pi.column+board_size/2 - 1] = digit;

	}
	//printf("1\n");
	//printBoard();
	/* co-ordinates of four Quadrants */
	p1.row = pi.row; p1.column = pi.column; //1st Quadrant
	p2.row = pi.row; p2.column = pi.column + (board_size/2); //2nd Quadrant
	p3.row = pi.row + board_size/2; p3.column = pi.column; //3rd Quadrant
	p4.row = pi.row + board_size/2; p4.column = pi.column + board_size/2; //4th Quadrant
	/* Recursive Calls */
	Tile(board_size/2,p1);
	//printf("2\n");
	//printBoard();
	Tile(board_size/2,p2);
	//printf("3\n");
	//printBoard();
	Tile(board_size/2,p3);
	//printf("4\n");
	//printBoard();
	Tile(board_size/2,p4);

	return;

}
/*----------------------------------- helper function for recursion ---------------------*/
void trominoTile(int board_size){
	printf("Building Tromino......\n");
	point p1;
	p1.row =0;
	p1.column=0;
	Tile(board_size,p1);
	printMatrix();

}
/*--------------------- Intialize the board ------------------------------------------*/
int ** create(int k,point p){
	printf("Initializing Tromino......\n");

	n = pow(2,k);
	int ** board1= (int **)malloc(n * sizeof(int *));;

	
	for (int i = 0; i < n; i++)
	{
		board1[i]= malloc(n*sizeof(int));
		for (int j = 0; j < n; j++)
		{
			if(i== p.row && j == p.column){
				board1[i][j]= -1;
			}
			else{
				board1[i][j]= 0;
			}
		}
	}
	return board1;
}
/*------------------------------- Main Function ----------------------*/
int main(int argc, char * argv[]){


	printf("----------------Tromino Tilling-------------------\n");
	printf("\n");
	printf("Taking User Inputs for building Tromino......\n");
	if(argc == 4){
		point p;
		int k = atoi(argv[1]);
		//int hole_row = argv[2];
		//int hole_row = argv[3];
		p.row = atoi(argv[2]);
		p.column= atoi(argv[3]);
		//int n = k*k;
		//board = malloc(sizeof(k)*k*k);
		board = create(k,p);
		trominoTile(n);
		printf("\n");
		printf("Tromino Build......\n");
	}else{
	printf("\n");
	printf("Not correct User inputs......\n");
	printf("Please re-run the program with correct user inputs.\n");
	}
	return 0;


}
/*---------------------End---------------------------*/
/*------------------Comments---------------------------
1) Need to put check to see if value of k is greater then 1.
2) Need to put check to see if hole location given is not outside the range.
3) Not forget to include -lm while compiliging your code.
gcc tromino.c -o tromino.out -lm
*/