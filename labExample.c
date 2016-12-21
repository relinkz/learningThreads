#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1024
#define T_SIZE 128
#define T_NUM 8

static double a[SIZE][SIZE];
static double b[SIZE][SIZE];
static double c[SIZE][SIZE];

pthread_t pts[SIZE];
pthread_attr_t attr;
//pthread_attr_init(&attr);

int i, j, k;

void* matrix(void *y)
{
        int x = *(int*)y;
        x = x * T_SIZE;
        for(x; x < T_SIZE; x++)
        {
                for(j = 0; j < SIZE; j++)
                {
                        a[x][j] = drand48();
                        b[x][j] = drand48();
                }
        }
}
static void
init_matrix(int x)
{
    pthread_attr_init(&attr);
        int y = 0;
        i = 0;
    for (y; y < T_NUM; y++)
    {
        pthread_create(&pts[i], &attr, matrix, (void*)&i );
        i++;
    }

    for(i = 0; i < T_NUM; i++)
    {
        pthread_join(pts[i], NULL);
    }
}
void* doThings(void *d)
{
    for(j = 0; j < SIZE; j++)
    {
        c[i][j] = 0.0;
         for(k = 0; k < SIZE; k++)
        {
            c[i][j] =  c[i][j] +  a[i][k] * b[k][j];
        }
    }
}

int main(int argc, char **argv)
{
    init_matrix(i);
    
    pthread_attr_init(&attr);
    for (i = 0; i < SIZE; i++)
    {
          pthread_create(&pts[i], &attr, doThings, (void*)0);  
    }
    int x = 0;

    for(x = 0; x < SIZE; x++)
    {
         pthread_join(&pts[x], NULL);
    }
}
