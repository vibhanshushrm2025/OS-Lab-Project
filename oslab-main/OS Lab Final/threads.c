//.c file, run in linux
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
//.c file, run in linux
pthread_t tid[4];

void* doThreadTask(void *arg)
{
	        pthread_t id = pthread_self();
		int val=1;
		for(int i=0;i<4;i++){
			if(pthread_equal(id,tid[i])){
					printf("Thread %d processing...\n",i+1);
					val=i+1;
					break;
			}
		}


             //thread doing some work
	     sleep(1);

	     printf("Ending thread %d.\n",val);
}

int main(void)
{
	    int i = 0;
	    int err;

            while(i<4){
	          err = pthread_create(&(tid[i]), NULL, &doThreadTask, NULL);
		  if (err != 0)
		      printf("\nCant't create thread :[%s]", strerror(err));
		  else
		      printf("Thread %d created successfully\n",i+1);

		  i++;
	 }

	 sleep(7);
	 return 0;

}
