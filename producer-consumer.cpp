#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <queue>
#include <map>
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
        sleep(1);
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
        sleep(1);
    }
}
int main()
{   
    pthread_t p[5];
    pthread_t c[5];
    sem_init(&empty,0,5);
    sem_init(&full,0,0);
    int i;
    pthread_mutex_lock(&mutex);
    for(i = 0; i < 5; i++) {
        pthread_create(&p[i],NULL,producer,NULL);
        pthread_create(&c[i],NULL,consumer,NULL);
        mc[c[i]] = i+1;
        mp[p[i]] = i+1; 
    }
    pthread_mutex_unlock(&mutex);
    for(i = 0; i < 5; i++) {
        pthread_join(p[i],NULL);
        pthread_join(c[i],NULL);
    }
}