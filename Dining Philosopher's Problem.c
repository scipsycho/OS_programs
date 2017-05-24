//start of program

#include <stdio.h>  // for input output
#include <unistd.h> // for using sleep function
#include <stdlib.h>	// for using other standar library functions
#include <pthread.h> // for using threads

//Defining number of philosophers
#define NOP 5
//declaring mutex variable for every chopstick present
pthread_mutex_t chopstick[NOP];
//Declaring thread for every philospher
pthread_t philos[NOP];

//An function explicitly made to initialize the mutex variables
void initialize()
{
	int i;
	for(i=0;i<NOP;i++)
		pthread_mutex_init(&chopstick[i],NULL);
}

//Function for the philosopher
void* dinner(void *param)
{
	//The parameter contains the id of the philosopher
	int id=*((int*)param);
	//Time that is used to create delay effects of eating and thinking
	int waittime;
	//infinite loop as the philosophers think, eat and then again think
	while(1)
	{
	//waitime randomized
	waittime=rand()%5;

	//thinking
	printf("Philosopher %d is thinking\n",id);
	sleep(waittime);
	//hungry
	printf("Philosopher %d is hungry\n",id);

	waittime=rand()%5;
	//Trying to eat
	//the chopsticks beside the philosopher locked before trying to eat
	pthread_mutex_lock(&chopstick[(id-1)%NOP]);
	pthread_mutex_lock(&chopstick[(id+1)%NOP]);

	printf("Philospher %d is eating\n",id);
	sleep(waittime);

	//the locked chopsticks are released after eating
	pthread_mutex_unlock(&chopstick[(id-1)%NOP]);
	pthread_mutex_unlock(&chopstick[(id+1)%NOP]);

	}
	return NULL;
}

int main()
{
	//loop counter variable
	int i;
	//id for each philosopher
	int id[NOP];
	for(i=0;i<NOP;i++)
		id[i]=i+1;
	//calling the initialize construct
	initialize();


	//creating the threads for the philosophers
	for(i=0;i<NOP;i++)
		pthread_create(&philos[i],NULL,dinner,(void *)&id[i]);
		//the last argument is the id of the philosopher that is passed
		//to the dinner function

		//threads are joined using the function
	for(i=0;i<NOP;i++)
		pthread_join(philos[i],NULL);

	return 0;
}

//end of program
