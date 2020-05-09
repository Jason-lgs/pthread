#include <stdio.h>
#include <pthread.h>
#if 0
typedef struct
{
	int                       detachstate;   // 线程的分离状态
	int                       schedpolicy;   // 线程调度策略
	structsched_param         schedparam;    // 线程的调度参数
	int                       inheritsched;  // 线程的继承性
	int                       scope;         // 线程的作用域
	size_t                    guardsize;     // 线程栈末尾的警戒缓冲区大小
	int                       stackaddr_set; // 线程的栈设置
	void*                     stackaddr;     // 线程栈的位置
	size_t                    stacksize;     // 线程栈的大小
} pthread_attr_t;
#endif 

pthread_t pthread_tt;

void *thread1(void *arg)
{
/* 没有被其他的线程所等待，自己运行结束了，线程也就终止了，马上释放系统资源 */
	printf("hello world!\n");
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
        pthread_attr_t attr;
        
	pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	/*创建线程*/
	if((temp = pthread_create(&pthread_tt, &attr, thread1, NULL)) != 0) //comment2
	{
		printf("pthread_cteate is ok !\n");
	}

	sleep(1);	
	pthread_attr_destroy(&attr);
	//thread_wait();
	return 0;
}

