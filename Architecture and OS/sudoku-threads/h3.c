#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int board[9][9] =
{	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0}		};//blank 9x9 sudoku board 




/* structure for passing data to threads */ 
typedef struct
{
	int row;
	int column;
	int threadNumber;
	
} parameters;



int threadResults[27] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//27 threads
//each index represents whether that thread passed (1) or failed (0)

void *rowCheck(void *param);//the row check thread
void *colCheck(void *param);//the col check thread
void *threeByThreeCheck(void *param);//the 3x3 check thread

void loadBoard();//load the sudoku board from text file

int main(int argc, char *argv[])
{
	loadBoard();//loading values into board
	
	pthread_t tid[27];//thread identifiers
	pthread_attr_t attr;//thread attributes
	
	//create all threads
	
	int threadIndex = 0;//used for the thread to store its result in threadResults[]
	
	//create all rows threads
	
	int i;
	for(i = 0; i < 9; i++){
	
		//create the parameters for each thread
		
		parameters *data = (parameters *) malloc(sizeof(parameters));
		data->row = i;
		data->column = -1;
		data->threadNumber = threadIndex;
	
	
		pthread_attr_init(&attr);
		pthread_create(&tid[threadIndex],&attr,rowCheck,data);
		
		threadIndex = threadIndex + 1;
	}
	
	//create all columns threads
	
	
	for(i = 0; i < 9; i++){
	
		//create the parameters for each thread
		
		parameters *data = (parameters *) malloc(sizeof(parameters));
		data->row = -1;
		data->column = i;
		data->threadNumber = threadIndex;
	
	
		pthread_attr_init(&attr);
		pthread_create(&tid[threadIndex],&attr,colCheck,data);
		
		threadIndex = threadIndex + 1;
	}
	
	//create all 3x3 threads
	
	int c = 0;
	for(i = 0; i < 3; i++){
		for(c = 0; c < 3; c++){
			
			//create the parameters for each thread
		
			parameters *data = (parameters *) malloc(sizeof(parameters));
			data->row = i * 3;
			data->column = c * 3;
			data->threadNumber = threadIndex;
			//free(data)//we might need to free all of these heheheh
		
			pthread_attr_init(&attr);
			pthread_create(&tid[threadIndex],&attr,threeByThreeCheck,data);
			
			threadIndex = threadIndex + 1;
			
		}
	}
	
	//wait for all threads to complete
	
	for(i = 0; i < 27; i++){
	
		pthread_join(tid[i],NULL);
	
	}
	
	//check the results of each thread
	//1 = suduku puzzle solves. 0 = not solved
	
	int completed = 1;
	for(i = 0; i < 27; i++){
		if(threadResults[i] == 0){
			completed = 0;
		}
	}
	
	//print overall results
	
	if(completed == 1){
		printf("Puzzle is solved\n");
	}else{
		printf("Puzzle is not solved\n");
	}
	
	
	return 0;
}

void *rowCheck(void *param) { 

	parameters* data = (parameters*) param;
	
	int numberBank[9] = {1,2,3,4,5,6,7,8,9};
	int c = 0;
	int r = data->row;
	
	
	for(c = 0; c < 9; c++){
		int numBankIndex = board[r][c] - 1;
		numberBank[numBankIndex] = 0;//if every number from 1-9 is shown once, then numbank will only be 0's
	}
	
	int i = 0;
	int sum = 0;
	
	for(i = 0; i < 9; i++){
		sum += numberBank[i];
	}
	if( sum == 0 ){
		
		threadResults[data->threadNumber] = 1;//make this thread as success
		printf("Thread %d is successful\n",data->threadNumber);
	}else{
		printf("Thread %d is not successful\n",data->threadNumber);
	}
	
	pthread_exit(0);
}

void *colCheck(void *param) { 
	parameters* data = (parameters*) param;
	
	int numberBank[9] = {1,2,3,4,5,6,7,8,9};
	int c = data->column;
	int r = 0;
	
	
	for(r = 0; r < 9; r++){
		int numBankIndex = board[r][c] - 1;
		numberBank[numBankIndex] = 0;//if every number from 1-9 is shown once, then numbank will only be 0's
	}
	
	int i = 0;
	int sum = 0;
	
	for(i = 0; i < 9; i++){
		sum += numberBank[i];
	}
	if( sum == 0 ){
		
		threadResults[data->threadNumber] = 1;//make this thread as success
		printf("Thread %d is successful\n",data->threadNumber);
	}else{
		printf("Thread %d is not successful\n",data->threadNumber);
	}
	
	pthread_exit(0);
}

void *threeByThreeCheck(void *param) { 
	parameters* data = (parameters*) param;
	
	int numberBank[9] = {1,2,3,4,5,6,7,8,9};
	int c = data->column;
	int r = data->row;
	
	int x = 0;
	int y = 0;
	
	for(x = 0; x < 3; x++){//check 3x3 area with left top corner starting at [r][c]
		for(y = 0; y < 3; y++){
			int numBankIndex = board[r+x][c+y] - 1;
			numberBank[numBankIndex] = 0;//if every number from 1-9 is shown once, then numbank will only be 0's
		}
	}
	
	int i = 0;
	int sum = 0;
	
	for(i = 0; i < 9; i++){
		sum += numberBank[i];
	}
	if( sum == 0 ){
		
		threadResults[data->threadNumber] = 1;//make this thread as success
		printf("Thread %d is successful\n",data->threadNumber);
	}else{
		printf("Thread %d is not successful\n",data->threadNumber);
	}
	
	pthread_exit(0);
}

void loadBoard(){
	
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("input.txt", "r");
    if (fp == NULL){
		printf("broke");
	}
        
	int row = 0;//increment after each line
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
		
		int col = 0;
		int i = 0;
		for(i = 0; i < 17; i++){
			if(line[i]!=','){
				int num = line[i] - '0';//This is how you convert char to int
				
				board[row][col] = num;
				//printf("%c,", line[i]);
				col++;
			}
		}
		printf("\n");
		row++;
		
    }

    fclose(fp);
	if (line)
        free(line);
}