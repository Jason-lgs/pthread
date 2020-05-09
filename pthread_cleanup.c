/**************************************************************************
    > File Name: pthread_cleanup.c
    > Author: lgs
    > Mail: shengfly1@163.com
    > Created Time: 2020年05月09日 星期六 11时37分48秒
 ************************************************************************/

#include<stdio.h>

#include <stdlib.h>

#include <pthread.h>

 

void cleanup(void *arg)

{

    printf("cleanup:%s\n",(char*)arg);

}

void *thr_fn1(void *arg)

{

    printf("thread 1 start\n");

    pthread_cleanup_push(cleanup,"thread 1 first handler");

    pthread_cleanup_push(cleanup,"thread 1 second handler");

    printf("thread 1 push complete\n");

    if(arg)
	pthread_exit(NULL);
 //       return ((void *)1);

    pthread_cleanup_pop(0);

    pthread_cleanup_pop(0);

  //  return ((void *)1);
	pthread_exit(NULL);

}

void *thr_fn2(void *arg)

{   

    printf("thread 2 start\n");

    pthread_cleanup_push(cleanup,"thread 2 first handler");

    pthread_cleanup_push(cleanup,"thread 2 second handler");

    printf("thread 2 push complete\n");

    if(arg)

        pthread_exit((void *)2);

    pthread_cleanup_pop(0);

    pthread_cleanup_pop(0);

    pthread_exit((void *)2);

}

int main()

{

    int err;

    pthread_t tid1,tid2;

    void *tret;

    err = pthread_create(&tid1,NULL,thr_fn1,(void *)1);

    if(err != 0)

    {

        fprintf(stderr,"thread create 1 is error\n");

        return -1;

    }

    err = pthread_join(tid1,&tret);
    if(err != 0)
    {
        fprintf(stderr,"can't join with thread 1\n");
        return -2;
    }

 
#if 0
    err = pthread_create(&tid2,NULL,thr_fn2,(void *)1);

    if(err != 0)

    {

        fprintf(stderr,"thread create 2 is error\n");

        return -2;

    }

    err = pthread_join(tid1,&tret);

    if(err != 0)

    {

        fprintf(stderr,"can't join with thread 1\n");

        return -2;

    }

 

    //pthread_cancel(tid1);

    printf("thread 1 exit code %d\n",tret);

    err = pthread_join(tid2,&tret);

    if(err != 0)

    {

        fprintf(stderr,"can't join with thread 2\n");

        return -2;

    }

    printf("thread 2 exit code %d\n",tret);
#endif
    return 0;

}

