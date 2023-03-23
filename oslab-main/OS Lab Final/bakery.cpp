#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;
// Milan Mundhra
// 20JE0564
//.cpp file run in linux
#define N 1001

bool Entering[N];
int Number[N];
int shared = 0;
int n;

bool compare(int a, int b, int c, int d)
{
    if (a == c)
        return b < d;
    return a < c;
}
void lock(int i)
{

    Entering[i] = true;
    int val = 0;
    for (int j = 0; j < n; j++)
        val = max(val, Number[j]);
    Number[i] = 1 + val;
    Entering[i] = false;

    for (int j = 0; j < n; j++)
    {
        while (Entering[j])
            ;

        while ((Number[j] != 0) && compare(Number[j], j, Number[i], i))
            ;
    }
}
void unlock(int i)
{
    Number[i] = 0;
}
void *Thread(void *args)
{
    int *x = (int *)args;
    int i = *x;
    while (true)
    {

        lock(i);

        printf("Process %d is in critical section and shared value = %d\n", i, shared);
        shared++;

        unlock(i);
        printf("Process %d is in remainder section\n", i);
        (*x)++;
        return 0;
    }
}
int main(int argc, char *argv[])
{

    int n;
    printf("Enter the no of processes: ");
    scanf("%d", &n);

    pthread_t tid[n];

    int val = 0;
    for (int i = 0; i < n; i++)
        pthread_create(&(tid[i]), NULL, &Thread, &val);

    for (int i = 0; i < n; i++)
        pthread_join(tid[i], NULL);

    sleep(2);
    return 0;
}
