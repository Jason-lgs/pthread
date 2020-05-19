#include <stdio.h>
#include <pthread.h>
#include<fcntl.h> 
#include <time.h>
#define MAX 10

int fd;
pthread_t thread[2];
pthread_mutex_t mut;
int number=0, i;
void *thread1()
{
	int a = 500;
	printf ("thread1 : I'm thread 1\n");
	while(a)
	{	
		a--;
		printf("fasfasfdasfdafdafasfda\n");
		write(fd, "hello\n", 6);
		usleep(50);
	}
	pthread_exit(NULL);
 }


void *thread2()
{
	int a = 500;
	printf("thread2 : I'm thread 2\n");
	while(a)
	{	
		a--;
		printf("fasfasfdasfdafdafasfda\n");
		write(fd, "world\n", 6);
		usleep(50);
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

		fd = open("./1.log", O_RDWR|O_APPEND);
		if(-1 == fd)
                {
			printf("file open is error!\n");
			return -1;
		}

		

		 time_t timep;   
      struct tm *p; 
     
     time(&timep);   
     p = localtime(&timep);
    
     printf("%d-%d-%d %d:%d:%d\n", (1900 + p->tm_year), ( 1 + p->tm_mon), p->tm_mday,
                                 (p->tm_hour + 12), p->tm_min, p->tm_sec); 

#if 0
		/*用默认属性初始化互斥锁*/
	    	pthread_mutex_init(&mut,NULL);
		printf("我是主函数哦，我正在创建线程，呵呵\n");
		thread_create();
		printf("我是主函数哦，我正在等待线程完成任务阿，呵呵\n");
		thread_wait();
#endif
		return 0;
}
