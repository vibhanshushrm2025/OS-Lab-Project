#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <bits/stdc++.h>
// Milan Mundhra
// 20JE0564
//.cpp file run in linux

using namespace std;

int readcount = 0, shared = 5;
sem_t muttex, wrt;
pthread_t r[5], w[2];

void *reader(void *args)
{
    int *x = (int *)args;
    printf("----------------------------------\n");
    printf("Reader - %d is reading\n", *x);
    (*x)++;

    sem_wait(&muttex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);
    sem_post(&muttex);

    printf("Updated value :%d\n", shared);
    sem_wait(&muttex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);
    sem_post(&muttex);

    return 0;
}

void *writer(void *args)
{
    int *x = (int *)args;
    printf("Writer - %d is writing\n", *x);
    (*x)++;

    sem_wait(&wrt);
    shared += 5;
    sem_post(&wrt);

    return 0;
}

int main()
{
    // initializing muttex and wrt with 1
    sem_init(&muttex, 0, 1);
    sem_init(&wrt, 0, 1);

    int read = 0;
    int write = 0;
    pthread_create(&r[0], NULL, &reader, &read);
    sleep(1);
    pthread_create(&w[0], NULL, &writer, &write);
    sleep(1);
    pthread_create(&r[1], NULL, &reader, &read);
    sleep(1);
    pthread_create(&r[2], NULL, &reader, &read);
    sleep(1);
    pthread_create(&r[3], NULL, &reader, &read);
    sleep(1);
    pthread_create(&w[1], NULL, &writer, &write);
    sleep(1);
    pthread_create(&r[4], NULL, &reader, &read);
    sleep(1);

    pthread_join(r[0], NULL);
    pthread_join(w[0], NULL);
    pthread_join(r[1], NULL);
    pthread_join(r[2], NULL);
    pthread_join(r[3], NULL);
    pthread_join(w[1], NULL);
    pthread_join(r[4], NULL);

    return (0);
}
