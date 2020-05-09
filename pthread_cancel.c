#include <stdio.h>
#include <pthread.h>

pthread_t pthread_tt;

void *thread1(void *arg) 
{
	printf("hello world!\n");
	/* void pthread_exit( void * value_ptr ); 线程的终止可以是调用了pthread_exit或者该线程的例程结束。也就是说,一个线程可以隐式的退出,也可以显式的调用pthread_exit函	  数来退出。*/
	while(1)
        {	
		  /* ，只有在被取消线程下次系统调用时，才会真正结束线程。如果线程里面没有执行系统调用，可以使用pthread_testcancel解决 now end  not to down*/
		  pthread_testcancel();  
	}

//	printf("byebye world!\n");

}

void thread_wait(void)
{
	printf("wait iws !\n");
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
	
	sleep(1);

	/* 一个线程可以调用pthread_cancel终止同一进程中的另一个线程，但是值得强调的是：同一进程的线程间，pthread_cancel向另一线程发终止信号。系统并不会马上关闭被取消线程，只有在被取消线程下次系统调用时，才会真正结束线程。或调用pthread_testcancel，让内核去检测是否需要取消当前线程。被取消的线程，退出值，定义在Linux的pthread库中常数PTHREAD_CANCELED的值是-1。*/
	pthread_cancel(pthread_tt);
	thread_wait();
	return 0;
}
