#include <stdio.h>
#include <pthread.h>
#include<fcntl.h> 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <fcntl.h>

sem_t sem;

#define MAX 10
#define LOG_FILE_CTR
pthread_t thread[2];
int number=0, i;
void *thread1()
{
	int a = 500;
	printf ("thread1 : I'm thread 1\n");
	while(1)
	{	
		sem_wait(&sem);
		a--;
		printf("111111111111111111111fasfasfdasfdafdafasfda\n");
		usleep(500);
	}
	pthread_exit(NULL);
 }


void *thread2()
{
	int a = 500;
	printf("thread2 : I'm thread 2\n");
	while(1)
	{	
  	        sem_post(&sem);
		a--;
		printf("222222222222222222222222222222fasfasfdasfdafdafasfda\n");
		usleep(250);
	}
	pthread_exit(NULL);
}


void thread_create(void)
{
	int temp;
	memset(&thread, 0, sizeof(thread)); //comment1
		/*创建线程*/
	if((temp = pthread_create(&thread[0], NULL, thread1, NULL)) != 0) //comment2
		printf("线程1创建失败!\n");
	else
		printf("线程1被创建\n");


	if((temp = pthread_create(&thread[1], NULL, thread2, NULL)) != 0) //comment3
		printf("线程2创建失败");
	else
		printf("线程2被创建\n");
}


void thread_wait(void)
{
	/*等待线程结束*/
	if(thread[0] !=0) { //comment4
		pthread_join(thread[0],NULL);
		printf("线程1已经结束\n");
	}

	if(thread[1] !=0) { //comment5
		pthread_join(thread[1],NULL);
		printf("线程2已经结束\n");
	}
}


int main()
{
		   int ret;

   		    ret =sem_init(&sem,0,0);

		if(ret!=0)
   		 {
        		perror("sem_init");
	         }
#if 1
		/*用默认属性初始化互斥锁*/
		printf("我是主函数哦，我正在创建线程，呵呵\n");
		thread_create();
		printf("我是主函数哦，我正在等待线程完成任务阿，呵呵\n");
		thread_wait();
#endif
		
		return 0;
}
