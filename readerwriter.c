#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<time.h>
sem_t r,w;
int shared=5;
int reader_count=0,writer_count=0;
int m,n;
void reader_func()
{
	sem_wait(&r);
	reader_count++;
	printf("I am Reader value is %d\n",shared);
	printf("No of Readers=%d\n",reader_count);
	sem_post(&r);
}
void writer_func()
{	
	int local;
	sem_wait(&w);
	writer_count++;
	sem_post(&r);
	local=shared;
	local=local+1;
	shared=local;
	printf("I am Writer value updated %d\n",shared);
	if(writer_count==n)
	{
		printf("No of Readers=0\n");
	}	
	sem_post(&w);
}
int main()
{
	srand(time(0));
	printf("Enter no of readers and writers\n");
	scanf("%d%d",&m,&n);
	int i;
	sem_init(&r,0,m);
	sem_init(&w,0,n);
	pthread_t *reader,*writer;
	for(i=0;i<m;i++)
		pthread_create(&reader,NULL,reader_func,NULL);
	for(i=0;i<n;i++)
		pthread_create(&writer,NULL,writer_func,NULL);
	for(i=0;i<m+n;i++)
	{	
		pthread_join(reader,NULL);
		pthread_join(writer,NULL);
	}
	return 0;
}

