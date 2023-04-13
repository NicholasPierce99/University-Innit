#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <semaphore.h>
#include <math.h>

//example run: ./a.out 16384 128 out.txt

int n = 0;//size of array, assume power of 2
int m = 0;//number of threads, also power of 2, m < n
char * file_out = "";//output file name


//reusable barrier variables
int count = 0;
sem_t mutex;
sem_t barrier_sem_1;
sem_t barrier_sem_2;

int *unsortedArrayPointer;//pointer to array to be kept unsorted
int *sortedArrayPointer;//pointer to array to be sorted

void * sort_segment(void * ptr);
void merge(int thread0, int thread1, int length);
void barrier(int threads);
void printSortedArray();
int compare_function(const void *a,const void *b);//used in the qsort function
void writeToFile();

int main(int argc, char *argv[])//sample run: mysort n m out.txt
{
	
	n = atoi(argv[1]);//grab command line arguments
	m = atoi(argv[2]);
	file_out = argv[3];
	
	int sortedArray[n];
	int unsortedArray[n];
	sortedArrayPointer = sortedArray;
	unsortedArrayPointer = unsortedArray;
	
	int i;
	srand(time(NULL));//generate random seed
	for(i = 0; i < n; i++){//populate array with random ints 0-100000
		int randNum = rand() % 100000;//random number 0-100000
		sortedArray[i] = randNum;
		unsortedArray[i] = randNum;
		printf("\n%d",unsortedArray[i]);
	}
	
	
	pthread_t sorters[m];
	
	//initialize semaphore
	//sem_init(&mutex,0,1);//0 means shared between threads, 1 is the value its initialized to
	sem_init(&mutex,0,1);
	sem_init(&barrier_sem_1,0,0);
	sem_init(&barrier_sem_2,0,0);
	
    
    //create threads
    for(i = 0; i < m; i++){
        pthread_create(&sorters[i], NULL, sort_segment, (void *)i);
    }
	//join threads once done
    for(i = 0; i < m; i++){
        pthread_join(sorters[i], NULL);
    }
	
	printSortedArray();
	
	//test to see if results are correct
	qsort (unsortedArray, n, sizeof(*unsortedArray), compare_function);
	int isSorted = 1;
	for(i = 0; i < n; i++){
		if(unsortedArray[i] != sortedArrayPointer[i]){
			isSorted = 0;
		}
	}
	if(isSorted == 1){
		printf("\nsorted successfully\n");
	}else{
		printf("\nnot sorted\n");
	}
	
	writeToFile();
	
}
void printSortedArray(){
	int i;
	for(i = 0; i < n; i++){
		printf("\nsorted: %d",sortedArrayPointer[i]);
	}
	
}

void * sort_segment(void * ptr){//thread function
    int id;
	id = (int)ptr;
	
	int segment_length = (n/m);//how long is this threads portion
	int startIndex = id * segment_length;//where does this portion start in the global array
	int endIndex = startIndex + segment_length;//where does this portion end in the global array
	
	int segment_Array[segment_length];//local array containing this threads portion to be sorted
	
	int i;
	int index = 0;
	
	//dont need to lock because no thread will access the same index in the array
	for(i = startIndex; i < endIndex; i++){//load global array portion into local array
		
		segment_Array[index++] = unsortedArrayPointer[i];
		
	}
	
	qsort (segment_Array, segment_length, sizeof(*segment_Array), compare_function);//sort the local array
	
	//I also dont need to lock because each thread writes to its own space on the array, no overlap possible
	index = 0;
	for(i = startIndex; i < endIndex; i++){//writing sorted portion to global array
		
		sortedArrayPointer[i] = segment_Array[index++];
		
	}
	
	barrier(m);//wait for all threads to get to this point
	
	int original_segment_length = n/m;
	
	int levels = 2;//there will always be at least 2 threads. hopefully.
	while(levels <= m){
		if(id%levels==0){
			printf("\nTry Merge(%d, %d)",id,id+(levels/2));
			merge(id, id+(levels/2), original_segment_length * (levels/2));
			printf("\nComplete Merge(%d, %d)",id,id+(levels/2));
		}
		levels = levels * 2;
		
		barrier(m);//wait for all threads to finish merging
	}
	
	//example
	
	//8 threads
	//levels = 2: merge(0,1) merge(2,3) merge(4,5) merge(6,7)
	//levels = 4: merge(0,2)			merge(4,6)
	//levels = 8: merge(0,4)
	
	//16 threads
	//add 1 to id		//levels = 2: merge(0,1) merge(2,3) merge(4,5) merge(6,7) merge(8,9) merge(10,11) merge(12,13) merge(14,15)
	//add 2 to id		//levels = 4: merge(0,2)			merge(4,6) 			  merge(8,10) 			  merge(12,14)
	//add 4 to id		//levels = 8: merge(0,4)					 			  merge(8,12)
	//add 8 to id		//levels = 8: merge(0,8)
}

