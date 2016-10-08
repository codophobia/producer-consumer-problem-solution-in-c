#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <queue>
#include <map>
#include <cstring>
#include <cstdlib>
using namespace std;
sem_t empty;
sem_t full;
int cnt = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
map<pthread_t,int> mc,mp;
queue<int> q;
void *producer(void *a)
{   
    while(1) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        cnt = cnt+1;
        q.push(cnt);
        cout<<cnt<<" item produced by producer "<<mp[pthread_self()]<<endl;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(3);
    }
}
void *consumer(void *a)
{   
    while(1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        cout<<q.front()<<" item consumed by consumer "<<mc[pthread_self()]<<endl;
        q.pop();
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(3);
    }
}
int main(int argc,char *argv[])
{   
    if(argc < 4) {
        cout<<"not enough arguments"<<endl;
        exit(1);
    }
    int pno;
    int cno;
    int buffersize;
    int i;

    pno = atoi(argv[1]);
    cno = atoi(argv[2]);
    buffersize = atoi(argv[3]);
    pthread_t p[pno];
    pthread_t c[cno];
    sem_init(&empty,0,buffersize);
    sem_init(&full,0,0);
    pthread_mutex_lock(&mutex);
    for(i = 0; i < pno; i++) {
        pthread_create(&p[i],NULL,producer,NULL);
        mp[p[i]] = i+1; 
    }
    for(i = 0; i < cno; i++) {
        pthread_create(&c[i],NULL,consumer,NULL);
        mc[c[i]] = i+1;
    }
    pthread_mutex_unlock(&mutex);
    for(i = 0; i < pno; i++) {
        pthread_join(p[i],NULL);
    }
    for(i = 0; i < cno; i++) {
        pthread_join(c[i],NULL);
    }
}