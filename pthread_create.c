#include <stdio.h>
#include <pthread.h>

pthread_t pthread_tt;

void *thread1(void *arg) 
{
	printf("hello world!\n");
	/* void pthread_exit( void * value_ptr ); 线程的终止可以是调用了pthread_exit或者该线程的例程结束。也就是说,一个线程可以隐式的退出,也可以显式的调用pthread_exit函	  数来退出。*/
	pthread_exit(NULL);
}

void thread_wait(void)
{
	/*等待线程结束*/
	if(0 != pthread_tt)
		pthread_join(pthread_tt, NULL);
	
}


int main()
{
	
	int temp = 0;

	/*创建线程*/
	if((temp = pthread_create(&pthread_tt, NULL, thread1, NULL)) != 0) //comment2
	{
		printf("pthread_cteate is ok !\n");
	}
		
	thread_wait();
	return 0;
}