void merge(int thread0, int thread1, int length){
	
	int segment_length = n/m;
	
	int thread0StartIndex = thread0 * segment_length;//index in the global array, never changes
	int thread0EndIndex = thread0StartIndex + length;//changes since this thread could have already merged with another thread so could be longer
	
	int thread1StartIndex = thread1 * segment_length;
	int thread1EndIndex = thread1StartIndex + length;
	
	int thread0_Array[length];//depending how many merges have happened, could be larger than n/m
	int thread1_Array[length];
	
	int i;
	int index = 0;
	
	//dont need to lock because no thread will access the same index in the array, before the barrier
	for(i = thread0StartIndex; i < thread0EndIndex; i++){//read this threads portion from the global array
		
		thread0_Array[index++] = sortedArrayPointer[i];
		
	}
	index = 0;
	for(i = thread1StartIndex; i < thread1EndIndex; i++){//read this threads portion from the global array
		
		thread1_Array[index++] = sortedArrayPointer[i];
		
	}
	
	int thread0Index = 0;//keep track of which elements havent been merged into the global array
	int thread1Index = 0;
	for(i = thread0StartIndex; i < thread1EndIndex; i++){//actual merge code, loop through the portion of the global array where both these threads portions will be merged to
		if(thread0Index >= length){//thread0Index must be < length. otherwise add thread1Index to sorted array
			sortedArrayPointer[i] = thread1_Array[thread1Index];
			thread1Index++;
		}else if(thread1Index >= length){
			sortedArrayPointer[i] = thread0_Array[thread0Index];
			thread0Index++;
		}else{
			
			if(thread0_Array[thread0Index] < thread1_Array[thread1Index]){//add whichever threadindex is smallest to the global array
				sortedArrayPointer[i] = thread0_Array[thread0Index];
				thread0Index++;
			}else if(thread0_Array[thread0Index] > thread1_Array[thread1Index]){
				sortedArrayPointer[i] = thread1_Array[thread1Index];
				thread1Index++;
			}else{//numbers are equal, add both of them in whatever order
				sortedArrayPointer[i] = thread0_Array[thread0Index];
				thread0Index++;
				
			}
		
		}
		
	}
	
}

void barrier(int threads){//reusable barrier
	
	//increment count
	sem_wait(&mutex);//mutex 1 initially, others are 0
	count++;
	if (count == threads) {//last thread
		int i;
		for (i = 0; i < threads; i++) {
		  sem_post(&barrier_sem_1);//release all of the threads
		}
	}
	sem_post(&mutex);
	sem_wait(&barrier_sem_1);//all threads except the last wait here because semaphore = 0
	
	
	//decrement count
	sem_wait(&mutex);
	count--;
	if (count == 0) {//last thread
		int i;
		for (i = 0; i < threads; i++) {
		  sem_post(&barrier_sem_2);//release all of the threads, if threads start the next barrier before this thread
		  //leaves its ok because count is at 0 and nothing conflicts
		}
	}
	sem_post(&mutex);
	sem_wait(&barrier_sem_2);//must user different semaphore because a thread could get here before first semaphore gets back to 0
	
}

int compare_function(const void *a,const void *b) {//used in the qsort function
	int *x = (int *) a;
	int *y = (int *) b;
	return *x - *y;
}
void writeToFile(){

	FILE * fp;
    
	fp = fopen(file_out, "w+");
	int i;
	for(i = 0; i < n; i++){
		fprintf(fp, "%d\n", sortedArrayPointer[i]);
	}
	
	fclose(fp);
	
}
