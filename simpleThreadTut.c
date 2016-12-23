#include <pthread.h>
#include <stdio.h>

//tutorial found on
//http://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/


//this function is run by the secound thread
void* inc_x(void* x_void_ptr)
{
	int* x_ptr = (int*)x_void_ptr;
	
	//increment x to 100
	while(++(*x_ptr) < 100);

	printf("x increment finished\n");
}

int main()
{
	int x = 0;
	int y = 0;

	//show the initial values of x and y
	printf("x: %d, y: %d\n", x, y);

	//this variable is our reference to the secound thread
	pthread_t inc_x_thread;

	//create a secound thread which execute inc_x(&x)
	if(pthread_create(&inc_x_thread, NULL, inc_x, &x))
	{
		fprintf(stderr, "error creating thread");
		return 1;
	}
	//increment y to 100 in the first thread
	while(++y < 100);

	printf("y increment finished\n");

	//wait for secound thread to finish
	if(pthread_join(inc_x_thread, NULL))
	{
		fprintf(stderr, "Error joining thread\n");
		return 2;
	}

	//show the results - x is now 100 thanks to the secound thread
	printf("x: %d, y: %d\n",x, y);

	return 0;
}