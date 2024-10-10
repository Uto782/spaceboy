#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>

#define COUNT 1000
#define LOOP 10000

struct timespec ts[4][COUNT];

pthread_mutex_t mutex;

void busy(){
	for(int i=0;i<LOOP;i++){
	}
}

void *fun(void *arg){
	int thn=(int)arg;
	for(int i=0;i<100;i++){
		pthread_mutex_lock(&mutex);
		for(int j=0;j<10;j++){
			busy();
			clock_gettime(CLOCK_REALTIME,&ts[thn][(i*10)+j]);
		}
		pthread_mutex_unlock(&mutex);
		busy();
	}
}

int main(){	
	pthread_t th0,th1,th2,th3;
	
	struct timespec x;
	clock_gettime(CLOCK_REALTIME,&x);
	
	long startt=x.tv_sec*1000000000L+x.tv_nsec;
	pthread_mutex_init(&mutex,NULL);
	
	
	pthread_create(&th0,NULL,fun,(void *)0);
	pthread_create(&th1,NULL,fun,(void *)1);
	pthread_create(&th2,NULL,fun,(void *)2);
	pthread_create(&th3,NULL,fun,(void *)3);
	
	pthread_join(th0,NULL);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	pthread_join(th3,NULL);
	
	for(int thn=0;thn<4;thn++){
		for(int i=0;i<COUNT;i++){
			long t=ts[thn][i].tv_sec*1000000000L+ts[thn][i].tv_nsec;
			printf("%ld\t%d\n",t-startt,thn);
		}
	}
}
