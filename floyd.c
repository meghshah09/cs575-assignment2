#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int totalRow=0;
int totalColumn =0;
int ** path;
/*--------------------- Print the Matrix(Debug)-----------------------------*/
void printMatrix(int ** board){
	//int cnt=0;
	printf("-------------------------------------------------------------\n");
	for (int i = 0; i < totalRow; i++)
	{
		printf("|");
		for (int j = 0; j < totalColumn; j++)
		{
			printf(" %d\t| ",board[i][j]);
		}
		printf("\n");
	}
	printf("-------------------------------------------------------------\n");
}

/*--------------------- Create a Weight Matrix from Given File------------------*/
int ** Create (char * fileName){

	int ** matrixArray = (int **)malloc(sizeof(int *)*10000);
	char buff[255];
	char *token;
	int i=0;
	int j = 0;
	FILE *fptr;
	//fprintf(stderr,"File Finding");
	fptr = fopen (fileName,"r");
	while(fgets(buff,sizeof(buff),fptr)){
		j=0;
		//fprintf(stderr,"File Finding\n");
		matrixArray[i] = malloc(10000*sizeof(int));
		token = strtok(buff,",") ;
		//printf("%s\n",token);
		matrixArray[i][j] = atoi(token);
		while((token = strtok(NULL,","))){
			//printf("j : %s\n",token);
			j++;
			matrixArray[i][j] = atoi(token);
			
		}
		//printf("%d\n",j);
		i++;
	}

	totalRow=i;
	totalColumn =j+1;

	return matrixArray;
}
/*-----------------------------Initaializing Path Matrix------------------------------------*/
int ** initializePath(int ** path){
	fprintf(stderr, "Initializing Path Matrix.........\n");
	path = (int **)malloc(sizeof(int *)*totalRow);
	for (int i = 0; i < totalRow; ++i)
	{
		path[i] = malloc(sizeof(int)*totalColumn);
		for (int j = 0; j < totalColumn; j++)
		{
			path[i][j]=-1;
		}
	}
	return path;
}
/*-----------------------------Initaializing D Matrix----------------------------------*/
int ** initializeDmatrix(int ** d1, int ** m){
	fprintf(stderr, "Initializing D Matrix........\n");
	d1 = (int **)malloc(sizeof(int *)*totalRow);
	for (int i = 0; i < totalRow; ++i)
	{
		d1[i] = malloc(sizeof(int)*totalColumn);
		for (int j = 0; j < totalColumn; j++)
		{
			d1[i][j]=m[i][j];
		}
	}
	return d1;
}
/*------------------------- Core Floyd Algorithm Implementation -------------------------*/
void floyd(int ** d, int ** p){

	for (int k = 0; k < totalRow; k++)
	{
		for (int i = 0; i < totalRow; i++)
		{
			for (int j = 0; j < totalRow; j++)
			{
					if(d[i][j] > (d[i][k]+ d[k][j])){
						d[i][j]= (d[i][k]+ d[k][j]);
						p[i][j] = k;

					}

			}
		}
		
	}
	fprintf(stderr, "Shortest Paths Stored..................\n");
	return;

}
/*--------------------------Recursive Function to print all the shortest Node-------------------------------*/
void Path(int q, int r){
	
	if(path[q][r] == -1){
		
		return;
	}
	Path(q,path[q][r]);
	fprintf(stderr,"V%d ",path[q][r]+1);
	Path(path[q][r],r);


}
/*---------------------------------------------- Helper function to print all nodes -----------------------*/
void printNode(int ** d){
	for(int i =0; i< totalRow; i++){
		for (int j = 0; j < totalColumn; j++)
		{	
			if(d[i][j]<500){
				fprintf(stderr,"V%d : ",i+1);
				Path(i,j);
				fprintf(stderr,"V%d\n",j+1);
			}
		}
	}
}
/*------------------------------------------Main Function---------------------------------*/
int main(int argc, char * argv[]){


	printf("----------------Floyd Algorithm-------------------\n");
	printf("\n");
	printf("Taking User Inputs for finding the shortest path using Floyd Algorithm......\n");

	if(argc==2 && argv[1]!= NULL){
		int ** matrix;
		int ** d;
		matrix = Create(argv[1]);
		path = initializePath(path);
		d = initializeDmatrix(d,matrix);
		floyd(d,path);
		//printf("Weight Matix \n");
		//printMatrix(matrix);
		//printf("Path Matrix\n");
		//printMatrix(path);
		printf("Shortest Path From All Nodes :\n");
		//printMatrix(d);
		printNode(matrix);
	}
	else{
		printf("\n");
		printf("Not correct User inputs......\n");
		printf("Please re-run the program with correct user inputs.\n");
	}
	return 0;
}
/*--------------------------END-----------------------------*/