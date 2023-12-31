#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THREADS 10
#define MAX_SIZE 100

int n1 = 2, m1 = 3;
int n2 = 2, m2 = 3;
int B[MAX_SIZE][MAX_SIZE], C[MAX_SIZE][MAX_SIZE], A[MAX_SIZE][MAX_SIZE];
int T[MAX_SIZE];

int current_index = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t prod_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cons_cond = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    int tampon_size = n1;
    while (1) {
        pthread_mutex_lock(&mutex);

        while (current_index == tampon_size) {
            pthread_cond_wait(&prod_cond, &mutex);
        }

        int row_index = current_index;
        for (int col = 0; col < m2; col++) {
            int sum = 0;
            for (int i = 0; i < m1; i++) {
                sum += B[row_index][i] * C[i][col];
            }
            T[row_index * m2 + col] = sum;
        }
         printf("Thread %ld calculated row %d of T:\n", pthread_self(), row_index);
        for (int col = 0; col < m2; col++) {
            printf("%d ", T[row_index * m2 + col]);
        }
        printf("\n");

        current_index++;
        pthread_cond_signal(&cons_cond);
        pthread_mutex_unlock(&mutex);

        if (row_index == n1 - 1) {
            break;
        }
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        while (current_index == 0) {
            pthread_cond_wait(&cons_cond, &mutex);
        }

        int row_index = current_index - 1;
        for (int col = 0; col < m2; col++) {
            A[row_index][col] = T[row_index * m2 + col];
        }

        current_index--;
        pthread_cond_signal(&prod_cond);
        pthread_mutex_unlock(&mutex);

        if (row_index == 0) {
            break;
        }
    }

    pthread_exit(NULL);
}

int main() {
    
    printf("matrice B  : ");
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m1; j++) {
            scanf("%d",&B[i][j]);
        }
    }
    printf("matrice C : ");
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < m2; j++) {
            scanf("%d",&C[i][j]);
        }
    }

    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    printf("Matrix A:\n");
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    return 0;
}
