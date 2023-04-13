#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

void pickup(int i);
void putdown(int i);
void test(int i);
void init_philosophers(void);
void philosopher_loop(void * num);
void * dine_loop(void * ptr);

//philosopher struct, keeps track of states, mutex lock, and the individual threads, this is the monitor
struct dining_philosophers{
    enum {THINKING, HUNGRY, EATING} state[5];
    pthread_mutex_t lock;
    pthread_cond_t condition[5];
    pthread_t philosophers[5];
};

struct dining_philosophers dining_philosophers;

int main(int argc, char *argv[]){
    int i;
    init_philosophers();

    //initialize lock
    pthread_mutex_init(&dining_philosophers.lock, NULL);
    
    //create 5 philosopher threads and have each perform the dining loop
    for(i = 0; i < 5; i++){
        pthread_create(&dining_philosophers.philosophers[i], NULL, dine_loop, (void *)i);
    }
    for(i = 0; i < 5; i++){
        pthread_join(dining_philosophers.philosophers[i], NULL);
    }
}

//each philosopher starts in thinking state
void init_philosophers(void){
    int i;
    for(i = 0; i < 5; i++){
        dining_philosophers.state[i] = THINKING;
    }
}
//pickup the chopstick
void pickup(int i){
    dining_philosophers.state[i] = HUNGRY;
    pthread_mutex_lock(&dining_philosophers.lock);
    printf("Philosopher %d is hungry\n", i);

    test(i);
    if(dining_philosophers.state[i] != EATING){
        //wait
        pthread_cond_wait(&dining_philosophers.condition[i], &dining_philosophers.lock);
    }
    pthread_mutex_unlock(&dining_philosophers.lock);
}
//put down the chopstick
void putdown(int i){

    pthread_mutex_lock(&dining_philosophers.lock);
    dining_philosophers.state[i] = THINKING;
    printf("philosopher %d has finished eating \n", i);
    test((i + 4) % 5);
    test((i + 1) % 5);
    pthread_mutex_unlock(&dining_philosophers.lock);
}
//test if a philosopher can pickup chopsticks
void test(int i){
    if((dining_philosophers.state[(i + 4) % 5]) != EATING && (dining_philosophers.state[i] == HUNGRY) && (dining_philosophers.state[(i + 1) % 5] != EATING) ){
        dining_philosophers.state[i] = EATING;
        
        //signal the parent process to unlock mutex
        pthread_cond_signal(&dining_philosophers.condition[i]);
    }
}
//dining loop each thread will execute this function
//basic loop goes pickup, putdown
void * dine_loop(void * ptr){
    while(1){

        
//seed random number generator
        srand(time(NULL));
        int think_time, eat_time, id;

        //think/eat for 1-3 seconds per rubric
        think_time = rand() % 3;
        eat_time = rand() % 3;

        id = (int)ptr;
		sleep(think_time);
        printf("philosopher %d is done thinking and ready to eat \n", id);
        pickup(id);
        printf("philosopher %d is eating \n", id);
        sleep(eat_time);
        putdown(id);
    }
}