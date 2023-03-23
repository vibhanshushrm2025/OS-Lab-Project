#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <bits/stdc++.h>
// Milan Mundhra
// 20JE0564
//.cpp file run in linux

using namespace std;
pthread_t tid[2];
int turn;
bool flag[2];

void *processP1(void *args)
{
    pthread_t id = pthread_self();

    int *shared = (int *)args;
    // thread doing some work
    for (int i = 0; i < 4; i++)
    {
        flag[0] = true;
        turn = 1;
        while (flag[1] && turn == 1)
            ;

        (*shared)++;
        printf("P1 is in critical section and shared value=%d\n", *shared);

        flag[0] = false;
        printf("P1 is in remainder section\n");
    }
    printf("Ending P1\n");
    return 0;
}

void *processP2(void *args)
{
    pthread_t id = pthread_self();

    int *shared = (int *)args;
    // thread doing some work
    for (int i = 0; i < 4; i++)
    {
        flag[1] = true;
        turn = 0;
        while (flag[0] && turn == 0)
            ;

        (*shared)--;
        printf("P2 is in critical section and shared value=%d\n", *shared);

        flag[1] = false;

        printf("P2 is in remainder section\n");
    }
    printf("Ending P2\n");
    return 0;
}
int main(int argc, char *argv[])
{

    int shared = 0;

    pthread_create(&tid[0], NULL, &processP1, &shared);
    pthread_create(&tid[1], NULL, &processP2, &shared);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    sleep(2);
    return 0;
}
